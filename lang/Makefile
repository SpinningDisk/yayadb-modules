cc=gcc
ar = ar
ld = ld.lld

BuildLoc = build
LexerSrc = src
LexerName  = lex
SocketSrc = src
SocketName = socket
VMSrc = src
VMName = vm
ParserSrc = src
ParserName = main

# always compile static. compile shared yourself if you want. I don't

.PHONY: build debug clean
clean:
	rm -rf $(BuildLoc)/
	mkdir -p $(BuildLoc)/
	mkdir -p $(BuildLoc)/lib
	mkdir -p $(BuildLoc)/tmp

build:
# compilation
	$(cc) -c $(LexerSrc)/$(LexerName).c -o $(BuildLoc)/tmp/$(LexerName).o -Wall -Wextra -lpcre
	$(cc) -c $(SocketSrc)/$(SocketName).c -o $(BuildLoc)/tmp/$(SocketName).o -Wall -Wextra
	$(cc) -c $(VMSrc)/$(SocketName).c -o $(BuildLoc)/tmp/$(VMName).o -Wall -Wextra
# linking
#	$(cc) -fuse-ld=lld $(BuildLoc)/tmp/$(LexerName).o -lpcre -o $(BuildLoc)/tmp/$(LexerName).linked.o
# assembling
	$(ar) rcs $(BuildLoc)/lib/liblang.a $(BuildLoc)/tmp/$(LexerName).o $(BuildLoc)/tmp/$(SocketName).o $(BuildLoc)/tmp/$(VMName).o
# compilation of parser
	$(cc) -o $(BuildLoc)/$(ParserName) $(ParserSrc)/$(ParserName).c -Wall -Wextra -Iinclude/ -Lbuild/lib/ -lpcre -llang