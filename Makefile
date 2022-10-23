.PHONY: build test check_before check_after check_coverage memtest clean

build:
	./build.sh

clean:
	rm -rf DoIt/build
