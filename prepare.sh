cgcreate -a $USER -t $USER -g memory:limitmemory
echo 1100000000 > /sys/fs/cgroup/limitmemory/memory.max
echo 1000000000 > /sys/fs/cgroup/limitmemory/memory.high

echo 5 > /proc/sys/vm/page-cluster

