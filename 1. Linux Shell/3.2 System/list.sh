#!/bin/bash

echo "List cac file co size tren 100k"
echo "Hay nhap duong dan toi file can list: "
read path

#if [ ! -f $path ]; then
#    echo "$path not exists!!"
#    exit 1
#fi

files=$(find $path -size +100k)

echo "----------------------LIST OF FILES---------------------------"

for file in $files
do
    echo $file
done

echo "--------------------------------------------------------------"
printf "Would you like to...\n1. Delete all files\n2. Compress all files\n3. Cancel\n"
printf "Enter your selected number: " 
read choice

case $choice in
	1)
	rm $files
	;;
	2)
	cmd="tar -zcvf files.tar.gz"
	for file in $files
	do
		filename=$(basename $file)
		parent=$(dirname $file)
		cmd+=" -C $parent $filename"
	done
    echo "$cmd"
	echo "--------------------------------------------------------------"
	echo "Result:"
	$cmd
	;;
	*)
	echo "Cancelled"
	;;
esac

exit 0