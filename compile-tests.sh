#!/bin/bash -eu

for file in ./tests/*.c
do
	testname="$(basename $file | cut -d '.' -f 1)"

	printf "Compiling test '$testname' ... "

	gcc \
		-Wall \
		-Wpedantic \
		-D_FORTIFY_SOURCE=2 \
		./src/*.c \
		"$file" \
		-o "./bin/$testname"

	printf "ok \n"
done
