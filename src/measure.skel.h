/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */

/* THIS FILE IS AUTOGENERATED BY BPFTOOL! */
#ifndef __MEASURE_BPF_SKEL_H__
#define __MEASURE_BPF_SKEL_H__

#include <errno.h>
#include <stdlib.h>
#include <bpf/libbpf.h>

struct measure_bpf {
	struct bpf_object_skeleton *skeleton;
	struct bpf_object *obj;
	struct {
		struct bpf_map *start_time;
		struct bpf_map *rodata_str1_1;
		struct bpf_map *rodata;
	} maps;
	struct {
		struct bpf_program *handle_mm_fault_entry;
		struct bpf_program *handle_mm_fault_exit;
	} progs;
	struct {
		struct bpf_link *handle_mm_fault_entry;
		struct bpf_link *handle_mm_fault_exit;
	} links;

#ifdef __cplusplus
	static inline struct measure_bpf *open(const struct bpf_object_open_opts *opts = nullptr);
	static inline struct measure_bpf *open_and_load();
	static inline int load(struct measure_bpf *skel);
	static inline int attach(struct measure_bpf *skel);
	static inline void detach(struct measure_bpf *skel);
	static inline void destroy(struct measure_bpf *skel);
	static inline const void *elf_bytes(size_t *sz);
#endif /* __cplusplus */
};

static void
measure_bpf__destroy(struct measure_bpf *obj)
{
	if (!obj)
		return;
	if (obj->skeleton)
		bpf_object__destroy_skeleton(obj->skeleton);
	free(obj);
}

static inline int
measure_bpf__create_skeleton(struct measure_bpf *obj);

static inline struct measure_bpf *
measure_bpf__open_opts(const struct bpf_object_open_opts *opts)
{
	struct measure_bpf *obj;
	int err;

	obj = (struct measure_bpf *)calloc(1, sizeof(*obj));
	if (!obj) {
		errno = ENOMEM;
		return NULL;
	}

	err = measure_bpf__create_skeleton(obj);
	if (err)
		goto err_out;

	err = bpf_object__open_skeleton(obj->skeleton, opts);
	if (err)
		goto err_out;

	return obj;
err_out:
	measure_bpf__destroy(obj);
	errno = -err;
	return NULL;
}

static inline struct measure_bpf *
measure_bpf__open(void)
{
	return measure_bpf__open_opts(NULL);
}

static inline int
measure_bpf__load(struct measure_bpf *obj)
{
	return bpf_object__load_skeleton(obj->skeleton);
}

static inline struct measure_bpf *
measure_bpf__open_and_load(void)
{
	struct measure_bpf *obj;
	int err;

	obj = measure_bpf__open();
	if (!obj)
		return NULL;
	err = measure_bpf__load(obj);
	if (err) {
		measure_bpf__destroy(obj);
		errno = -err;
		return NULL;
	}
	return obj;
}

static inline int
measure_bpf__attach(struct measure_bpf *obj)
{
	return bpf_object__attach_skeleton(obj->skeleton);
}

static inline void
measure_bpf__detach(struct measure_bpf *obj)
{
	bpf_object__detach_skeleton(obj->skeleton);
}

static inline const void *measure_bpf__elf_bytes(size_t *sz);

static inline int
measure_bpf__create_skeleton(struct measure_bpf *obj)
{
	struct bpf_object_skeleton *s;
	int err;

	s = (struct bpf_object_skeleton *)calloc(1, sizeof(*s));
	if (!s)	{
		err = -ENOMEM;
		goto err;
	}

	s->sz = sizeof(*s);
	s->name = "measure_bpf";
	s->obj = &obj->obj;

	/* maps */
	s->map_cnt = 3;
	s->map_skel_sz = sizeof(*s->maps);
	s->maps = (struct bpf_map_skeleton *)calloc(s->map_cnt, s->map_skel_sz);
	if (!s->maps) {
		err = -ENOMEM;
		goto err;
	}

	s->maps[0].name = "start_time";
	s->maps[0].map = &obj->maps.start_time;

	s->maps[1].name = ".rodata.str1.1";
	s->maps[1].map = &obj->maps.rodata_str1_1;

	s->maps[2].name = "measure_.rodata";
	s->maps[2].map = &obj->maps.rodata;

	/* programs */
	s->prog_cnt = 2;
	s->prog_skel_sz = sizeof(*s->progs);
	s->progs = (struct bpf_prog_skeleton *)calloc(s->prog_cnt, s->prog_skel_sz);
	if (!s->progs) {
		err = -ENOMEM;
		goto err;
	}

	s->progs[0].name = "handle_mm_fault_entry";
	s->progs[0].prog = &obj->progs.handle_mm_fault_entry;
	s->progs[0].link = &obj->links.handle_mm_fault_entry;

	s->progs[1].name = "handle_mm_fault_exit";
	s->progs[1].prog = &obj->progs.handle_mm_fault_exit;
	s->progs[1].link = &obj->links.handle_mm_fault_exit;

	s->data = measure_bpf__elf_bytes(&s->data_sz);

	obj->skeleton = s;
	return 0;
err:
	bpf_object__destroy_skeleton(s);
	return err;
}

static inline const void *measure_bpf__elf_bytes(size_t *sz)
{
	static const char data[] __attribute__((__aligned__(8))) = "\
\x7f\x45\x4c\x46\x02\x01\x01\0\0\0\0\0\0\0\0\0\x01\0\xf7\0\x01\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\x48\x22\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\x40\0\x20\0\
\x01\0\x85\0\0\0\x0e\0\0\0\x63\x0a\xfc\xff\0\0\0\0\x85\0\0\0\x05\0\0\0\x7b\x0a\
\xf0\xff\0\0\0\0\xbf\xa2\0\0\0\0\0\0\x07\x02\0\0\xfc\xff\xff\xff\xbf\xa3\0\0\0\
\0\0\0\x07\x03\0\0\xf0\xff\xff\xff\x18\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb7\x04\
\0\0\0\0\0\0\x85\0\0\0\x02\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\0\0\0\x85\0\0\0\
\x0e\0\0\0\x63\x0a\xfc\xff\0\0\0\0\xbf\xa2\0\0\0\0\0\0\x07\x02\0\0\xfc\xff\xff\
\xff\x18\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x85\0\0\0\x01\0\0\0\xbf\x07\0\0\0\0\0\
\0\x15\x07\x1a\0\0\0\0\0\xbf\xa2\0\0\0\0\0\0\x07\x02\0\0\xfc\xff\xff\xff\x18\
\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x85\0\0\0\x03\0\0\0\x85\0\0\0\x05\0\0\0\xbf\
\x06\0\0\0\0\0\0\x79\x77\0\0\0\0\0\0\xbf\xa1\0\0\0\0\0\0\x07\x01\0\0\xec\xff\
\xff\xff\xb7\x02\0\0\x10\0\0\0\x85\0\0\0\x10\0\0\0\x55\0\x0d\0\0\0\0\0\xbf\xa1\
\0\0\0\0\0\0\x07\x01\0\0\xec\xff\xff\xff\xb7\x02\0\0\x07\0\0\0\x18\x03\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x85\0\0\0\xb6\0\0\0\x55\0\x06\0\0\0\0\0\x1f\x76\0\0\0\0\0\
\0\x18\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb7\x02\0\0\x08\0\0\0\xbf\x63\0\0\0\0\0\
\0\x85\0\0\0\x06\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\0\0\0\x47\x50\x4c\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x6d\x65\x61\
\x73\x75\x72\x65\0\x25\x6c\x6c\x75\x20\x6e\x73\0\x5e\0\0\0\x05\0\x08\0\x06\0\0\
\0\x18\0\0\0\x21\0\0\0\x2f\0\0\0\x39\0\0\0\x42\0\0\0\x4c\0\0\0\x01\x03\x04\x20\
\x70\x02\x7a\x0c\0\x01\x03\x04\x18\x20\x01\x50\x04\x20\x70\x02\x7a\0\0\x01\x04\
\x04\x10\x98\x02\x02\x7a\x14\0\x01\x04\x04\x40\x88\x01\x01\x57\0\x01\x04\x04\
\x80\x01\xf0\x01\x01\x56\0\x01\x04\x04\xf0\x01\x98\x02\x01\x56\0\x01\x11\x01\
\x25\x25\x13\x05\x03\x25\x72\x17\x10\x17\x1b\x25\x11\x01\x55\x23\x73\x17\x74\
\x17\x8c\x01\x17\0\0\x02\x34\0\x03\x25\x49\x13\x3f\x19\x3a\x0b\x3b\x0b\x02\x18\
\0\0\x03\x01\x01\x49\x13\0\0\x04\x21\0\x49\x13\x37\x0b\0\0\x05\x24\0\x03\x25\
\x3e\x0b\x0b\x0b\0\0\x06\x24\0\x03\x25\x0b\x0b\x3e\x0b\0\0\x07\x13\x01\x0b\x0b\
\x3a\x0b\x3b\x0b\0\0\x08\x0d\0\x03\x25\x49\x13\x3a\x0b\x3b\x0b\x38\x0b\0\0\x09\
\x0f\0\x49\x13\0\0\x0a\x21\0\x49\x13\x37\x05\0\0\x0b\x16\0\x49\x13\x03\x25\x3a\
\x0b\x3b\x05\0\0\x0c\x16\0\x49\x13\x03\x25\x3a\x0b\x3b\x0b\0\0\x0d\x34\0\x03\
\x25\x49\x13\x3a\x0b\x3b\x05\0\0\x0e\x15\0\x49\x13\x27\x19\0\0\x0f\x34\0\x03\
\x25\x49\x13\x3a\x0b\x3b\x0b\0\0\x10\x15\x01\x49\x13\x27\x19\0\0\x11\x05\0\x49\
\x13\0\0\x12\x0f\0\0\0\x13\x26\0\0\0\x14\x2e\x01\0\0\x15\x34\0\x03\x25\x49\x13\
\x3a\x0b\x3b\x0b\x02\x18\0\0\x16\x26\0\x49\x13\0\0\x17\x18\0\0\0\x18\x04\x01\
\x49\x13\x0b\x0b\x3a\x0b\x3b\x05\0\0\x19\x28\0\x03\x25\x1c\x0f\0\0\x1a\x2e\x01\
\x03\x25\x3a\x0b\x3b\x0b\x27\x19\x49\x13\x20\x21\x01\0\0\x1b\x05\0\x03\x25\x3a\
\x0b\x3b\x0b\x49\x13\0\0\x1c\x34\0\x03\x25\x3a\x0b\x3b\x0b\x49\x13\0\0\x1d\x13\
\x01\x03\x25\x0b\x0b\x3a\x0b\x3b\x05\0\0\x1e\x0d\0\x03\x25\x49\x13\x3a\x0b\x3b\
\x05\x38\x0b\0\0\x1f\x2e\x01\x11\x1b\x12\x06\x40\x18\x7a\x19\x03\x25\x3a\x0b\
\x3b\x0b\x27\x19\x49\x13\x3f\x19\0\0\x20\x1d\x01\x31\x13\x55\x23\x58\x0b\x59\
\x0b\x57\x0b\0\0\x21\x34\0\x02\x22\x31\x13\0\0\x22\x34\0\x02\x18\x31\x13\0\0\0\
\xc6\x03\0\0\x05\0\x01\x08\0\0\0\0\x01\0\x0c\0\x01\x08\0\0\0\0\0\0\0\x02\0\0\0\
\0\0\0\0\0\x02\x08\0\0\0\x0c\0\0\0\x0c\0\0\0\x02\x03\x3a\0\0\0\0\x2e\x02\xa1\0\
\x03\x46\0\0\0\x04\x4a\0\0\0\x04\0\x05\x04\x06\x01\x06\x05\x08\x07\x02\x06\x59\
\0\0\0\0\x0b\x02\xa1\x01\x07\x20\0\x06\x08\x07\x82\0\0\0\0\x07\0\x08\x09\x97\0\
\0\0\0\x08\x08\x08\x0a\xa9\0\0\0\0\x09\x10\x08\x0d\xc0\0\0\0\0\x0a\x18\0\x09\
\x87\0\0\0\x03\x93\0\0\0\x04\x4a\0\0\0\x01\0\x05\x08\x05\x04\x09\x9c\0\0\0\x03\
\x93\0\0\0\x0a\x4a\0\0\0\0\x04\0\x09\xae\0\0\0\x0b\xb7\0\0\0\x0c\x01\x96\x02\
\x0b\x93\0\0\0\x0b\x01\x88\x02\x09\xc5\0\0\0\x0c\xcd\0\0\0\x10\x01\x1e\x0c\xd5\
\0\0\0\x0f\x01\x12\x05\x0e\x07\x08\x0d\x11\xe2\0\0\0\x02\x6f\x01\x09\xe7\0\0\0\
\x0e\xcd\0\0\0\x0f\x12\xe2\0\0\0\x02\x71\x0f\x13\xfc\0\0\0\x02\x4d\x09\x01\x01\
\0\0\x10\x1b\x01\0\0\x11\x1f\x01\0\0\x11\x20\x01\0\0\x11\x20\x01\0\0\x11\xcd\0\
\0\0\0\x05\x14\x05\x08\x12\x09\x25\x01\0\0\x13\x14\x15\x15\x33\x01\0\0\0\x29\
\x02\xa1\x02\0\x03\x3f\x01\0\0\x04\x4a\0\0\0\x08\0\x16\x46\0\0\0\x0f\x16\x4c\
\x01\0\0\x02\x37\x09\x51\x01\0\0\x10\x1f\x01\0\0\x11\x1f\x01\0\0\x11\x20\x01\0\
\0\0\x0f\x17\x69\x01\0\0\x02\x57\x09\x6e\x01\0\0\x10\x1b\x01\0\0\x11\x1f\x01\0\
\0\x11\x20\x01\0\0\0\x0d\x18\x87\x01\0\0\x02\x89\x01\x09\x8c\x01\0\0\x10\x1b\
\x01\0\0\x11\x1f\x01\0\0\x11\x9c\x01\0\0\0\x0c\xa4\x01\0\0\x1a\x01\x0e\x05\x19\
\x07\x04\x0d\x1b\xb1\x01\0\0\x02\x6e\x10\x09\xb6\x01\0\0\x10\x1b\x01\0\0\x11\
\xcb\x01\0\0\x11\x9c\x01\0\0\x11\xcb\x01\0\0\0\x09\x3f\x01\0\0\x0f\x1c\xd8\x01\
\0\0\x02\xb0\x09\xdd\x01\0\0\x10\x1b\x01\0\0\x11\xcb\x01\0\0\x11\x9c\x01\0\0\
\x17\0\x18\xa4\x01\0\0\x04\x01\xef\x82\x19\x1d\0\x19\x1e\x01\x19\x1f\x02\x19\
\x20\x04\0\x18\xa4\x01\0\0\x04\x01\xcf\x17\x19\x21\x10\0\x1a\x22\0\x0e\x93\0\0\
\0\x1b\x23\0\x0e\x32\x02\0\0\x1c\x3b\0\x0f\xae\0\0\0\x1c\x3c\0\x10\xc5\0\0\0\0\
\x09\x37\x02\0\0\x1d\x3a\xa8\x01\x89\x06\x1e\x24\x10\x03\0\0\x01\x8a\x06\0\x1e\
\x26\x10\x03\0\0\x01\x8b\x06\x08\x1e\x27\x10\x03\0\0\x01\x8c\x06\x10\x1e\x28\
\x10\x03\0\0\x01\x8d\x06\x18\x1e\x29\x10\x03\0\0\x01\x8e\x06\x20\x1e\x2a\x10\
\x03\0\0\x01\x8f\x06\x28\x1e\x2b\x10\x03\0\0\x01\x90\x06\x30\x1e\x2c\x10\x03\0\
\0\x01\x91\x06\x38\x1e\x2d\x10\x03\0\0\x01\x92\x06\x40\x1e\x2e\x10\x03\0\0\x01\
\x93\x06\x48\x1e\x2f\x10\x03\0\0\x01\x94\x06\x50\x1e\x30\x10\x03\0\0\x01\x95\
\x06\x58\x1e\x31\x10\x03\0\0\x01\x96\x06\x60\x1e\x32\x10\x03\0\0\x01\x97\x06\
\x68\x1e\x33\x10\x03\0\0\x01\x98\x06\x70\x1e\x34\x10\x03\0\0\x01\x99\x06\x78\
\x1e\x35\x10\x03\0\0\x01\x9a\x06\x80\x1e\x36\x10\x03\0\0\x01\x9b\x06\x88\x1e\
\x37\x10\x03\0\0\x01\x9c\x06\x90\x1e\x38\x10\x03\0\0\x01\x9d\x06\x98\x1e\x39\
\x10\x03\0\0\x01\x9e\x06\xa0\0\x05\x25\x07\x08\x1f\x03\x70\0\0\0\x01\x5a\x42\0\
\x0e\x93\0\0\0\x1b\x23\0\x0e\x32\x02\0\0\x20\x11\x02\0\0\0\0\x0e\x05\x21\0\x21\
\x02\0\0\x21\x01\x29\x02\0\0\0\0\x1a\x3d\0\x17\x93\0\0\0\x1b\x23\0\x17\x32\x02\
\0\0\x1c\x3e\0\x1a\x7b\x03\0\0\x1c\x3b\0\x18\xae\0\0\0\x1c\x3f\0\x19\xc0\0\0\0\
\x1c\x40\0\x19\xc5\0\0\0\x1c\x41\0\x19\xc5\0\0\0\0\x03\x46\0\0\0\x04\x4a\0\0\0\
\x10\0\x1f\x04\x28\x01\0\0\x01\x5a\x43\0\x17\x93\0\0\0\x1b\x23\0\x17\x32\x02\0\
\0\x20\x42\x03\0\0\x01\0\x17\x05\x22\x02\x91\x04\x52\x03\0\0\x21\x02\x5a\x03\0\
\0\x21\x03\x62\x03\0\0\x21\x04\x6a\x03\0\0\x21\x05\x72\x03\0\0\0\0\0\x2f\0\0\0\
\x05\0\x08\0\x03\0\0\0\x0c\0\0\0\x15\0\0\0\x1f\0\0\0\x01\x03\x04\0\x28\x04\x40\
\x60\0\x01\x04\x04\0\x18\x04\x20\x98\x02\0\x03\x03\x70\x03\x04\xa8\x02\0\x14\
\x01\0\0\x05\0\0\0\0\0\0\0\x27\0\0\0\x39\0\0\0\x67\0\0\0\x6f\0\0\0\x74\0\0\0\
\x88\0\0\0\x93\0\0\0\x98\0\0\0\x9c\0\0\0\xa8\0\0\0\xac\0\0\0\xbb\0\0\0\xc1\0\0\
\0\xc7\0\0\0\xda\0\0\0\xe0\0\0\0\xe4\0\0\0\xfd\0\0\0\x0e\x01\0\0\x22\x01\0\0\
\x27\x01\0\0\x2f\x01\0\0\x43\x01\0\0\x57\x01\0\0\x6c\x01\0\0\x79\x01\0\0\x7f\
\x01\0\0\x8b\x01\0\0\x9c\x01\0\0\xa4\x01\0\0\xb0\x01\0\0\xba\x01\0\0\xc5\x01\0\
\0\xd3\x01\0\0\xed\x01\0\0\xf1\x01\0\0\xf5\x01\0\0\x03\x02\0\0\x07\x02\0\0\x0b\
\x02\0\0\x0f\x02\0\0\x12\x02\0\0\x15\x02\0\0\x19\x02\0\0\x1d\x02\0\0\x20\x02\0\
\0\x23\x02\0\0\x26\x02\0\0\x29\x02\0\0\x2c\x02\0\0\x2f\x02\0\0\x32\x02\0\0\x3a\
\x02\0\0\x3d\x02\0\0\x40\x02\0\0\x46\x02\0\0\x49\x02\0\0\x4c\x02\0\0\x54\x02\0\
\0\x58\x02\0\0\x5b\x02\0\0\x74\x02\0\0\x79\x02\0\0\x82\x02\0\0\x89\x02\0\0\x8f\
\x02\0\0\xa5\x02\0\0\x55\x62\x75\x6e\x74\x75\x20\x63\x6c\x61\x6e\x67\x20\x76\
\x65\x72\x73\x69\x6f\x6e\x20\x31\x34\x2e\x30\x2e\x30\x2d\x31\x75\x62\x75\x6e\
\x74\x75\x31\x2e\x31\0\x73\x72\x63\x2f\x6d\x65\x61\x73\x75\x72\x65\x2e\x62\x70\
\x66\x2e\x63\0\x2f\x68\x6f\x6d\x65\x2f\x64\x61\x6e\x69\x65\x6c\x2f\x52\x57\x54\
\x48\x2f\x42\x41\x2f\x63\x6f\x64\x65\x2f\x62\x65\x6e\x63\x68\x6d\x61\x72\x6b\
\x2f\x62\x65\x6e\x63\x68\x6d\x61\x72\x6b\0\x4c\x49\x43\x45\x4e\x53\x45\0\x63\
\x68\x61\x72\0\x5f\x5f\x41\x52\x52\x41\x59\x5f\x53\x49\x5a\x45\x5f\x54\x59\x50\
\x45\x5f\x5f\0\x73\x74\x61\x72\x74\x5f\x74\x69\x6d\x65\0\x74\x79\x70\x65\0\x69\
\x6e\x74\0\x6d\x61\x78\x5f\x65\x6e\x74\x72\x69\x65\x73\0\x6b\x65\x79\0\x5f\x5f\
\x6b\x65\x72\x6e\x65\x6c\x5f\x70\x69\x64\x5f\x74\0\x70\x69\x64\x5f\x74\0\x76\
\x61\x6c\x75\x65\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x6c\x6f\x6e\x67\x20\x6c\
\x6f\x6e\x67\0\x5f\x5f\x75\x36\x34\0\x75\x36\x34\0\x62\x70\x66\x5f\x67\x65\x74\
\x5f\x63\x75\x72\x72\x65\x6e\x74\x5f\x70\x69\x64\x5f\x74\x67\x69\x64\0\x62\x70\
\x66\x5f\x6b\x74\x69\x6d\x65\x5f\x67\x65\x74\x5f\x6e\x73\0\x62\x70\x66\x5f\x6d\
\x61\x70\x5f\x75\x70\x64\x61\x74\x65\x5f\x65\x6c\x65\x6d\0\x6c\x6f\x6e\x67\0\
\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x62\x70\x66\x5f\x6d\x61\x70\x5f\x6c\x6f\x6f\x6b\
\x75\x70\x5f\x65\x6c\x65\x6d\0\x62\x70\x66\x5f\x6d\x61\x70\x5f\x64\x65\x6c\x65\
\x74\x65\x5f\x65\x6c\x65\x6d\0\x62\x70\x66\x5f\x67\x65\x74\x5f\x63\x75\x72\x72\
\x65\x6e\x74\x5f\x63\x6f\x6d\x6d\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x69\x6e\
\x74\0\x5f\x5f\x75\x33\x32\0\x62\x70\x66\x5f\x73\x74\x72\x6e\x63\x6d\x70\0\x62\
\x70\x66\x5f\x74\x72\x61\x63\x65\x5f\x70\x72\x69\x6e\x74\x6b\0\x42\x50\x46\x5f\
\x41\x4e\x59\0\x42\x50\x46\x5f\x4e\x4f\x45\x58\x49\x53\x54\0\x42\x50\x46\x5f\
\x45\x58\x49\x53\x54\0\x42\x50\x46\x5f\x46\x5f\x4c\x4f\x43\x4b\0\x54\x41\x53\
\x4b\x5f\x43\x4f\x4d\x4d\x5f\x4c\x45\x4e\0\x5f\x5f\x5f\x5f\x68\x61\x6e\x64\x6c\
\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\x5f\x65\x6e\x74\x72\x79\0\x63\x74\x78\
\0\x72\x31\x35\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x6c\x6f\x6e\x67\0\x72\x31\
\x34\0\x72\x31\x33\0\x72\x31\x32\0\x62\x70\0\x62\x78\0\x72\x31\x31\0\x72\x31\
\x30\0\x72\x39\0\x72\x38\0\x61\x78\0\x63\x78\0\x64\x78\0\x73\x69\0\x64\x69\0\
\x6f\x72\x69\x67\x5f\x61\x78\0\x69\x70\0\x63\x73\0\x66\x6c\x61\x67\x73\0\x73\
\x70\0\x73\x73\0\x70\x74\x5f\x72\x65\x67\x73\0\x70\x69\x64\0\x74\x73\0\x5f\x5f\
\x5f\x5f\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\x5f\x65\
\x78\x69\x74\0\x63\x6f\x6d\x6d\0\x73\x74\x61\x72\x74\x5f\x74\x73\0\x65\x6e\x64\
\x5f\x74\x73\0\x64\x65\x6c\x74\x61\0\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\
\x66\x61\x75\x6c\x74\x5f\x65\x6e\x74\x72\x79\0\x68\x61\x6e\x64\x6c\x65\x5f\x6d\
\x6d\x5f\x66\x61\x75\x6c\x74\x5f\x65\x78\x69\x74\0\x2c\0\0\0\x05\0\x08\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\x9f\xeb\x01\0\x18\0\0\0\0\0\0\0\x24\x03\0\0\x24\x03\0\0\xd9\x03\0\0\0\0\0\0\0\
\0\0\x02\x03\0\0\0\x01\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\x01\0\0\0\0\0\0\0\x03\
\0\0\0\0\x02\0\0\0\x04\0\0\0\x01\0\0\0\x05\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\0\
\0\0\0\0\0\0\0\x02\x06\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x02\0\0\0\x04\0\0\0\0\
\x04\0\0\0\0\0\0\0\0\0\x02\x08\0\0\0\x19\0\0\0\0\0\0\x08\x09\0\0\0\x1f\0\0\0\0\
\0\0\x08\x02\0\0\0\0\0\0\0\0\0\0\x02\x0b\0\0\0\x2e\0\0\0\0\0\0\x08\x0c\0\0\0\
\x32\0\0\0\0\0\0\x08\x0d\0\0\0\x38\0\0\0\0\0\0\x01\x08\0\0\0\x40\0\0\0\0\0\0\0\
\x04\0\0\x04\x20\0\0\0\x4b\0\0\0\x01\0\0\0\0\0\0\0\x50\0\0\0\x05\0\0\0\x40\0\0\
\0\x5c\0\0\0\x07\0\0\0\x80\0\0\0\x60\0\0\0\x0a\0\0\0\xc0\0\0\0\x66\0\0\0\0\0\0\
\x0e\x0e\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\x02\x11\0\0\0\x71\0\0\0\x15\0\0\x04\xa8\
\0\0\0\x79\0\0\0\x12\0\0\0\0\0\0\0\x7d\0\0\0\x12\0\0\0\x40\0\0\0\x81\0\0\0\x12\
\0\0\0\x80\0\0\0\x85\0\0\0\x12\0\0\0\xc0\0\0\0\x89\0\0\0\x12\0\0\0\0\x01\0\0\
\x8c\0\0\0\x12\0\0\0\x40\x01\0\0\x8f\0\0\0\x12\0\0\0\x80\x01\0\0\x93\0\0\0\x12\
\0\0\0\xc0\x01\0\0\x97\0\0\0\x12\0\0\0\0\x02\0\0\x9a\0\0\0\x12\0\0\0\x40\x02\0\
\0\x9d\0\0\0\x12\0\0\0\x80\x02\0\0\xa0\0\0\0\x12\0\0\0\xc0\x02\0\0\xa3\0\0\0\
\x12\0\0\0\0\x03\0\0\xa6\0\0\0\x12\0\0\0\x40\x03\0\0\xa9\0\0\0\x12\0\0\0\x80\
\x03\0\0\xac\0\0\0\x12\0\0\0\xc0\x03\0\0\xb4\0\0\0\x12\0\0\0\0\x04\0\0\xb7\0\0\
\0\x12\0\0\0\x40\x04\0\0\xba\0\0\0\x12\0\0\0\x80\x04\0\0\xc0\0\0\0\x12\0\0\0\
\xc0\x04\0\0\xc3\0\0\0\x12\0\0\0\0\x05\0\0\xc6\0\0\0\0\0\0\x01\x08\0\0\0\x40\0\
\0\0\0\0\0\0\x01\0\0\x0d\x02\0\0\0\xd4\0\0\0\x10\0\0\0\xd8\0\0\0\x01\0\0\x0c\
\x13\0\0\0\0\0\0\0\x01\0\0\x0d\x02\0\0\0\xd4\0\0\0\x10\0\0\0\x01\x02\0\0\x01\0\
\0\x0c\x15\0\0\0\x95\x03\0\0\0\0\0\x01\x01\0\0\0\x08\0\0\x01\0\0\0\0\0\0\0\x03\
\0\0\0\0\x17\0\0\0\x04\0\0\0\x04\0\0\0\x9a\x03\0\0\0\0\0\x0e\x18\0\0\0\x01\0\0\
\0\0\0\0\0\0\0\0\x0a\x17\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x1a\0\0\0\x04\0\0\0\
\x08\0\0\0\xa2\x03\0\0\0\0\0\x0e\x1b\0\0\0\0\0\0\0\xc3\x03\0\0\x01\0\0\x0f\0\0\
\0\0\x0f\0\0\0\0\0\0\0\x20\0\0\0\xc9\x03\0\0\x01\0\0\x0f\0\0\0\0\x1c\0\0\0\0\0\
\0\0\x08\0\0\0\xd1\x03\0\0\x01\0\0\x0f\0\0\0\0\x19\0\0\0\0\0\0\0\x04\0\0\0\0\
\x69\x6e\x74\0\x5f\x5f\x41\x52\x52\x41\x59\x5f\x53\x49\x5a\x45\x5f\x54\x59\x50\
\x45\x5f\x5f\0\x70\x69\x64\x5f\x74\0\x5f\x5f\x6b\x65\x72\x6e\x65\x6c\x5f\x70\
\x69\x64\x5f\x74\0\x75\x36\x34\0\x5f\x5f\x75\x36\x34\0\x75\x6e\x73\x69\x67\x6e\
\x65\x64\x20\x6c\x6f\x6e\x67\x20\x6c\x6f\x6e\x67\0\x74\x79\x70\x65\0\x6d\x61\
\x78\x5f\x65\x6e\x74\x72\x69\x65\x73\0\x6b\x65\x79\0\x76\x61\x6c\x75\x65\0\x73\
\x74\x61\x72\x74\x5f\x74\x69\x6d\x65\0\x70\x74\x5f\x72\x65\x67\x73\0\x72\x31\
\x35\0\x72\x31\x34\0\x72\x31\x33\0\x72\x31\x32\0\x62\x70\0\x62\x78\0\x72\x31\
\x31\0\x72\x31\x30\0\x72\x39\0\x72\x38\0\x61\x78\0\x63\x78\0\x64\x78\0\x73\x69\
\0\x64\x69\0\x6f\x72\x69\x67\x5f\x61\x78\0\x69\x70\0\x63\x73\0\x66\x6c\x61\x67\
\x73\0\x73\x70\0\x73\x73\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x6c\x6f\x6e\x67\
\0\x63\x74\x78\0\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\
\x5f\x65\x6e\x74\x72\x79\0\x6b\x70\x72\x6f\x62\x65\x2f\x68\x61\x6e\x64\x6c\x65\
\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\0\x2f\x68\x6f\x6d\x65\x2f\x64\x61\x6e\x69\
\x65\x6c\x2f\x52\x57\x54\x48\x2f\x42\x41\x2f\x63\x6f\x64\x65\x2f\x62\x65\x6e\
\x63\x68\x6d\x61\x72\x6b\x2f\x62\x65\x6e\x63\x68\x6d\x61\x72\x6b\x2f\x73\x72\
\x63\x2f\x6d\x65\x61\x73\x75\x72\x65\x2e\x62\x70\x66\x2e\x63\0\x20\x20\x20\x20\
\x70\x69\x64\x5f\x74\x20\x70\x69\x64\x20\x3d\x20\x62\x70\x66\x5f\x67\x65\x74\
\x5f\x63\x75\x72\x72\x65\x6e\x74\x5f\x70\x69\x64\x5f\x74\x67\x69\x64\x28\x29\
\x20\x26\x20\x30\x78\x46\x46\x46\x46\x46\x46\x46\x46\x3b\0\x20\x20\x20\x20\x75\
\x36\x34\x20\x74\x73\x20\x3d\x20\x62\x70\x66\x5f\x6b\x74\x69\x6d\x65\x5f\x67\
\x65\x74\x5f\x6e\x73\x28\x29\x3b\0\x20\x20\x20\x20\x62\x70\x66\x5f\x6d\x61\x70\
\x5f\x75\x70\x64\x61\x74\x65\x5f\x65\x6c\x65\x6d\x28\x26\x73\x74\x61\x72\x74\
\x5f\x74\x69\x6d\x65\x2c\x20\x26\x70\x69\x64\x2c\x20\x26\x74\x73\x2c\x20\x42\
\x50\x46\x5f\x41\x4e\x59\x29\x3b\0\x69\x6e\x74\x20\x42\x50\x46\x5f\x4b\x50\x52\
\x4f\x42\x45\x28\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\
\x5f\x65\x6e\x74\x72\x79\x29\x20\x7b\0\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\
\x66\x61\x75\x6c\x74\x5f\x65\x78\x69\x74\0\x6b\x72\x65\x74\x70\x72\x6f\x62\x65\
\x2f\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\0\x20\x20\x20\
\x20\x73\x74\x61\x72\x74\x5f\x74\x73\x20\x3d\x20\x62\x70\x66\x5f\x6d\x61\x70\
\x5f\x6c\x6f\x6f\x6b\x75\x70\x5f\x65\x6c\x65\x6d\x28\x26\x73\x74\x61\x72\x74\
\x5f\x74\x69\x6d\x65\x2c\x20\x26\x70\x69\x64\x29\x3b\0\x20\x20\x20\x20\x69\x66\
\x20\x28\x21\x73\x74\x61\x72\x74\x5f\x74\x73\x29\0\x20\x20\x20\x20\x62\x70\x66\
\x5f\x6d\x61\x70\x5f\x64\x65\x6c\x65\x74\x65\x5f\x65\x6c\x65\x6d\x28\x26\x73\
\x74\x61\x72\x74\x5f\x74\x69\x6d\x65\x2c\x20\x26\x70\x69\x64\x29\x3b\0\x20\x20\
\x20\x20\x65\x6e\x64\x5f\x74\x73\x20\x3d\x20\x62\x70\x66\x5f\x6b\x74\x69\x6d\
\x65\x5f\x67\x65\x74\x5f\x6e\x73\x28\x29\x3b\0\x20\x20\x20\x20\x64\x65\x6c\x74\
\x61\x20\x3d\x20\x65\x6e\x64\x5f\x74\x73\x20\x2d\x20\x2a\x73\x74\x61\x72\x74\
\x5f\x74\x73\x3b\0\x20\x20\x20\x20\x69\x66\x20\x28\x62\x70\x66\x5f\x67\x65\x74\
\x5f\x63\x75\x72\x72\x65\x6e\x74\x5f\x63\x6f\x6d\x6d\x28\x63\x6f\x6d\x6d\x2c\
\x20\x54\x41\x53\x4b\x5f\x43\x4f\x4d\x4d\x5f\x4c\x45\x4e\x29\x29\0\x20\x20\x20\
\x20\x69\x66\x20\x28\x62\x70\x66\x5f\x73\x74\x72\x6e\x63\x6d\x70\x28\x63\x6f\
\x6d\x6d\x2c\x20\x37\x2c\x20\x22\x6d\x65\x61\x73\x75\x72\x65\x22\x29\x20\x3d\
\x3d\x20\x30\x29\0\x09\x20\x20\x20\x20\x62\x70\x66\x5f\x70\x72\x69\x6e\x74\x6b\
\x28\x22\x25\x6c\x6c\x75\x20\x6e\x73\x22\x2c\x20\x64\x65\x6c\x74\x61\x29\x3b\0\
\x69\x6e\x74\x20\x42\x50\x46\x5f\x4b\x52\x45\x54\x50\x52\x4f\x42\x45\x28\x68\
\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\x5f\x65\x78\x69\x74\
\x29\x20\x7b\0\x63\x68\x61\x72\0\x4c\x49\x43\x45\x4e\x53\x45\0\x5f\x5f\x5f\x5f\
\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\x5f\x65\x78\x69\
\x74\x2e\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x2e\x6d\x61\x70\x73\0\x2e\x72\x6f\x64\
\x61\x74\x61\0\x6c\x69\x63\x65\x6e\x73\x65\0\0\0\0\x9f\xeb\x01\0\x20\0\0\0\0\0\
\0\0\x24\0\0\0\x24\0\0\0\xa4\x01\0\0\xc8\x01\0\0\0\0\0\0\x08\0\0\0\xee\0\0\0\
\x01\0\0\0\0\0\0\0\x14\0\0\0\x16\x02\0\0\x01\0\0\0\0\0\0\0\x16\0\0\0\x10\0\0\0\
\xee\0\0\0\x07\0\0\0\0\0\0\0\x05\x01\0\0\x45\x01\0\0\x11\x3c\0\0\x08\0\0\0\x05\
\x01\0\0\x45\x01\0\0\x0b\x3c\0\0\x10\0\0\0\x05\x01\0\0\x7e\x01\0\0\x0e\x40\0\0\
\x18\0\0\0\x05\x01\0\0\x7e\x01\0\0\x09\x40\0\0\x28\0\0\0\x05\x01\0\0\0\0\0\0\0\
\0\0\0\x40\0\0\0\x05\x01\0\0\x9f\x01\0\0\x05\x48\0\0\x60\0\0\0\x05\x01\0\0\xd9\
\x01\0\0\x05\x38\0\0\x16\x02\0\0\x12\0\0\0\0\0\0\0\x05\x01\0\0\x45\x01\0\0\x11\
\x60\0\0\x08\0\0\0\x05\x01\0\0\x45\x01\0\0\x0b\x60\0\0\x18\0\0\0\x05\x01\0\0\0\
\0\0\0\0\0\0\0\x20\0\0\0\x05\x01\0\0\x30\x02\0\0\x10\x70\0\0\x40\0\0\0\x05\x01\
\0\0\x67\x02\0\0\x09\x74\0\0\x50\0\0\0\x05\x01\0\0\0\0\0\0\0\0\0\0\x58\0\0\0\
\x05\x01\0\0\x7a\x02\0\0\x05\x80\0\0\x70\0\0\0\x05\x01\0\0\xa6\x02\0\0\x0e\x88\
\0\0\x80\0\0\0\x05\x01\0\0\xc7\x02\0\0\x16\x8c\0\0\x90\0\0\0\x05\x01\0\0\0\0\0\
\0\0\0\0\0\x98\0\0\0\x05\x01\0\0\xe7\x02\0\0\x09\x94\0\0\xa8\0\0\0\x05\x01\0\0\
\xe7\x02\0\0\x09\x94\0\0\xb8\0\0\0\x05\x01\0\0\0\0\0\0\0\0\0\0\xc0\0\0\0\x05\
\x01\0\0\x1a\x03\0\0\x09\xa0\0\0\xe0\0\0\0\x05\x01\0\0\x1a\x03\0\0\x09\xa0\0\0\
\xe8\0\0\0\x05\x01\0\0\0\0\0\0\0\0\0\0\xf0\0\0\0\x05\x01\0\0\x48\x03\0\0\x06\
\xa4\0\0\x18\x01\0\0\x05\x01\0\0\x6b\x03\0\0\x05\x5c\0\0\x0c\0\0\0\xff\xff\xff\
\xff\x04\0\x08\0\x08\x7c\x0b\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x70\0\0\0\0\0\
\0\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x28\x01\0\0\0\0\0\0\xfe\0\0\0\x05\0\x08\
\0\x69\0\0\0\x08\x01\x01\xfb\x0e\x0d\0\x01\x01\x01\x01\0\0\0\x01\0\0\x01\x01\
\x01\x1f\x03\0\0\0\0\x2e\0\0\0\x32\0\0\0\x03\x01\x1f\x02\x0f\x05\x1e\x03\x43\0\
\0\0\0\x0c\x8a\x67\x7c\xb3\x40\x5f\x28\x8a\x2b\x09\xee\x5d\x70\x51\xe5\x55\0\0\
\0\x01\xbb\xa6\x69\xc0\xbc\x18\xd8\x12\xee\x92\x22\x37\xd0\x8f\xfd\x85\x5f\0\0\
\0\x02\x32\xb0\x94\x5d\xf6\x10\x15\xe3\xdd\x6b\xe9\xac\x5e\xa4\x27\x78\x04\0\0\
\x09\x02\0\0\0\0\0\0\0\0\x03\x0d\x01\x05\x11\x0a\x13\x05\x0b\x06\x20\x05\x0e\
\x06\x21\x05\x09\x06\x20\x03\x70\x20\x05\x05\x06\x03\x12\x4a\x46\x02\x02\0\x01\
\x01\x04\0\0\x09\x02\0\0\0\0\0\0\0\0\x03\x16\x01\x05\x11\x0a\x13\x05\x0b\x06\
\x20\x03\x68\x20\x05\x10\x06\x03\x1c\x2e\x05\x09\x4b\x06\x03\x63\x20\x05\x05\
\x06\x03\x20\x2e\x05\x0e\x3e\x05\x16\x2f\x06\x03\x5d\x20\x05\x09\x06\x03\x25\
\x2e\x06\x2e\x03\x5b\x20\x06\x03\x28\x2e\x06\x4a\x05\0\x03\x58\x20\x05\x06\x06\
\x03\x29\x20\x05\x05\x03\x6e\x58\x02\x02\0\x01\x01\x2f\x68\x6f\x6d\x65\x2f\x64\
\x61\x6e\x69\x65\x6c\x2f\x52\x57\x54\x48\x2f\x42\x41\x2f\x63\x6f\x64\x65\x2f\
\x62\x65\x6e\x63\x68\x6d\x61\x72\x6b\x2f\x62\x65\x6e\x63\x68\x6d\x61\x72\x6b\0\
\x73\x72\x63\0\x2f\x75\x73\x72\x2f\x69\x6e\x63\x6c\x75\x64\x65\x2f\x62\x70\x66\
\0\x73\x72\x63\x2f\x6d\x65\x61\x73\x75\x72\x65\x2e\x62\x70\x66\x2e\x63\0\x76\
\x6d\x6c\x69\x6e\x75\x78\x2e\x68\0\x62\x70\x66\x5f\x68\x65\x6c\x70\x65\x72\x5f\
\x64\x65\x66\x73\x2e\x68\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x61\x01\0\0\x04\0\xf1\xff\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x05\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x98\x01\0\0\0\0\x05\0\x18\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x38\0\0\
\0\x01\0\x0a\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\x03\0\x09\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x0a\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x03\0\x0b\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x0c\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x0f\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x03\0\x10\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x12\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x13\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x03\0\x19\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x1b\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x1d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\
\0\0\0\x12\0\x03\0\0\0\0\0\0\0\0\0\x70\0\0\0\0\0\0\0\x45\x01\0\0\x11\0\x08\0\0\
\0\0\0\0\0\0\0\x20\0\0\0\0\0\0\0\x92\0\0\0\x12\0\x05\0\0\0\0\0\0\0\0\0\x28\x01\
\0\0\0\0\0\0\x90\x01\0\0\x11\0\x07\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\x40\0\0\
\0\0\0\0\0\x01\0\0\0\x12\0\0\0\x20\0\0\0\0\0\0\0\x01\0\0\0\x12\0\0\0\x58\0\0\0\
\0\0\0\0\x01\0\0\0\x12\0\0\0\xc8\0\0\0\0\0\0\0\x01\0\0\0\x06\0\0\0\xf0\0\0\0\0\
\0\0\0\x01\0\0\0\x07\0\0\0\x08\0\0\0\0\0\0\0\x03\0\0\0\x09\0\0\0\x11\0\0\0\0\0\
\0\0\x03\0\0\0\x0b\0\0\0\x15\0\0\0\0\0\0\0\x03\0\0\0\x0f\0\0\0\x23\0\0\0\0\0\0\
\0\x03\0\0\0\x0d\0\0\0\x27\0\0\0\0\0\0\0\x03\0\0\0\x0a\0\0\0\x2b\0\0\0\0\0\0\0\
\x03\0\0\0\x08\0\0\0\x08\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x0c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x10\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x14\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x18\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x1c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x20\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x24\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x28\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x2c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x30\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x34\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x38\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x3c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x40\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x44\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x48\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x4c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x50\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x54\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x58\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x5c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x60\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x64\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x68\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x6c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x70\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x74\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x78\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x7c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x80\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x84\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x88\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x8c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x90\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x94\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x98\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x9c\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xa0\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xa4\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xa8\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xac\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xb0\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xb4\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xb8\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xbc\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xc0\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xc4\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xc8\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xcc\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xd0\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xd4\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xd8\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xdc\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xe0\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xe4\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xe8\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xec\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xf0\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xf4\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\xf8\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\xfc\0\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\0\x01\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x04\x01\0\0\0\0\0\0\
\x03\0\0\0\x0c\0\0\0\x08\x01\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x0c\x01\0\0\0\0\0\
\0\x03\0\0\0\x0c\0\0\0\x10\x01\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x14\x01\0\0\0\0\
\0\0\x03\0\0\0\x0c\0\0\0\x08\0\0\0\0\0\0\0\x02\0\0\0\x14\0\0\0\x10\0\0\0\0\0\0\
\0\x02\0\0\0\x12\0\0\0\x18\0\0\0\0\0\0\0\x02\0\0\0\x07\0\0\0\x20\0\0\0\0\0\0\0\
\x02\0\0\0\x02\0\0\0\x28\0\0\0\0\0\0\0\x02\0\0\0\x03\0\0\0\x04\x03\0\0\0\0\0\0\
\x04\0\0\0\x12\0\0\0\x1c\x03\0\0\0\0\0\0\x03\0\0\0\x07\0\0\0\x34\x03\0\0\0\0\0\
\0\x04\0\0\0\x14\0\0\0\x2c\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x3c\0\0\0\0\0\0\0\
\x04\0\0\0\x03\0\0\0\x50\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x60\0\0\0\0\0\0\0\
\x04\0\0\0\x02\0\0\0\x70\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x80\0\0\0\0\0\0\0\
\x04\0\0\0\x02\0\0\0\x90\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\xa0\0\0\0\0\0\0\0\
\x04\0\0\0\x02\0\0\0\xb0\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\xc8\0\0\0\0\0\0\0\
\x04\0\0\0\x03\0\0\0\xd8\0\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\xe8\0\0\0\0\0\0\0\
\x04\0\0\0\x03\0\0\0\xf8\0\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\x08\x01\0\0\0\0\0\0\
\x04\0\0\0\x03\0\0\0\x18\x01\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\x28\x01\0\0\0\0\0\
\0\x04\0\0\0\x03\0\0\0\x38\x01\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\x48\x01\0\0\0\0\
\0\0\x04\0\0\0\x03\0\0\0\x58\x01\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\x68\x01\0\0\0\
\0\0\0\x04\0\0\0\x03\0\0\0\x78\x01\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\x88\x01\0\0\
\0\0\0\0\x04\0\0\0\x03\0\0\0\x98\x01\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\xa8\x01\0\
\0\0\0\0\0\x04\0\0\0\x03\0\0\0\xb8\x01\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\xc8\x01\
\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\xd8\x01\0\0\0\0\0\0\x04\0\0\0\x03\0\0\0\x14\0\
\0\0\0\0\0\0\x03\0\0\0\x0e\0\0\0\x18\0\0\0\0\0\0\0\x02\0\0\0\x02\0\0\0\x2c\0\0\
\0\0\0\0\0\x03\0\0\0\x0e\0\0\0\x30\0\0\0\0\0\0\0\x02\0\0\0\x03\0\0\0\x22\0\0\0\
\0\0\0\0\x03\0\0\0\x10\0\0\0\x26\0\0\0\0\0\0\0\x03\0\0\0\x10\0\0\0\x2a\0\0\0\0\
\0\0\0\x03\0\0\0\x10\0\0\0\x36\0\0\0\0\0\0\0\x03\0\0\0\x10\0\0\0\x4b\0\0\0\0\0\
\0\0\x03\0\0\0\x10\0\0\0\x60\0\0\0\0\0\0\0\x03\0\0\0\x10\0\0\0\x7a\0\0\0\0\0\0\
\0\x02\0\0\0\x02\0\0\0\xa9\0\0\0\0\0\0\0\x02\0\0\0\x03\0\0\0\x11\x13\x14\x12\
\x05\0\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\x5f\x65\x6e\
\x74\x72\x79\0\x2e\x64\x65\x62\x75\x67\x5f\x61\x62\x62\x72\x65\x76\0\x2e\x74\
\x65\x78\x74\0\x2e\x72\x65\x6c\x2e\x42\x54\x46\x2e\x65\x78\x74\0\x5f\x5f\x5f\
\x5f\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\x74\x5f\x65\x78\
\x69\x74\x2e\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x2e\x72\x65\x6c\x6b\x72\x65\x74\x70\
\x72\x6f\x62\x65\x2f\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\x61\x75\x6c\
\x74\0\x2e\x72\x65\x6c\x6b\x70\x72\x6f\x62\x65\x2f\x68\x61\x6e\x64\x6c\x65\x5f\
\x6d\x6d\x5f\x66\x61\x75\x6c\x74\0\x68\x61\x6e\x64\x6c\x65\x5f\x6d\x6d\x5f\x66\
\x61\x75\x6c\x74\x5f\x65\x78\x69\x74\0\x2e\x64\x65\x62\x75\x67\x5f\x72\x6e\x67\
\x6c\x69\x73\x74\x73\0\x2e\x64\x65\x62\x75\x67\x5f\x6c\x6f\x63\x6c\x69\x73\x74\
\x73\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x73\x74\x72\x5f\x6f\x66\x66\
\x73\x65\x74\x73\0\x2e\x6d\x61\x70\x73\0\x2e\x64\x65\x62\x75\x67\x5f\x73\x74\
\x72\0\x2e\x64\x65\x62\x75\x67\x5f\x6c\x69\x6e\x65\x5f\x73\x74\x72\0\x2e\x72\
\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x61\x64\x64\x72\0\x2e\x72\x65\x6c\x2e\x64\
\x65\x62\x75\x67\x5f\x69\x6e\x66\x6f\0\x2e\x6c\x6c\x76\x6d\x5f\x61\x64\x64\x72\
\x73\x69\x67\0\x6c\x69\x63\x65\x6e\x73\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\
\x75\x67\x5f\x6c\x69\x6e\x65\0\x73\x74\x61\x72\x74\x5f\x74\x69\x6d\x65\0\x2e\
\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x66\x72\x61\x6d\x65\0\x6d\x65\x61\x73\
\x75\x72\x65\x2e\x62\x70\x66\x2e\x63\0\x2e\x73\x74\x72\x74\x61\x62\0\x2e\x73\
\x79\x6d\x74\x61\x62\0\x2e\x72\x6f\x64\x61\x74\x61\0\x2e\x72\x65\x6c\x2e\x42\
\x54\x46\0\x4c\x49\x43\x45\x4e\x53\x45\0\x4c\x42\x42\x31\x5f\x34\0\x2e\x72\x6f\
\x64\x61\x74\x61\x2e\x73\x74\x72\x31\x2e\x31\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x6f\x01\0\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x95\x20\0\0\0\0\0\0\xae\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\x25\0\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\x7b\0\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\x70\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x77\0\0\0\x09\0\
\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb0\x18\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\
\x1f\0\0\0\x03\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x5d\0\0\0\x01\0\0\0\
\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb0\0\0\0\0\0\0\0\x28\x01\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x59\0\0\0\x09\0\0\0\x40\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\xc0\x18\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\x1f\0\0\0\x05\0\0\0\
\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x2d\x01\0\0\x01\0\0\0\x03\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\xd8\x01\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\xde\0\0\0\x01\0\0\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\xe0\x01\0\0\0\0\0\0\x20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\x9f\x01\0\0\x01\0\0\0\x32\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x02\0\0\0\
\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\
\x7f\x01\0\0\x01\0\0\0\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\x02\0\0\0\0\0\0\
\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb7\0\0\0\
\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x10\x02\0\0\0\0\0\0\x62\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x17\0\0\0\x01\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x72\x02\0\0\0\0\0\0\x8d\x01\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x13\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\xff\x03\0\0\0\0\0\0\xca\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x0f\x01\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x19\0\0\0\0\0\0\x60\0\0\0\0\0\0\0\x1f\0\0\0\x0d\0\0\0\x08\0\0\0\0\0\0\0\
\x10\0\0\0\0\0\0\0\xa7\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xc9\x07\
\0\0\0\0\0\0\x33\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\xcb\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xfc\x07\0\0\0\0\0\0\x18\
\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xc7\0\0\0\
\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x60\x19\0\0\0\0\0\0\x40\x04\0\0\0\
\0\0\0\x1f\0\0\0\x10\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xe4\0\0\0\x01\0\
\0\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x14\x09\0\0\0\0\0\0\xba\x02\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\x03\x01\0\0\x01\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xce\x0b\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xff\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\xa0\x1d\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\x1f\0\0\0\x13\0\0\0\x08\0\
\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x8b\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\x0c\0\0\0\0\0\0\x15\x07\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\x87\x01\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xf0\
\x1d\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\x1f\0\0\0\x15\0\0\0\x08\0\0\0\0\0\0\0\x10\0\
\0\0\0\0\0\0\x2f\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x18\x13\0\0\0\
\0\0\0\xe8\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\x2b\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x20\x1e\0\0\0\0\0\0\xb0\
\x01\0\0\0\0\0\0\x1f\0\0\0\x17\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x54\
\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x15\0\0\0\0\0\0\x40\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x50\x01\0\0\x09\0\0\
\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xd0\x1f\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\x1f\
\0\0\0\x19\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x39\x01\0\0\x01\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\x15\0\0\0\0\0\0\x02\x01\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x35\x01\0\0\x09\0\0\0\x40\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\x10\x20\0\0\0\0\0\0\x80\0\0\0\0\0\0\0\x1f\0\0\0\x1b\0\0\0\
\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xef\0\0\0\x01\0\0\0\x30\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x42\x16\0\0\0\0\0\0\x71\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\
\0\0\0\x01\0\0\0\0\0\0\0\x1f\x01\0\0\x03\x4c\xff\x6f\0\0\0\x80\0\0\0\0\0\0\0\0\
\0\0\0\0\x90\x20\0\0\0\0\0\0\x05\0\0\0\0\0\0\0\x1f\0\0\0\0\0\0\0\x01\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x77\x01\0\0\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb8\
\x16\0\0\0\0\0\0\xf8\x01\0\0\0\0\0\0\x01\0\0\0\x11\0\0\0\x08\0\0\0\0\0\0\0\x18\
\0\0\0\0\0\0\0";

	*sz = sizeof(data) - 1;
	return (const void *)data;
}

#ifdef __cplusplus
struct measure_bpf *measure_bpf::open(const struct bpf_object_open_opts *opts) { return measure_bpf__open_opts(opts); }
struct measure_bpf *measure_bpf::open_and_load() { return measure_bpf__open_and_load(); }
int measure_bpf::load(struct measure_bpf *skel) { return measure_bpf__load(skel); }
int measure_bpf::attach(struct measure_bpf *skel) { return measure_bpf__attach(skel); }
void measure_bpf::detach(struct measure_bpf *skel) { measure_bpf__detach(skel); }
void measure_bpf::destroy(struct measure_bpf *skel) { measure_bpf__destroy(skel); }
const void *measure_bpf::elf_bytes(size_t *sz) { return measure_bpf__elf_bytes(sz); }
#endif /* __cplusplus */

__attribute__((unused)) static void
measure_bpf__assert(struct measure_bpf *s __attribute__((unused)))
{
#ifdef __cplusplus
#define _Static_assert static_assert
#endif
#ifdef __cplusplus
#undef _Static_assert
#endif
}

#endif /* __MEASURE_BPF_SKEL_H__ */
