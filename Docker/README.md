# DOCKER

1. Nắm được khái niệm về container.
2. Hiểu cách hoạt động của Docker.
3. Làm quen với các lệnh cơ bản của Docker
4. Viết được Dockerfile cơ bản.

## 1. CONTAINERLIZATION LÀ GÌ

Ngày lâu lâu rồi, mô hình máy chủ thường là ``máy chủ vật lý`` + `hệ điều hành(OS)` + `application`.

<p align="center">
  <img src="https://viblo.asia/uploads/19a271ca-f444-4bd5-b04a-f1b9c5ce10fd.png">
  <br/>
</p>

Vấn đề gặp phải ở đây là lãng phí tài nguyên, một máy chủ chỉ cài được một OS, cho dù có ổ cứng khủng, ram khủng thì cũng không tận dụng hết lợi thế.

Sau đó ra đời công nghệ ảo hóa `vitualization.`

<p align="center">
  <img src="https://viblo.asia/uploads/f83e4a3a-bc95-4a4d-af37-dbaa9e03d28f.png">
  <br/>
</p>

Bạn có thể đã nghe tới cái tên Vitualbox hay VMware rồi đúng không, đó đó chính nó đó. Với công nghệ này, trên một máy chủ vật lý mình có thể tạo được nhiều OS, tận dụng tài nguyên đã tốt hơn nhưng lại nảy sinh vấn đề tiếp.

* `Về tài nguyên:` Khi bạn chạy máy ảo, bạn phải cung cấp "cứng" `dung lượng ổ cứng` cũng như ram cho máy ảo đó, bật máy ảo lên để đó không làm gì thì máy thật cũng phải phân phát tài nguyên.

        Ví dụ khi tạo một máy ảo ram 2GB trên máy thật ram 4GB, lúc này máy thật sẽ mất 2GB ram cho máy ảo, kể cả khi máy ảo không dùng hết 2GB ram, đó là một sự lãng phí.

* `Về thời gian:` Việc khởi động, shutdown khá lâu, có thể lên tới hàng phút.

Ở bước tiến hóa tiếp theo, người ta sinh ra công nghệ `containerlization`

<p align="center">
  <img src="https://viblo.asia/uploads/5fdfbb3b-de87-4b24-a65c-3cf8753bfa15.png">
  <br/>
</p>

Với công nghệ này, trên một máy chủ vật lý, ta sẽ sinh ra được nhiều máy con (giống với công nghệ ảo hóa `vitualization`), nhưng tốt hơn ở chỗ là các máy con này (Guess OS) đều `dùng chung` phần nhân của máy mẹ (Host OS) và chia sẻ với nhau tài nguyên máy mẹ.

Có thể nói là khi nào cần tài nguyên thì được cấp, cần bao nhiêu thì cấp bấy nhiêu, như vậy việc tận dụng tài nguyên đã tối ưu hơn. Điểm nổi bật nhất của `containerlization` là nó sử dụng các `container`, và một kĩ sư của Google đã phát biểu rằng:

<p align="center">
  <img src="https://viblo.asia/uploads/d68c3328-bfee-41a7-add0-6e38ed98f9f3.png">
  <br/>
</p>

## 2. CONTAINER LÀ GÌ

Các phần mềm, chương trình sẽ được Container Engine ( là một công cụ ảo hóa tinh gọn được cài đặt trên host OS) đóng gói thành các container.

Vậy Container là một giải pháp để chuyển giao phần mềm một cách đáng tin cậy giữa các môi trường máy tính khác nhau bằng cách:

* Tạo ra một môi trường chứa mọi thứ mà phần mềm cần để có thể chạy được.
* Không bị các yếu tố liên quan đến môi trường hệ thống làm ảnh hưởng tới.
* Cũng như không làm ảnh hưởng tới các phần còn lại của hệ thống.
* Bạn có thể hiểu là ruby, rails, mysql ... kia được bỏ gọn vào một hoặc nhiều cái thùng (container), ứng dụng của bạn chạy trong những chiếc thùng đó, đã có sẵn mọi thứ cần thiết để hoạt động, không bị ảnh hưởng từ bên ngoài và cũng không gây ảnh hưởng ra ngoài.

Các tiến trình (process) trong một container bị cô lập với các tiến trình của các container khác trong cùng hệ thống tuy nhiên tất cả các container này đều chia sẻ kernel của host OS (dùng chung host OS).

Đây một nền tảng mở dành cho các lập trình viên, quản trị hệ thống dùng để xây dựng, chuyển giao và chạy các ứng dụng dễ dàng hơn. Ví dụ, bạn có một app java, bạn sẽ không cần cài đặt JDK vào máy thật để chạy app đó, chỉ cần kiếm container đã được setting tương ứng cho app về, bật nó lên, cho app chạy bên trong môi trường container đó, vậy là ok. Khi không sài nữa thì tắt hoặc xóa bỏ container đó đi, không ảnh hưởng gì tới máy thật của bạn.

* Ưu điểm:
  * Linh động: Triển khai ở bất kỳ nơi đâu do sự phụ thuộc của ứng dụng vào tầng OS cũng như cơ sở hạ tầng được loại bỏ.
  * Nhanh: Do chia sẻ host OS nên container có thể được tạo gần như một cách tức thì. Điều này khác với vagrant - tạo môi trường ảo ở level phần cứng, nên khi khởi động mất nhiều thời gian hơn.
  * Nhẹ: Container cũng sử dụng chung các images nên cũng không tốn nhiều disks.
  * Đồng nhất :Khi nhiều người cùng phát triển trong cùng một dự án sẽ không bị sự sai khác về mặt môi trường.
  * Đóng gói: Có thể ẩn môi trường bao gồm cả app vào trong một gói được gọi là container. Có thể test được các container. Việc bỏ hay tạo lại container rất dễ dàng.
* Nhược điểm:
  * Xét về tính an toàn:
    * Do dùng chung OS nên nếu có lỗ hổng nào đấy ở kernel của host OS thì nó sẽ ảnh hưởng tới toàn bộ container có trong host OS đấy.
    * Ngoài ra hãy thử tưởng tượng với host OS là Linux, nếu trong trường hợp ai đấy hoặc một ứng dụng nào đấy có trong container chiếm được quyền superuser, điều gì sẽ xảy ra? Về lý thuyết thì tầng OS sẽ bị crack và ảnh hưởng trực tiếp tới máy host bị hack cũng như các container khác trong máy đó (hacker sử dụng quyền chiếm được để lấy dữ liệu từ máy host cũng như từ các container khác trong cùng máy host bị hack chẳng hạn).

## 3. DOCKER RA ĐỜI

Công nghệ ảo hóa (vitualization) thì ta có thể dùng công cụ Vitualbox hay VMware thế còn đối với containerlization thì dùng gì đây ? Google họ dùng gì ?

Oh mình không biết được, mỗi một ông lớn có một cách để áp dụng công nghệ này và họ private source code.

Gần đây, có một công ty tiến hành public source code của họ về công nghệ này, họ tung ra sản phẩm mang tên là Docker và nhận được nhiều sự chú ý.

<p align="center">
  <img src="https://viblo.asia/uploads/5b1bb3b4-f3b8-4183-853a-d11f0f4a4997.png">
  <br/>
</p>

Sau đó công ty cũng đổi tên thành Docker luôn. Công ty này cung cấp công cụ Docker free nhưng họ kiếm được rất nhiều tiền từ những dịch vụ khác đi kèm với nó.

Với sự bùng nổ của việc sử dụng container cùng với những lợi ích lớn mà nó mang lại, gã khổng lồ phần mềm Microsoft không muốn bỏ qua cơ hội màu mỡ này với việc cho ra mắt tính năng mới có tên Windows Container.

## 4. CÀI ĐẶT DOCKER

* Docker hỗ trợ nhiều nền tảng hệ điều hành khác nhau bao gồm Linux, Windows và cả Mac. Ngoài ra, Docker còn hỗ trợ nhiều dịch vụ điện toán đám mây nổi tiếng như Microsoft Azure hay Amazon Web Services.
* Lưu ý là ban đầu nó được xây dựng trên nền tảng Linux. Vì Docker cần can thiệp vào phần lõi, nhân Kernel trong khí đó Linux là mã nguồn mở, gọi là cần gì có nấy.
* Đến khi thấy Docker hay quá, bác Windows ngỏ lời, thế là công ty Docker và công ty Microsoft hợp tác với nhau nhưng nghe chừng chưa khả quan lắm bởi vì nhân Windows có nhưng thứ không public được ( bản quyền mà ).
* Cho tới hiện tại khi cài Docker trên Windows hay Mac thì Docker sẽ cài một máy ảo Linux trên máy thật và Docker hoạt động dựa trên máy ảo Linux đó. Còn tương lai về sau thì ai biết được.
* Docker có 2 phiên bản, CE( dành cho nhà phát triển, nhóm nhỏ, coder như chúng ta) và EE (dành cho doanh nghiệp).

Dưới đây mình sẽ giới thiệu cài đặt đối với bản CE trên Ubuntu thông qua repository như sau:

```bash
I. Chuẩn bị một chút:

# Update the apt package index:
$ sudo apt-get update

# Install packages to allow apt to use a repository over HTTPS:
$ sudo apt-get install \
   apt-transport-https \
   ca-certificates \
   curl \
   software-properties-common

# Add Docker’s official GPG key:
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -


# Verify that you now have the key with the fingerprint 9DC8 5822 9FC7 DD38 854A E2D8 8D81 803C 0EBF CD88, by searching for the last 8 characters of the fingerprint.
$ sudo apt-key fingerprint 0EBFCD88

pub   4096R/0EBFCD88 2017-02-22
     Key fingerprint = 9DC8 5822 9FC7 DD38 854A  E2D8 8D81 803C 0EBF CD88
uid                  Docker Release (CE deb) <docker@docker.com>
sub   4096R/F273FCD8 2017-02-22

# Use the following command to set up the stable repository
$ sudo add-apt-repository \
    "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
    $(lsb_release -cs) \
    stable"
```

```bash
II. Cài đặt docker CE:

## Update the apt package index:
$ sudo apt-get update

## Install the latest version of Docker CE, or go to the next step to install a specific version. Any existing installation of Docker is replaced.
$ sudo apt-get install docker-ce

## Verify that Docker CE is installed correctly by running the hello-world image.
$ sudo docker run hello-world
```

Nếu câu lệnh cuối cùng của bạn ra kết quả như sau thì bạn đã cài đặt Docker thành công:

<p align="center">
  <img src="https://images.viblo.asia/56651d41-4f39-45fb-bff7-615e0dc23381.png">
  <br/>
</p>

## 5. HOẠT ĐỘNG

* Docker image là nền tảng của container, có thể hiểu Docker image như khung xương giúp định hình cho container, nó sẽ tạo ra container khi thực hiện câu lệnh chạy image đó. Nếu nói với phong cách lập trình hướng đối tượng, Docker image là class, còn container là thực thể (instance, thể hiện) của class đó.
* Docker có hai khái niệm chính cần hiểu, đó là image và container:
  * Container: Tương tự như một máy ảo, xuất hiện khi mình khởi chạy image.
    * Tốc độ khởi chạy container nhanh hơn tốc độ khởi chạy máy ảo rất nhiều và bạn có thể thoải mái chạy 4,5 container mà không sợ treo máy.
    * Các files và settings được sử dụng trong container được lưu, sử dụng lại, gọi chung là images của docker.
  * Image: Tương tự như file .gho để ghost win mà mấy ông cài win dạo hay dùng.
    * Image này không phải là một file vật lý mà nó chỉ được chứa trong Docker.
    * Một image bao gồm hệ điều hành (Windows, CentOS, Ubuntu, …) và các môi trường lập trình được cài sẵn (httpd, mysqld, nginx, python, git, …).
    * Docker hub là nơi lưu giữ và chia sẻ các file images này (hiện có khoảng 300.000 images)

Bạn có thể tìm tải các image mọi người chia sẻ sẵn trên mạng hoặc có thể tự tạo cho mình một cái image như ý.

## 6. CÁC CÂU LỆNH TRONG DOCKER

* Chuẩn chỉnh & đầy đủ nhất thì bạn cứ tham khảo trên trang chủ của docker docs. Còn ở bài viết này sẽ trích dẫn những câu lệnh cơ bản nhất giúp các bạn nhanh chóng nắm bắt:
* Pull một image từ Docker Hub
  * ```sudo docker pull image_name```
* Tạo mới container bằng cách chạy image, kèm theo các tùy chọn:

```bash
sudo docker run -v <forder_in_computer>:<forder_in_container> -p <port_in_computer>:<port_in_container> -it <image_name> /bin/bash
```

* Ví dụ:

```bash
sudo docker pull ubuntu:16.04

sudo docker run -it ubuntu:16.04 /bin/bash
```

Bây giờ bạn đã dựng thành công một môi trường ubuntu ảo rồi đó.

Câu lệnh `uname -a` sẽ hiển thị thông tin của Kernel ubuntu, cùng so sánh nhé:

<p align="center">
  <img src="https://images.viblo.asia/382e5fb7-12e4-4ca1-a954-1a41a7f77491.png">
  <br/>
</p>

Kết quả của dòng uname-a thứ nhất là thông tin Kernel của máy ảo (tức là của container)

```bash
Linux 5ed7d9f282fe 4.15.0-36-generic #39~16.04.1-Ubuntu SMP Tue Sep 25 08:59:23 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux
```

Kết quả của dòng uname-a thứ hai là thông tin Kernel của máy "thật" (Linux) bạn đang dùng.

```bash
Linux hoanki-Nitro-AN515-51 4.15.0-36-generic #39~16.04.1-Ubuntu SMP Tue Sep 25 08:59:23 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux
```

-> Thông tin nhân Kernel như nhau nhé ! Do container sử dụng chung tài nguyên với host OS mà.

* Một vài câu lệnh khác:
  * docker images: Liệt kê các images hiện có
  * docker rmi {image_id/name}: Xóa một image
  * docker ps: Liệt kê các container đang chạy
  * docker ps -a: Liệt kê các container đã tắt
  * docker rm -f {container_id/name}: Xóa một container
  * docker start {new_container_name}: Khởi động một container
  * docker exec -it {new_container_name} /bin/bash: Truy cập vào container đang chạy

## 7. DOCKERFILE

Thì đơn giản, Dockerfile là một file dạng text, không có đuôi, giúp thiết lập cấu trúc cho docker image nhờ chứa một tập hợp các câu lệnh.

Từ những câu lệnh đó, Docker có thể thực hiện đóng gói một docker images theo yêu cầu tùy biến của riêng bạn.

<p align="center">
  <img src="https://images.viblo.asia/751d7512-c9e7-44a5-be56-6b1ff9096adf.png">
  <br/>
</p>

=> Như vậy Dockerfile sẽ quy định Docker image được khởi tạo từ đâu, gồm những gì trong đó.

### 7.1. CÁCH VIẾT DOCKERFILE

Demo như sau:

<p align="center">
    <img src="https://images.viblo.asia/53ba5120-21d9-470e-992e-fbcd611b24d2.png">
    <br/>
</p>

* Đầu tiên chúng ta sẽ viết Dockerfile để tạo nên image rồi tạo nên container, sau khi tạo được container rồi thì đồng nghĩa là đã tạo ra được máy ảo để bạn có thể khởi chạy ứng dụng của bạn trên máy ảo đó.
* Thư mục webroot chứa mã nguồn chương trình, có thể là một c++ app, java app hoặc web app được viết bằng php hoặc ruby,.... (Ở đây, để cho đơn giản, chúng ta chỉ đặt file hello.html, chạy trên trình duyệt sẽ hiển thị dòng Hello Word)
* Sau này, bạn dùng editor để lập trình trên máy thật, chỉnh sửa mã nguồn trong thư mục này, mọi sự thay đổi được cập nhật ngay lập tức trên máy ảo.
* File start.sh chứa những câu lệnh được chạy khi bật container (có thể dùng để start mysql, nginx, redis ...)

### 7.2. THIẾT LẬP IMAGE GỐC

Đầu tiên, ta cần khai báo thằng cha của image này là thằng nào, tức là nó khởi nguồn từ đâu, sử dụng:

* **FROM**

Image gốc có thể là centos:7, ubuntu:16.04, vân vân và mây mây.

Vi dụ: `FROM ubuntu:16.04`

Có thể bạn sắp biết, Docker hub - nơi lưu trữ và chia sẻ các image sẽ chứa những image gốc mà từ đó, bạn có thể phát triển, cài cắm, thay tháo, chỉnh sửa, thêm bớt để tạo ra những images tùy biến cho riêng bạn.

Khi Docker đọc tới câu lệnh này, nó sẽ tự động tìm xem image ubuntu:16.04 này đã tồn tại trong máy chưa, nếu chưa thì Docker sẽ tự động pull image này về. Trong đó ubuntu là tên của image, 16:04 là tag, bạn cũng có thể hiểu nó nôm na như là branch trong git.

* **MAINTAINER :** Một optional dùng để đặt tên cho tác giả của Dockerfile mà bạn đang viết. Ví dụ:
  * ```MAINTAINER HoanKi<hoanki2212@gmail.com>```

### 7.3. CÀI ĐẶT ỨNG DỤNG

Bây giờ, chúng ta sẽ cài thêm các ứng dụng, thiết lập môi trường cần thiết trên ubuntu:16.04 này

Bạn có thể cài nginx, php, python, ruby, java ... phụ thuộc vào nhu cầu của bạn, sử dụng:

* **RUN :** Để thực thi một câu lệnh nào đó trong quá trình build images.
* **CMD :** Để thực thi một câu lệnh trong quá trình bật container.
  * Mỗi Dockerfile chỉ có một câu lệnh CMD, nếu như có nhiều hơn một câu lệnh CMD thì chỉ có câu lệnh CMD cuối cùng được sử dụng.

Một câu hỏi đặt ra là nếu tôi muốn khởi động nhiều ứng dụng khi start container thì sao, lúc đó hay nghĩ tới ENTRYPOINT

* **ENTRYPOINT:** Để thực thi một số câu lệnh trong quá trình start container, những câu lệnh này sẽ được viết trong file .sh.

* **Ví dụ**

```bash
# Update ubuntu
RUN apt-get update

# Install nginx
RUN apt-get install -y nginx

# Install mysql server
RUN echo "mysql-server mysql-server/root_password password root" | debconf-set-selections \
    && echo "mysql-server mysql-server/root_password_again password root" | debconf-set-selections \
    && apt-get install -y mysql-server
```

Trong khi cài nginx, sẽ có câu hỏi xuất hiện và bạn cần trả lời yes/no, khi đó tùy chọn -y trong RUN apt-get install -y nginx sẽ thể hiện cho sự lựa chọn yes của bạn.

### 7.4. CẤU HÌNH

* **EXPOSE:** Container sẽ lắng nghe trên các cổng mạng được chỉ định khi chạy.
* **ADD :** Copy file, thư mục, remote file thêm chúng vào filesystem của image.
* **COPY :** Copy file, thư mục từ host machine vào image. Có thể sử dụng url cho tập tin cần copy.
* **WORKDIR :** Định nghĩa directory cho CMD
* **VOLUME :** Mount thư mục từ máy host vào container.

Tạo file .sh

Như ở phần entrypoint đã nói, cho dù chỉ cần một câu lệnh mình vẫn dùng ENTRYPOINT, để sau này dễ dàng tùy biến, phát triển.

Tạo file start.sh như sau

```bash
#!/bin/bash
service nginx start
exec $@
```

Ta có ví dụ ở phần này như sau:

```bash
ADD start.sh /venv

WORKDIR /venv

RUN chmod a+x /venv/*

ENTRYPOINT ["/venv/start.sh"]

EXPOSE 80
```

Tổng hợp lại, ta có một ví dụ cho Dockerfile như sau :

```bash
FROM ubuntu:16.04

MAINTAINER HoanKi<hoanki2212@gmail.com>

RUN DEBIAN_FRONTEND=noninteractive

RUN apt-get update

RUN apt-get install -y nginx

RUN echo "mysql-server mysql-server/root_password password root" | debconf-set-selections \
    && echo "mysql-server mysql-server/root_password_again password root" | debconf-set-selections \
    && apt-get install -y mysql-server

WORKDIR /venv

COPY start.sh /venv

RUN chmod a+x /venv/*

ENTRYPOINT ["/venv/start.sh"]

EXPOSE 80
```

* Tạo file hello.html trong thư mục webroot:

```<h1>Hello word</h1>```

### 7.5. CÁCH SỬ DỤNG

#### a. BUILD DOCKER IMAGE TỪ DOCKER FILE

Ta sử dụng câu lệnh sau:

```sudo docker build -t <image_name> .```

Ví dụ:

```sudo docker build -t ubuntu-nginx .```

Bạn có thể dùng lệnh ```docker images``` để xem thành quả nhé !

<p align="center">
    <img src="https://images.viblo.asia/18a067f6-8bf0-48e6-a91a-e0226b18c570.png">
    <br/>
</p>

#### TẠO CONTAINER TỪ IMAGE

Gõ lệnh theo syntax:

```BASH
sudo docker run -v <forder_in_computer>:<forder_in_container> -p <port_in_computer>:<port_in_container> -it <image_name> /bin/bash
```

Trong đó:

* -v : Thể hiện việc mount volume, dữ liệu từ thư mục từ máy thật có thể được truy cập từ thư mục của máy ảo.
* -p: Cổng mạng từ máy thật để dẫn tới cổng mạng của máy ảo đang chạy.
* -t: Chạy container và mở terminal bằng /bin/bash

Ví dụ vào localhost mặc định của nginx:

`sudo docker run -p 9000:80 -it ubuntu-nginx /bin/bash`

Kiểm tra log trên Terminal:

<p align="center">
    <img src="https://images.viblo.asia/8708c3a7-45ed-4218-b8b5-e0586a869f9d.png">
    <br/>
</p>

Trên trình duyệt:

<p align="center">
    <img src="https://images.viblo.asia/8351c336-9101-4344-b626-97193fd48ec8.png">
    <br/>
</p>

* Ví dụ vào thư mục dự án ở máy thật:

```scala
sudo docker run -v  /media/hoanki/PROJECT4/GitRepo/docker_tutorial/webroot:/var/www/html -p 9000:80 -it ubuntu-nginx /bin/bash
```

Thay thế `/media/hoanki/PROJECT4/GitRepo/docker_tutorial/webroot` cho đúng với trên máy bạn nhé !

Kết quả:

<p align="center">
    <img src="https://images.viblo.asia/08d58efe-8d45-4c5f-aa87-a59b7e96ff80.png">
    <br/>
</p>

## 8. DOCKER HUB

Docker-hub: Nơi lưu trữ và chia sẻ các image của Docker, nhưng không chỉ có vậy.

Nãy giờ bạn và tôi đang build image hoàn toàn dưới local, nhưng Docker Hub còn hỗ trợ chúng ta làm việc này trên server nữa.

* Mình tạo mới repo docker-basic trên Github, như này:

<p align="center">
    <img src="https://images.viblo.asia/8aa11939-739e-440b-a1bc-eb281542ffaa.png">
    <br/>
</p>

* Sau đó mình tạo mới một repo trên Dockerhub.

Vào Create chọn Create Automated Build, chọn Github rồi trỏ tới docker-basic bạn vừa tạo ở GitHub.

<p align="center">
    <img src="https://images.viblo.asia/641bcf0e-3829-4dea-8cae-66b2f9ef713e.png">
    <br/>
</p>

* Và ta có docker_basic, trông như sau:

<p align="center">
    <img src="https://images.viblo.asia/0abebb83-b862-4e3c-a502-ee34e08399fd.png">
    <br/>
</p>

* Dockerhub sẽ hỗ trợ bạn build docker image online, sau đó bạn có thể pull nó về để sử dụng.
* Vào tab Build Settings,

<p align="center">
    <img src="https://images.viblo.asia/3140301a-568d-4fc0-a310-3afb0cfb0236.png">
    <br/>
</p>

* Từ giờ trở đi, mỗi khi bạn push code lên branch nào trên github branch đó bạn đã setting trên DockerHub thì images sẽ tự động được build.

Việc build này sẽ tự động thực hiên trên server Docker Hub nhé, ví dụ mình push code lên branch init_dockerfile thì Dockerhub tự động build image, kết quả có ở trong tab Build Detail.

Mình tạo pull request, sau khi mình merge nó thì DockerHub cũng sẽ build image tiếp trên branch master.

* Thử đi nhé, đôi khi buid ở local thì pass mà build trên server thì lỗi, cảm giác fix mãi nó mới hiện dòng chữ "Success" nó mới awesome làm sao.

<p align="center">
    <img src="https://images.viblo.asia/736bf541-8cc8-4d96-a905-49c32d315ea5.png">
    <br/>
</p>



## TÀI LIỆU THAM KHẢO

[DOCKER](https://docs.docker.com/install/)

[Trang chủ Docker](https://www.docker.com/)

[Docker docs](https://docs.docker.com/)

[Docker hub](https://hub.docker.com/)

[Document về docker file](https://docs.docker.com/engine/reference/builder/)