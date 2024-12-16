# Setup swap options
# Tune ksawpd’s aggressiveness (start at 20 % memory left, stop at 30% memory left)
echo 1000 > /proc/sys/vm/watermark_scale_factor
# Configure default readahead 
# setting it to zero means “1 page”, setting it to 1 means “2 pages”, setting it to 2 means “4 pages”, etc.
# default = 3 (8 pages) 
echo 3 > /proc/sys/vm/page-cluster
# set swappiness (prefer paging out over reclaiming page cache)
# default=60 (out of 100)
echo 60 > /proc/sys/vm/swappiness

# Generate access patterns
python /py/access_patterns.py

# Reset swap device
swapoff -a; swapon -a

# Set zram to node 1
echo 1 > /sys/block/zram0/device/numa_node

# Run benchmark on node 0 (cpu and memory)
numactl --cpunodebind=0 --membind=0 build/main
