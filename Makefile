.PHONY: build test check_before check_after check_coverage memtest_sanitizers memtest_valgrind clean

check_before_build:
	./linters/check_before_build.sh

build:
	./build.sh

check_object_files: build
	./linters/check_object_files.sh
	
test:
	cd DoIt && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd DoIt/build && ctest
	@cd DoIt/build && lcov -t "tests/tests.cpp" -o coverage.info -c -d database/> /dev/null
	@cd DoIt/build && genhtml -o report coverage.info > coverage_database.txt 

check_coverage:	
	@chmod +x run_coverage.sh & ./run_coverage.sh

memtest_valgrind:
	cd DoIt && mkdir -p build && cd build && cmake .. && cmake --build .
	valgrind --tool=memcheck --leak-check=full --leak-resolution=med --track-origins=yes --xml=yes --xml-file=unit_tests_valgrind.xml ./DoIt/build/tests/test_module
	./check_valgrind_report.sh

memtest_sanitizers:
	cd DoIt && mkdir -p build && cd build && cmake -DMEM_MOD=ON .. && cmake --build .

clean:
	rm -rf DoIt/build unit_tests_valgrind.xml
