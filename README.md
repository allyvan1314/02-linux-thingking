# TỔNG QUAN VỀ UNIX/LINUX

----

- [TỔNG QUAN VỀ UNIX/LINUX](#t%E1%BB%95ng-quan-v%E1%BB%81-unixlinux)
  - [1. Định nghĩa Unix/Linux](#1-%C4%91%E1%BB%8Bnh-ngh%C4%A9a-unixlinux)
  - [2. Cấu trúc Unix/Linux](#2-c%E1%BA%A5u-tr%C3%BAc-unixlinux)
  - [3. Khởi động hệ thống trong Unix/Linux](#3-kh%E1%BB%9Fi-%C4%91%E1%BB%99ng-h%E1%BB%87-th%E1%BB%91ng-trong-unixlinux)
  - [4. Đăng nhập Unix/Linux](#4-%C4%91%C4%83ng-nh%E1%BA%ADp-unixlinux)
  - [5. Đăng nhập hệ thống Unix/Linux](#5-%C4%91%C4%83ng-nh%E1%BA%ADp-h%E1%BB%87-th%E1%BB%91ng-unixlinux)
  - [6. Thay đổi mật khẩu trong Unix/Linux](#6-thay-%C4%91%E1%BB%95i-m%E1%BA%ADt-kh%E1%BA%A9u-trong-unixlinux)
  - [7. Liệt kê thư mục và file trong Unix/Linux](#7-li%E1%BB%87t-k%C3%AA-th%C6%B0-m%E1%BB%A5c-v%C3%A0-file-trong-unixlinux)
  - [8. Lệnh whoami trong Unix/Linux](#8-l%E1%BB%87nh-whoami-trong-unixlinux)
  - [9. Ai đã đăng nhập trong Unix/Linux](#9-ai-%C4%91%C3%A3-%C4%91%C4%83ng-nh%E1%BA%ADp-trong-unixlinux)
  - [10. Đăng xuất trong Unix/Linux](#10-%C4%91%C4%83ng-xu%E1%BA%A5t-trong-unixlinux)
  - [11. Để thoát khỏi chương trình](#11-%C4%91%E1%BB%83-tho%C3%A1t-kh%E1%BB%8Fi-ch%C6%B0%C6%A1ng-tr%C3%ACnh)
  - [12. Đóng hệ thống trong Unix/Linux](#12-%C4%91%C3%B3ng-h%E1%BB%87-th%E1%BB%91ng-trong-unixlinux)

----

## 1. Định nghĩa Unix/Linux

Hệ điều hành Unix là tập hợp các chương trình mà thực hiện vai trò như một đường link giữa máy tính và người sử dụng.

Các chương trình máy tính phân cấp các nguồn hệ thống và phối hợp tất cả các phần bên trong của máy tính được gọi là Hệ điều hành hoặc kernel (hạt nhân).

Những người sử dụng giao tiếp với kernel thông qua một chương trình mà được biết như là shell. Shell là một bộ biên dịch dòng lệnh, nó biên dịch các lệnh được nhập bởi người sử dụng và chuyển đổi chúng thành một ngôn ngữ mà kernel có thể hiểu.

Unix/Linux được phát triển lần đầu tiên bởi một nhóm các nhân viên AT&T tại phòng thí nghiệm Bell Labs, gồm có Ken Thompson, Dennis Ritchie, Douglas Mclloy và Joe Ossanna.

Có rất nhiều phiên bản Unix khác nhau trên thị trường. Solaris Unix, AIX, HP Unix và BSD là một số ví dụ. Linux cũng là một phiên bản của Unix mà là miễn phí.

Nhiều người có thể sử dụng một máy tính Unix cùng một lúc; vì thế Unix được gọi là hệ thống đa người dùng.

Một người sử dụng có thể chạy nhiều chương trình cùng một lúc; vì thế Unix được gọi là đa nhiệm.

## 2. Cấu trúc Unix/Linux

Sơ đồ dưới là cấu trúc của một hệ thống Unix:

<p align = "center">
    <img src = "https://vietjack.com/unix/images/cau_truc_he_thong_unix_linux.jpg">
    <br/>
</p>

Khái niệm chính mà được thống nhất trong tất cả các phiên bản Unix gồm 4 cơ sở sau:

* **Kernel:** Kernel là trái tim của hệ điều hành. Nó tương tác với phần cứng và hầu hết nhiệm vụ như quản lý bộ nhớ, quản lý file, lên chương trình nhiệm vụ.
* **Shell:** Shell là một tiện ích mà xử lý các yêu cầu của bạn. Khi bạn gõ một lệnh tại terminal của bạn, shell biên dịch lệnh đó và gọi chương trình mà bạn muốn. Shell sử dụng cú pháp chuẩn cho tất cả các lệnh. C Shell, Bourne Shell và Korn Shell là những shell được biết đến nhiều nhất và có sẵn trong hầu hết các phiên bản Unix.
* **Các lệnh và các tiện ích:** Có rất nhiều lệnh và tiện ích mà bạn có thể sử dụng trong công việc hàng ngày. cp, mv, cat và grep … là một số ví dụ của lệnh và tiện ích. Có trên 250 lệnh tiêu chuẩn cộng với một số lệnh khác được cung cấp bởi phần mềm thứ 3. Tất cả các lệnh này đi cùng với các tùy chọn (chức năng) của nó.
* **File và thư mục:** Tất cả dữ liệu trong Unix được tổ chức trong các file. Tất cả các file được tổ chức vào trong các thư mục. Những thư mục này được tổ chức trong một cấu trúc dạng cây được gọi như là hệ thống file.

## 3. Khởi động hệ thống trong Unix/Linux

Nếu bạn có một máy tính mà đã cài đặt hệ điều hành Unix trên đó, thì sau đó đơn giản bạn chỉ cần bật để khởi động hệ thống.

Ngay sau khi bạn bật hệ thống, hệ thống bắt đầu khởi động và cuối cùng nó nhắc bạn đăng nhập vào trong hệ thống, mà hành động đăng nhập này được sử dụng cho các hoạt động thường ngày.

## 4. Đăng nhập Unix/Linux

Khi bạn lần đầu kết nối với một hệ thống Unix, bạn thường nhìn thấy một dòng nhắc như sau:

>login:

## 5. Đăng nhập hệ thống Unix/Linux

1. Chuẩn bị sẵn sàng ID sử dụng và mật khẩu. Liên hệ với người quản lý nếu bạn chưa có nó.
2. Nhập ID tại dòng nhắc đăng nhập, sau đó nhấn Enter. ID của bạn là phân biệt chữ hoa-thường, vì thế chắc chắn rằng bạn đã nhập chính xác như người quản lý đã chỉ dẫn.
3. Nhập mật khẩu vào ô mật khẩu và nhấn Enter. Mật khẩu của bạn cũng phân biệt kiểu chữ.
4. Nếu bạn cung cấp ID và mật khẩu chính xác thì sau đó bạn sẽ được cho phép để vào hệ thống. Bạn đọc qua thông tin và các thông báo mà hiện trên màn hình như hình dưới đây:

```scala
login : amrood
amrood's password:
Last login: Sun Jun 14 09:32:32 2009 from 62.61.164.73
$
```

Bạn sẽ được cung cấp với một lệnh nhắc (đôi khi được gọi là lệnh $) mà tại đó bạn sẽ nhập tất cả các lệnh của bạn. Ví dụ để kiểm tra lịch, bạn cần nhập lệnh cal như sau:

```scala
$ cal
December 2015
Su Mo Tu We Th Fr Sa
       1  2  3  4  5
 6  7  8  9 10 11 12
13 14 15 16 17 18 19
20 21 22 23 24 25 26
27 28 29 30 31
$
```

## 6. Thay đổi mật khẩu trong Unix/Linux

Tất cả các hệ điều hành Unix đều yêu cầu mật khẩu để đảm bảo cho các dữ liệu và file của bạn và cũng đảm bảo an toàn cho chính hệ thống chống lại sự thâm nhập của hacker hoặc cracker. Dưới đây là các bước để thay đổi mật khẩu:

1. Để bắt đầu, soạn passwd tại dòng nhắc lệnh như hình dưới.
2. Nhập mật khẩu cũ
3. Nhập mật khẩu mới mà bạn muốn đổi. Luôn luôn giữ cho mật khẩu càng phức tạp càng tốt để mà không ai có thể đoán được nó. Nhưng chắc chắn rằng bạn nhớ nó.
4. Bạn cần xác nhận lại mật khẩu bằng cách nhập nó thêm lần nữa.

```scala
$ passwd
Changing password for amrood
(current) Unix password:******
New UNIX password:*******
Retype new UNIX password:*******
passwd: all authentication tokens updated  successfully
$
```

* **Ghi chú:** Tôi đã đặt dấu * vào vị trí chỉ cho bạn địa điểm bạn cần nhập mật khẩu cũ và mới. Ngoài ra tại hệ thống của bạn, nó sẽ không hiển thị bất cứ ký tự nào khi bạn gõ mật khẩu vào.

## 7. Liệt kê thư mục và file trong Unix/Linux

Tất cả dữ liệu trong Unix được tổ chức vào trong các file. Tất cả các file được tổ chức vào trong các thư mục. Những thư mục này được tổ chức vào trong một cấu trúc cây được gọi là hệ thống file.

Bạn có thể sử dụng lệnh ls để liệt kê tất cả các file hoặc thư mục có trong một thư mục. Dưới đây là ví dụ về cách sử dụng lệnh ls với tùy chọn -l.

```scala
$ ls -l
total 19621
drwxrwxr-x  2 amrood amrood      4096 Dec 25 09:59 uml
-rw-rw-r--  1 amrood amrood      5341 Dec 25 08:38 uml.jpg
drwxr-xr-x  2 amrood amrood      4096 Feb 15  2006 univ
drwxr-xr-x  2 root   root        4096 Dec  9  2007 urlspedia
-rw-r--r--  1 root   root      276480 Dec  9  2007 urlspedia.tar
drwxr-xr-x  8 root   root        4096 Nov 25  2007 usr
-rwxr-xr-x  1 root   root        3192 Nov 25  2007 webthumb.php
-rw-rw-r--  1 amrood amrood     20480 Nov 25  2007 webthumb.tar
-rw-rw-r--  1 amrood amrood      5654 Aug  9  2007 yourfile.mid
-rw-rw-r--  1 amrood amrood    166255 Aug  9  2007 yourfile.swf

$
```

Ở đây, các kết quả mà bắt đầu với d…… biểu diễn các thư mục. Ví dụ như uml, univ và urlspedia là các thư mục và phần còn lại là file.

## 8. Lệnh whoami trong Unix/Linux

Trong khi bạn đăng nhập vào hệ thống, bạn có thể sẵn lòng để biết: Who am I?

Cách đơn giản nhất là tìm kiếm "bạn là ai" là nhập lệnh whoami:

```cpp
$ whoami
 amrood

$
```

Hãy thử nó trên hệ thống của mình. Lệnh này liệt kê các tên tài khoản liên kết với sự đăng nhập hiện tại. Bạn có thể thử lệnh whoami cũng để nhận thông tin về chính mình.

## 9. Ai đã đăng nhập trong Unix/Linux

Đôi khi bạn có thể muốn biết ai đã đăng nhập vào máy tính trong cùng thời gian.

Có 3 lệnh có sẵn để giúp bạn nhận được thông tin này, dựa trên cơ sở bạn muốn biết bao nhiêu về những người sử dụng khác: users, who và w.

```scala
$ users
 amrood bablu qadir

$ who
amrood ttyp0 Oct 8 14:10 (limbo)
bablu  ttyp2 Oct 4 09:08 (calliope)
qadir  ttyp4 Oct 8 12:09 (dent)

$
```

Bạn hãy thử lệnh w trên hệ thống của bạn để kiểm tra kết quả. Lệnh này sẽ liệt kê một số thông tin liên quan tới người đăng nhập vào trong hệ thống.

## 10. Đăng xuất trong Unix/Linux

Khi bạn đã kết thúc phiên làm việc của mình, bạn cần thoát khỏi chương trình để đảm bảo rằng không ai có thể truy cập vào các file của bạn khi họ giả trang bạn.

## 11. Để thoát khỏi chương trình

Bạn chỉ cần gõ lệnh logout tại dòng lệnh nhắc, và hệ thống sẽ vệ sinh mọi thứ và ngắt kết nối.

## 12. Đóng hệ thống trong Unix/Linux

Cách phù hợp nhất để đóng hệ thống Unix là thông qua sử dụng một trong các lệnh sau:

|Lệnh|Miêu tả|
|-----|------|
|halt|Đóng hệ thống ngay lập tức.|
|init 0|Đóng hệ thống sử dụng script được xác định trước để đồng bộ và vệ sinh hệ thống trước khi shutdown.|
|init 6|Khởi động lại hệ thống bằng cách đóng hệ thống ngay lập tức và sau đó bắt đầu lại như lúc trước khi đóng.|
|poweroff|Đóng hệ thống ở chế độ poweroff|
|reboot|Khởi động lại hệ thống|
|shutdown|Đóng hệ thống|