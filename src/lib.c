#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define MAX_LINE_LENGTH 256
#define NUMBERS_PER_LINE 20
#define NUM_CONFIG_PARAMS 6
#define VERBOSE 1
#define COLORS 4

const char *thread_colors[COLORS] = {
    "\033[31m", // red
    "\033[32m", // green
    "\033[33m", // yellow
    "\033[34m"  // blue
};
const char *reset_color = "\033[0m";

typedef enum access_type {
    rw,
    r,
} access_type;

typedef struct {
    int SIZE_MEMORY;
    int SIZE_ELEMENTS;
    int NUM_THREADS;
    access_type ACCESS;
} Config;

typedef struct {
    int thread_id;
    FILE *file;
    pthread_mutex_t *file_mutex;
    Config *cfg;
} ThreadData;

int shared_count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;


void parse_numbers_from_line(const char *line, int *numbers, int *count) {
    const char *ptr = line;
    *count = 0;

    while (*ptr) {
        while (*ptr && !isdigit(*ptr)) {
            ptr++;
        }
        if (*ptr && isdigit(*ptr)) {
            numbers[*count] = strtol(ptr, (char **)&ptr, 10);
            (*count)++;
        }
    }
}


void read_config(FILE *file, Config *cfg) {
    char line[MAX_LINE_LENGTH];
    int values[NUM_CONFIG_PARAMS];
    int count = 0;
    
    fgets(line, sizeof(line), file);
    parse_numbers_from_line(line, values, &count);
    
    for (int i = 0; i < count; i++) {
        switch (i) {
            case 0:
                cfg->SIZE_MEMORY = values[i];
                break;
            case 1:
                cfg->SIZE_ELEMENTS = values[i];
                break;
            case 2:
                cfg->NUM_THREADS = values[i];
                break;
        }
    }

}


void print_address(int address, int thread_id) {
    printf("%s%d%s ", thread_colors[thread_id % COLORS], address, reset_color);

    pthread_mutex_lock(&count_mutex);
    shared_count++;
    if (shared_count % NUMBERS_PER_LINE == 0)
        printf("\n");
    pthread_mutex_unlock(&count_mutex);
}


void *process_lines(void *arg) {
    ThreadData *thread = (ThreadData *)arg;
    char line[MAX_LINE_LENGTH];

    while (1) {
        pthread_mutex_lock(thread->file_mutex);
        if (!fgets(line, sizeof(line), thread->file)) {
            // EoF
            pthread_mutex_unlock(thread->file_mutex);
            break;
        }
        fgets(line, sizeof(line), thread->file);
        pthread_mutex_unlock(thread->file_mutex);

        int addresses[MAX_LINE_LENGTH];
        int count = 0;
        parse_numbers_from_line(line, addresses, &count);

        for (int i = 0; i < count; i++) {
            print_address(addresses[i], thread->thread_id);
        }
    }

    return NULL;
}