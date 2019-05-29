#!/bin/bash

echo "Chuong trinh tinh tong cac so trong 1 file cho truoc!!"
echo "Nhap ten file: "
read filename

# kiểm tra tên file có tồn tại
if [ ! -f "$filename" ]; then
    echo "$filename not exists!!"
    exit 1 
fi

a=$(awk '{sum+=$1} END {print(sum)}' $filename)
echo "C1: Tong cac so trong file $filename la: $a"

echo "Thoi gian thuc hien c1:"
time awk '{sum+=$1} END {print(sum)}' $filename

b=$(paste -sd+ $filename | bc)
echo "C2: Tong cac so trong file $filename la: $b"

echo "Thoi gian thuc hien c2:"
time paste -sd+ $filename | bc

exit 0