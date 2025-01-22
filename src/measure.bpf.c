#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 1024);
    __type(key, pid_t);
    __type(value, u64);
} start_time SEC(".maps");

SEC("kprobe/handle_mm_fault")
int BPF_KPROBE(handle_mm_fault_entry) {
    pid_t pid = bpf_get_current_pid_tgid() & 0xFFFFFFFF;
    u64 ts = bpf_ktime_get_ns();

    bpf_map_update_elem(&start_time, &pid, &ts, BPF_ANY);
    return 0;
}

SEC("kretprobe/handle_mm_fault")
int BPF_KRETPROBE(handle_mm_fault_exit) {
    pid_t pid = bpf_get_current_pid_tgid() & 0xFFFFFFFF;
    u64 *start_ts, end_ts, delta;
    char comm[TASK_COMM_LEN];

    start_ts = bpf_map_lookup_elem(&start_time, &pid);
    if (!start_ts)
        return 0;

    bpf_map_delete_elem(&start_time, &pid);

    end_ts = bpf_ktime_get_ns();
    delta = end_ts - *start_ts;

    if (bpf_get_current_comm(comm, TASK_COMM_LEN))
	    return 0; /* Reading 'task comm' failed */

    if (bpf_strncmp(comm, 7, "measure") == 0)
	    bpf_printk("%llu ns", delta);

    return 0;
}

char LICENSE[] SEC("license") = "GPL";