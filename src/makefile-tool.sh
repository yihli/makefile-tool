#!/bin/bash

# list all the cpp files in files array.
print_files() {

	#list number
	count=1

	echo Listing files...
	for i in "${files[@]}"
	do
		echo $count')' "$i"
		((count++))
	done
}

# store all the cpp files found in the directory in an array
get_files() {

	input=$(ls "$directory")

	# need to fix double quote error from shellcheck here
	for i in ${input[@]}
	do
		if [[ $i =~ ^(.*\.cpp)$ ]]; then
			files+=("$i")
		fi
	done
}

# verifies given directory exists
check_argument() {
	if ! [ -d "$directory" ]; then
		echo \["$directory"\] is not a valid directory. 
		echo Usage: bash makefile-tool.sh \[directory\]
		exit 1
	fi
}

files=()
directory=$1

if [ $# -ne 1 ]; then
	echo No argument specified or too many specified. 
	echo Usage: bash makefile-tool.sh \"directory\"
	exit 1
fi

check_argument 
get_files
print_files
