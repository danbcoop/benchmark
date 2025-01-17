#define _GNU_SOURCE

#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h> //Sysconf

#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "measure.skel.h"

#include "lib.h"
#include "memory.h"

extern Config cfg;
extern uint8_t* data;
extern uint32_t page_size;
extern uint64_t num_pages;
extern uint64_t accesses;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file");
        return 1;
    }
    
    read_config(file, &cfg);
    fclose(file);
#ifdef VERBOSE
        printf("Config:\n\tThreads: %d\tRand: %d\n\tSeq: %d\tStride: %d\n", 
                    cfg.NUM_THREADS, cfg.ratio_rand, cfg.ratio_seq, cfg.ratio_stride);
#endif

     struct measure_bpf *skel;

     /* Load BPF program */
     skel = measure_bpf__open_and_load();
     if (!skel) {
         printf("Failed to open and load BPF program\n");
         return 1;
     }
    
     /* Attach BPF program */
     int err = measure_bpf__attach(skel);
     if (err) {
         printf("Failed to attach BPF program: %d\n", err);
         measure_bpf__destroy(skel);
         return 1;
     }

#ifndef TEST
    clear_cache();
    uint64_t available_memory = get_free_memory(NUMA_NODE_LOCAL);
    page_size = sysconf(_SC_PAGESIZE);
    num_pages = num_of_elements(available_memory, page_size, cfg.HOT_COLD_FRACTION, cfg.HOT_RATE, cfg.HIT_RATE);

    data = mmap(NULL, (num_pages * page_size), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (data == MAP_FAILED) {
        printf("mmap() failed\n");
        return 1;
    }
#else
    clear_cache();
    page_size = sysconf(_SC_PAGESIZE);
	uint64_t available_memory = sysconf(_SC_AVPHYS_PAGES) * page_size;
    num_pages = num_of_elements(available_memory, page_size, cfg.HOT_COLD_FRACTION, cfg.HOT_RATE, cfg.HIT_RATE);

    data = mmap(NULL, (num_pages * page_size), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (data == MAP_FAILED) {
        printf("mmap() failed\n");
        return 1;
    }
#endif
    accesses = compute_number_of_accesses()*2;
    read_vmstat();
    pthread_t threads[cfg.NUM_THREADS];
    ThreadData thread_data[cfg.NUM_THREADS];

    uint32_t seed = 2043832;
    srand(seed);
    
    for (int i = 0; i < cfg.NUM_THREADS; i++) {
        thread_data[i].thread_id = i;

        if (pthread_create(&threads[i], NULL, do_access, &thread_data[i]) != 0) {
            printf("Thread creation failed.");
            fclose(file);
            return 1;
        }
    }

    for (int i = 0; i < cfg.NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    move_hot_region();

    /* Detach and unload BPF program */
    measure_bpf__destroy(skel);

    printf("\n %lu pages used.\n", num_pages);
    printf("\n %lu pages accessed.\n", accesses);
    printf("Memory available: %luMi\n", available_memory/1024/1024);
    printf("Memory used: %luMi\n", num_pages*page_size/1024/1024);
    
    /* Print vmstat */
    read_vmstat();
    
    /* Print page fault handling times */
    char buf[MAX_LINE_LENGTH];
    file = fopen("/sys/kernel/debug/tracing/trace_pipe", "r");
    if (file) {
    	while (fgets(buf, sizeof(buf), file)) {
    		printf("%s", buf);
    	}
    	fclose(file);
    }
    return 0;
}
