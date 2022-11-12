<<<<<<< HEAD
.PHONY: build test check_before check_after check_coverage memtest clean

check:
	./linters/check_before_build.sh

build:
	./build.sh

check_after: build
	./linters/check_object_files.sh
	
clean:
	rm -rf DoIt/build
=======
test:
	cd DoIt && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd DoIt/build && ctest
	@cd DoIt/build && lcov -t "tests/tests.cpp" -o coverage.info -c -d database/> /dev/null
	@cd DoIt/build && genhtml -o report coverage.info > coverage_database.txt 

check_coverage:	
	@./run_coverage.sh
>>>>>>> origin/test_ci
.PHONY: build test check_before check_after check_coverage memtest clean

check:
	./linters/check_before_build.sh

build:
	./build.sh

check_after: build
	./linters/check_object_files.sh
	
test:
	cd DoIt && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd DoIt/build && ctest
	@cd DoIt/build && lcov -t "tests/tests.cpp" -o coverage.info -c -d database/> /dev/null
	@cd DoIt/build && genhtml -o report coverage.info > coverage_database.txt 

check_coverage:	
	@./run_coverage.sh

clean:
	rm -rf DoIt/build
