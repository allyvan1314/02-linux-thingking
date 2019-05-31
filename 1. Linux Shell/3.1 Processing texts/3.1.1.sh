#!/bin/bash

echo "Chuong trinh dem so dong cua 1 tap tin chua menh de cho truoc!!"
echo "Nhap ten file: "
read filename

# kiểm tra tên file có tồn tại
if [ ! -f "$filename" ]; then
    echo "$filename not exists!!"
    exit 1 
fi

echo "Nhap chuoi can tim: "
read pattern

n1=$(egrep -o $pattern $filename | wc -l)
echo "So lan xuat hien $pattern tron $filename la $n1!"

# đếm số dòng xuất hiện $pattern trong $filename
n=$(grep -c $pattern $filename)
echo "So dong chua $pattern trong $filename la $n!"

exit 0