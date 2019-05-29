#!/bin/bash

echo "Chuong trinh dem so dong cua code!!"

echo "Nhap ten file:"
read filename

if [ ! -f "$filename" ]; then
    echo "$filename not exists!!"
    exit 1 
fi

n1=$(grep -v "[a-Z]" $filename | grep -v "{" | grep -v "}" | wc -l)
echo "So dong trong la: $n1"

n2=$(grep -v "[a-Z]" $filename | wc -l)
n2=$((n2-n1))
echo "So dong chi chua ky tu dac biet (khong chua code) la: $n2"

#chỉ chứa comment k chứa code
n3=$(grep -c "^\s*//" $filename)

n4=$(grep -c "//" $filename)
echo "So dong chua comment la: $n4"

n5=$(grep -c "[a-Z]" $filename)
n5=$((n5-n3))
echo "So dong chua code la: $n5"