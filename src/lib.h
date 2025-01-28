#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <stdint.h>


#define MAX_LINE_LENGTH 256
#define NUMBERS_PER_LINE 20
/*#define VERBOSE */
#define COLORS 5
#define TEST
#define NUMA_NODE_LOCAL 0
#define TRACE_BUFFER 1024
/*#define BPF*/
#define MAX_PAGES 999998976


typedef enum access_type {
    rw,
    r,
} access_type;

typedef struct {
    double HOT_COLD_FRACTION;
    double HOT_RATE;
    double HIT_RATE;
    int NUM_THREADS;
    int SIZE_SEQUENCE;
    int SIZE_STRIDE;
    int ratio_rand;
    int ratio_seq;
    int ratio_stride;
    int SIMULATE_GC;
    void (*access)(long unsigned int);
} Config;

typedef struct {
    int thread_id;
    uint64_t offset;
    uint64_t num_of_pages;
    uint64_t accesses;
    uint64_t index;
} ThreadData;

typedef struct {
    char *bytes;
} Data;

void init_output(void);
void read_config(FILE *file, Config *cfg);
void read_vmstat(void);
uint64_t compute_number_of_accesses(void);
uint64_t num_of_elements(uint64_t available_memory, uint32_t element_size, 
                            double hot_fraction, double hot_cold_ratio, double hit_rate);
void write_time_deltas(void);

// int allocate_data();
// void initialize_data();
// void parse_numbers_from_line(const char *line, int *numbers, int *count);
// void init_indices(int N);

// void access_memory(uint64_t address, pattern_type p);
#ifdef TEST
void print_address(int address, int thread_id, int miss);
#endif

uint64_t mod(uint64_t a, uint64_t b);
void *do_access(void *arg);
void move_hot_region(void);
void read_write(uint64_t index);
