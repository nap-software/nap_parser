#!/bin/bash -u

mkdir -p bin/

./compile-tests.sh

if [ "$?" -eq 0 ]; then
	printf "\033[1;32mAll tests compiled successfully.\033[0;0m\n"
else
	printf "\033[1;31mError compiling some of the tests\033[0;0m\n"
	exit 1
fi

for file in ./bin/*
do
	testname="$(basename $file | cut -d '.' -f 1)"

	printf "Running test '$testname' ... "

	valgrind \
		--leak-check=full \
		--error-exitcode=3 \
		--exit-on-first-error=yes \
		"$file" 1>/dev/null 2>/dev/null

	if [ "$?" -eq 0 ]; then
		printf "\033[1;32mok\033[0;0m\n"
	else
		printf "\033[1;31merror\033[0;0m\n"
	fi
done
