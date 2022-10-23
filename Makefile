check_before:
	./linters/check_before.sh

check_after: build
	./linters/check_after.sh