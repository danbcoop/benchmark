# Setup swap options
# Tune ksawpd’s aggressiveness (start at 20 % memory left, stop at 30% memory left)
#echo 1000 > /proc/sys/vm/watermark_scale_factor
# Configure default readahead 
# setting it to zero means “1 page”, setting it to 1 means “2 pages”, setting it to 2 means “4 pages”, etc.
# default = 3 (8 pages) 
# echo 5 > /proc/sys/vm/page-cluster
#cat /proc/sys/vm/page-cluster
# set swappiness (prefer paging out over reclaiming page cache)
# default=60 (out of 100)
# echo 100 > /proc/sys/vm/swappiness
#cat /proc/sys/vm/swappiness

# Set zram to node 1
#echo 1 > /sys/block/zram0/device/numa_node
# Run benchmark on node 0 (cpu and memory)
#numactl --cpunodebind=0 --membind=0 build/main

# Reset page cache
echo 1 > /proc/sys/vm/drop_caches
# Reset swap device
swapoff -a
swapon /swapfile

t=$(cat ./config | grep threads | awk '{print $NF}')
v=$(cat /sys/kernel/mm/swap/per_thread_ra_enabled)
b=$(cat /sys/kernel/mm/swap/bulk_size_ra)
cat /proc/vmstat | grep swap_ra >> ./vmstat_gc_pt_"$v"_blk_"$b"_t_"$t".txt
cat /proc/vmstat | grep pswpin >> ./vmstat_gc_pt_"$v"_blk_"$b"_t_"$t".txt

/usr/bin/time -o ./time_gc_pt_"$v"_blk_"$b"_t_"$t".txt -a cgexec -g memory:limitmemory make run 

cat /proc/vmstat | grep swap_ra >> ./vmstat_gc_pt_"$v"_blk_"$b"_t_"$t".txt
cat /proc/vmstat | grep pswpin >> ./vmstat_gc_pt_"$v"_blk_"$b"_t_"$t".txt
#dmesg -l debug | grep swap > debug.txt 

