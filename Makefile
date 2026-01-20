

.PHONY: clean build run

build:
	echo "building..."
	cd protocol; mkdir -p .cmake build/lib build/bin; cmake -S ./ -B ./.cmake; cd .cmake; make;

run:
	make build
	echo "running..."
	protocol/build/bin/test