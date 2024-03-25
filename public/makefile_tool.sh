#!/bin/bash

check_for_main() {
	found=false
	exec_name=$1

	echo $exec_name

	# read line by line to look for int main 
	while IFS= read -r line; do
		if [[ $line =~ ^[[:space:]]*int[[:space:]]*main[[:space:]]*\(.*\) ]]; then
			echo Int main was found. Connecting headers...
			found=true
			./find_includes $directory$chosen_file ${exec_name}
		fi
	done < $directory$chosen_file

	# int main not found
	if ! [[ found ]]; then
		echo The specified .cpp file does not contain int main. Exiting...
		exit 1
	fi
}

prompt() {
	exec_names=()

	read -p "Please enter a name for your executable: " name
	exec_names+=($name)

	echo Your executable will be named \"${name}\"
	
	read -r -p "Please specify which .cpp file contains \"int main()\": " chosen_file

	# if there was no user input
	if [[ -z "$chosen_file" ]]; then
		echo No file was specified. Exiting...
		exit 1
	fi

	check_for_main ${name}
}

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
	
	for i in ${input[@]}
	do
		if [[ $i =~ ^(.*\.cpp)$ ]]; then
			files+=("$i")
		fi
	done

	# if nothing was read to the files array
	if [[ ${#files[@]} =~ 0 ]]; then
		echo No .cpp files were found in \""$directory"\" 
		echo Did you specify the right directory?
		exit 1
	fi	
}

# verifies given directory exists
check_argument() {
	# -d checks if a directory exists 
	if ! [ -d "$directory" ]; then
		echo \["$directory"\] is not a valid directory. 
		echo Usage: bash makefile-tool.sh \[directory\]
		exit 1
	fi
}

files=()
directory=$1

# if the number of arguments is not one
if [ $# -ne 1 ]; then
	echo No argument specified or too many specified. 
	echo Usage: bash makefile-tool.sh \"directory\"
	exit 1
fi

check_argument 
get_files
print_files
prompt



