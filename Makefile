memtest: build
	valgrind --tool=memcheck --leak-check=full --leak-resolution=med --track-origins=yes ./Doit/build/tests/test_module