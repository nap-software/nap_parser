#!/bin/bash -eux

rm -rf obj release
mkdir -p obj release

for file in ./src/*.c
do
	filename="$(basename $file | cut -d '.' -f 1)"

	gcc \
		-Wall \
		-Wpedantic \
		-c \
		-o "./obj/$filename.o" \
		"$file"
done

ar rcs ./release/libnap_parser.a obj/*.o
cp ./src/nap_parser.h ./release/
