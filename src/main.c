#define _GNU_SOURCE

#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h> //Sysconf

#include <sys/select.h>

#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "measure.skel.h"

#include "lib.h"
#include "memory.h"

extern Config cfg;
extern uint8_t* data;
extern uint32_t page_size;
extern uint64_t num_pages;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename_cfg = argv[1];
    FILE *file = fopen(filename_cfg, "r");
    if (!file) {
        printf("Error opening file");
        return 1;
    }
    
    read_config(file, &cfg);
    fclose(file);
    /*init_output();*/
#ifdef VERBOSE
    printf("Config:\n\tThreads: %d\tRand: %d\n\tSeq: %d\tStride: %d\n", 
            cfg.NUM_THREADS, cfg.ratio_rand, cfg.ratio_seq, cfg.ratio_stride);
#endif

#ifdef BPF
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
#endif

#ifndef TEST
    /*clear_cache();*/
    page_size = sysconf(_SC_PAGESIZE);

    data = mmap(NULL, (num_pages * page_size), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (data == MAP_FAILED) {
        printf("mmap() failed\n");
        return 1;
    }
#else
    clear_cache();
    page_size = sysconf(_SC_PAGESIZE);
	num_pages = MAX_PAGES/page_size;
	/* Set overallocation */
	num_pages *= 2;
	/* ensure divisibility*/
	num_pages = num_pages - (num_pages % cfg.NUM_THREADS);

    data = mmap(NULL, (num_pages * page_size), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (data == MAP_FAILED) {
        printf("mmap() failed\n");
        return 1;
    }
#endif
    
    pthread_t threads[cfg.NUM_THREADS];
    ThreadData thread_data[cfg.NUM_THREADS];

    uint32_t seed = 2043832;
    srand(seed);
    
    for (int i = 0; i < cfg.NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].num_of_pages = num_pages / cfg.NUM_THREADS; // we made sure that num_pages is alwas divisible by #threads
        thread_data[i].offset = i * (thread_data[i].num_of_pages);
        thread_data[i].accesses = thread_data[i].num_of_pages * 3;
        thread_data[i].index = 0;

        if (pthread_create(&threads[i], NULL, do_access, &thread_data[i]) != 0) {
            printf("Thread creation failed.");
            return 1;
        }
    }

    for (int i = 0; i < cfg.NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

#ifdef BPF
    /* Detach and unload BPF program */
    measure_bpf__destroy(skel);
    init_output();
    write_time_deltas();
#endif
#ifdef VERBOSE
    printf("\n %lu pages used.\n", num_pages);
    printf("Memory used: %luMi\n", num_pages*page_size);
#endif
    return 0;
}
