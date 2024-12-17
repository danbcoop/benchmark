#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#include "lib.c"

extern Config cfg;
//extern int shared_count;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    
    read_config(file, &cfg);
#ifdef VERBOSE
        printf("Config:\n\tMemory: %d\tElement: %d\n\tThreads: %d\n", 
                    cfg.SIZE_MEMORY, cfg.SIZE_ELEMENTS, cfg.NUM_THREADS);
#endif

#ifndef TEST
    // Allocate and initialize data
    if (!allocate_data()) {
        return 0;
    }
    initialize_data();
#endif

    pthread_t threads[cfg.NUM_THREADS];
    ThreadData thread_data[cfg.NUM_THREADS];
    pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

    for (int i = 0; i < cfg.NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].file = file;
        thread_data[i].file_mutex = &file_mutex;

        if (pthread_create(&threads[i], NULL, process_lines, &thread_data[i]) != 0) {
            perror("Error creating thread");
            fclose(file);
            return 1;
        }
    }

    for (int i = 0; i < cfg.NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    fclose(file);

    return 0;
}
