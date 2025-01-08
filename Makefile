# You can change these variables if you want to use a different compiler or debugger
CC = gcc
DBG = gdb

# We use .PHONY to tell make to always run these commands even if a file exists
# with the same name in this directory. For more information on .PHONY, see
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: build-main
build-main: build-dir
	$(CC) -Wall -O0 -g -o build/main.o src/main.c src/lib.c src/memory.c -lm

.PHONY: check
check:
	@which $(CC) > /dev/null && echo "SUCCESS: $(CC) is installed" || echo "ERROR: $(CC) not found, please install clang"
	@which $(DBG) > /dev/null && echo "SUCCESS: $(DBG) is installed" || echo "ERROR: $(DBG) not found, please install lldb"

.PHONY: build-dir
build-dir:
	if [ ! -d build ]; then mkdir build; fi

.PHONY: build-test
build-test: build-dir
	$(CC) -Wall -O0 -g -o build/test.o src/test.c -lm

.PHONY: run
run: build-main
	./build/main.o config

.PHONY: test
test: build-test
	./build/test.o

.PHONY: debug
debug: build-main
	$(DBG) ./build/main.o

.PHONY: debug-test
debug-test: build-test
	$(DBG) ./build/test.o
