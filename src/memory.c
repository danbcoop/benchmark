// #include <numa.h>
// #include <numaif.h>

#include "memory.h"
#include <stdio.h>

// unsigned long long get_free_memory(int node) {
//     if (numa_available() == -1) {
//         printf("NUMA is not supported on this system.\n");
//         return 1;
//     }

//     unsigned long long free
//     numa_node_size(node, &free);
//     return free
// }

void clear_cache() {
    FILE *file = fopen("/proc/sys/vm/drop_caches", "w");
    if (file == NULL) {
        printf("Failed to open /proc/sys/vm/drop_caches. Cache not cleared.");
    }

    /* Clear page cache, dentries, inodes. */
    fprintf(file, "3\n");
    fclose(file);
}