.PHONY: build test check_before check_after check_coverage memtest clean

check:
	./linters/check_before_build.sh

build:
	./build.sh

check_after: build
	./linters/check_object_files.sh
	
clean:
	rm -rf DoIt/build
