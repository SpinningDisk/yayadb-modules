cc=gcc
ar = ar
ld = ld.lld

BuildLoc = build
SocketSrc = src
SocketName = socket
ProtocolSrc = src
ProtocolName = proto
TestSrc = src
TestName = test

PythonFlags := $(shell python3-config --cflags)
PythonLdFlags := $(shell python3-config --ldflags)

# always compile static. compile shared yourself if you want. I don't

.PHONY: build clean test
clean:
	rm -rf $(BuildLoc)/
	mkdir -p $(BuildLoc)/
	mkdir -p $(BuildLoc)/lib
	mkdir -p $(BuildLoc)/tmp

build:
# compilation
	$(cc) -c $(SocketSrc)/$(SocketName).c -o $(BuildLoc)/tmp/$(SocketName).o -Wall -Wextra
	$(cc) -c $(ProtocolSrc)/$(ProtocolName).c -o $(BuildLoc)/tmp/$(ProtocolName).o -Wall -Wextra $(PythonFlags)

# assembling
	$(ar) rcs $(BuildLoc)/lib/libprotocol.a $(BuildLoc)/tmp/$(SocketName).o $(BuildLoc)/tmp/$(ProtocolName).o

test:
	make build
# Compile and link test.c (includes proto.h and Python.h)
	$(cc) $(TestSrc)/$(TestName).c $(BuildLoc)/lib/libprotocol.a \
    $(shell python3-config --includes) \
    $(shell python3-config --embed --ldflags) \
    -o $(BuildLoc)/$(TestName)
