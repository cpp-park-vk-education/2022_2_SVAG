test:
	cd DoIt && mkdir -p build && cd build && cmake -DTEST_MODE=ON .. && cmake --build .
	cd DoIt/build && ctest
	@cd DoIt/build && lcov -t "tests/tests.cpp" -o coverage.info -c -d database/> /dev/null
	@cd DoIt/build && genhtml -o report coverage.info > coverage_database.txt 

check_coverage:	
	@./run_coverage.sh