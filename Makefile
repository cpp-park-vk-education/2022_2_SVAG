check:
	./linters/check_before_build.sh

check_after: build
	./linters/check_object_files.sh
	