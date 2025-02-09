TARGET = build/measure
ARCH = $(shell uname -m | sed 's/x86_64/x86/' | sed 's/aarch64/arm64/')

BPF_OBJ = ${TARGET:=.bpf.o}
USER_C = src/main.c
USER_SKEL = src/measure.skel.h

.PHONY: all 

$(TARGET): $(USER_C) $(USER_SKEL) 
	gcc -Wall -o $(TARGET) $(USER_C) src/lib.c src/memory.c -lm -l:libbpf.a -lelf -lz
#	gcc -Wall -o $(TARGET) $(USER_C) -L../libbpf/src -l:libbpf.a -lelf -lz

build/measure.bpf.o: src/measure.bpf.c src/vmlinux.h
	clang \
	    -target bpf \
        -D __TARGET_ARCH_$(ARCH) \
	    -Wall \
	    -O2 -g -o $@ -c $<

$(USER_SKEL): $(BPF_OBJ)
	bpftool gen skeleton $< > $@

src/vmlinux.h:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > src/vmlinux.h

clean:
	- rm $(BPF_OBJ)
	- rm $(TARGET)
	- rm src/vmlinux.h

.PHONY: run
run: $(TARGET)
	./build/measure config
