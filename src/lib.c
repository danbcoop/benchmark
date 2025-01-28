#include "lib.h"
#include "random.c"

#ifdef TEST
const char *thread_colors[COLORS] = {
    "\033[31m", // red
    "\033[32m", // green
    "\033[33m", // yellow
    "\033[34m",  // blue
    "\033[4m",  // blue
};
const char *reset_color = "\033[0m";
#endif

int shared_count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

char* data;
uint32_t page_size;
uint64_t num_pages;
uint64_t accesses;
uint64_t offset = 0;
FILE *file_out;

Config cfg = {.HOT_COLD_FRACTION=0.2, .HOT_RATE=0.5, .HIT_RATE=0.7, .NUM_THREADS=0, .SIZE_SEQUENCE=8,
                .SIZE_STRIDE=10 , .ratio_rand=0, .ratio_seq=10, .ratio_stride=0, .SIMULATE_GC = 1, .access=read_write};


void read_write(uint64_t index) {
    char bytes[page_size];
    
    memcpy(bytes, &data[index * page_size], page_size);
    memset(bytes, *bytes + uniform(2), page_size);
    memcpy(&data[index * page_size], bytes, page_size);
}

void read(uint64_t index) {
    char bytes[page_size];

    memcpy(bytes, &data[index * page_size], page_size);
}

void write_time_deltas() {
    FILE *pipe = fopen("/sys/kernel/debug/tracing/trace", "r");
    char line[MAX_LINE_LENGTH];

    if (pipe) {
	    while (fgets(line, sizeof(line), pipe)) {
    		fprintf(file_out, "%s", line);
	     }
        fclose(pipe);
    }
    
    /* Clear 'trace' */
	FILE *f = fopen("/sys/kernel/debug/tracing/trace", "w");
	fprintf(f,"\n");
	fclose(f);
}

void read_config(FILE *file, Config *cfg) {
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), file)) {
        char key[MAX_LINE_LENGTH];
        int value;

        if (sscanf(line, "%s = %d", key, &value) == 2) {
            if (strcmp(key, "pattern_strided") == 0) {
                cfg->ratio_stride = value;
            } else if (strcmp(key, "pattern_sequential") == 0) {
                cfg->ratio_seq = value;
            } else if (strcmp(key, "threads") == 0) {
                cfg->NUM_THREADS = value;
            } else if (strcmp(key, "pattern_random") == 0) {
                cfg->ratio_rand = value;
            } else if (strcmp(key, "simulate_gc") == 0) {
                cfg->SIMULATE_GC = value;
            } 
#ifdef VERBOSE
	      else {

                printf("Unknown option: %s\n", key);
            }
#endif
        }
    }
}

void init_output() {
    char filename_output[MAX_LINE_LENGTH];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(filename_output, sizeof(filename_output), "time-delta_%m%d_%H%M%S.txt", t);
    file_out = fopen(filename_output, "w");
    if (!file_out) {
        perror("Failed to create output file");
    }
    
    read_vmstat();
}

void read_vmstat() {
    FILE *file = fopen("/proc/vmstat", "r");
    time_t now = time(NULL);
    FILE *file_out;
    char filename[MAX_LINE_LENGTH];
    
    struct tm *t = localtime(&now);
    strftime(filename, sizeof(filename), "vmstat_%m%d_%H%M%S.txt", t);
    file_out = fopen(filename, "w");
    if (!file) {
        perror("Failed to open /proc/vmstat");
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
    		fprintf(file_out, "%s", line);
    }

    fclose(file);
    fclose(file_out);
}

void access_memory(uint64_t address, pattern_type pattern) {
    switch (pattern) {
    case SEQUENTIAL:
        for (int i = 0; i < cfg.SIZE_SEQUENCE; i++) {
            int addr = mod(address+i,num_pages);
            cfg.access(addr);
        }
        break;
    case STRIDED:
        for (int i = 0; i < cfg.SIZE_SEQUENCE*cfg.SIZE_STRIDE; i += cfg.SIZE_STRIDE) {
            int addr = mod(address + i, num_pages);
            cfg.access(addr);
        }
        break;
    case RANDOM:
        cfg.access(address);
        break;
    }
}

uint64_t mod(uint64_t a, uint64_t b) {
    uint64_t r = a % b;
    return r < 0 ? r + b : r;
}

#ifdef TEST
void print_address(int address, int thread_id, int miss) {
    if (miss) {
        printf("%s%s%d%s ", thread_colors[4],thread_colors[thread_id % COLORS], address, reset_color);
    } else {
        printf("%s%d%s ", thread_colors[thread_id % COLORS], address, reset_color);
    }

    // pthread_mutex_lock(&count_mutex);
    // shared_count++;
    // if (shared_count % NUMBERS_PER_LINE == 0)
    //     printf("\n");
    // pthread_mutex_unlock(&count_mutex);
}

void print_addresses(int address, pattern_type pattern,int thread_id, int miss) {
    switch (pattern)
    {
    case SEQUENTIAL:
        for (int i = 0; i < cfg.SIZE_SEQUENCE; i++) {
            print_address(mod(address+i,num_pages), thread_id, miss);
        }
        break;
    case STRIDED:
        for (int i = 0; i < cfg.SIZE_SEQUENCE*cfg.SIZE_STRIDE; i += cfg.SIZE_STRIDE) {
            address = mod(address + (i), num_pages);
            print_address(address, thread_id, miss);
        }
        break;
    case RANDOM:
        print_address(address, thread_id, miss);
        break;
    }
}
#endif

/* Compute the expected value of accesses needed such that every memory
 * region is hit at least once (coupon collector's problem) */
uint64_t compute_number_of_accesses() {
    double num_cold = cfg.HOT_COLD_FRACTION * num_pages;
	double accesses = (num_cold * harmonic(num_cold)) / cfg.HOT_RATE;
	return (uint64_t) accesses;
}

/* Computes the number of pages needed to achieve the desired hit rate */
uint64_t num_of_elements(uint64_t available_memory, uint32_t element_size, double hot_fraction, double hot_cold_ratio, double hit_rate) {
	if (hot_cold_ratio >= hit_rate) {
		printf("Hit rate should be larger than the hot/cold-ratio.");
		return 0;
	}
	uint64_t available_elements, local_hot_elements, local_cold_elements, remote_cold_elements;
	available_elements = available_memory / element_size;
	local_hot_elements = available_elements * hot_fraction;
	local_cold_elements = available_elements - local_hot_elements;
	remote_cold_elements = (local_cold_elements * 
			((1 - hot_cold_ratio) / (hit_rate - hot_cold_ratio)))
	       		- local_cold_elements;
	printf("local hot: %lu, local cold: %lu, available elements: %lu, remote cold: %lu\n", local_hot_elements, local_cold_elements,available_elements, remote_cold_elements);
	return remote_cold_elements + available_elements;
}

void move_hot_region() {
    offset = uniform(num_pages);
}

void *do_access(void *arg) {
    ThreadData *thread = (ThreadData *)arg;
    /*uint64_t count = 0;*/

    while (thread->accesses) {
        /*count++;*/
        uint64_t address;
        (thread->accesses)--;
        
        if (thread->thread_id == 1 && cfg.SIMULATE_GC) {
            address = uniform(thread->num_of_pages) + thread->offset;   
        } else {
            address = mod(thread->index, thread->num_of_pages) + thread->offset;
            (thread->index)++;
        }
        /*print_address(address, thread->thread_id, 0);*/
        // access_memory(page);
        cfg.access(address);
    }
    /*printf("%lu\n",count);*/

    return NULL;
}
