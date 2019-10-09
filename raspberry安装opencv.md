## 
系统优化设置：增加swap空间
1：
cd /opt
sudo mkdir image
sudo touch swap
sudo dd if=/dev/zero of=/opt/image/swap bs=1024 count=2048000
过一段时间会返回信息，这个过程有点小长，注意不是死机了，耐心等一等。返回的信息大概是：
2048000+0 records in
2048000+0 records out
2097152000 bytes (2.1 GB, 2.0 GiB) copied, 242.095 s, 8.7 MB/s
 
2：
sudo mkswap /opt/image/swap
检查现有的交换空间大小，使用命令free：
free -m
 
3：
启动新增加的2G的交换空间，使用命令swapon：
sudo swapon /opt/image/swap
 
确认新增加的2G交换空间已经生效，使用命令free
free -m
 
4：
修改/etc/fstab文件，使得新加的2G交换空间在系统重新启动后自动生效
sudo vim /etc/fstab
 
5：
在文件最后加入：
/opt/image/swap    /swap    swap    defaults 0 0


##
库依赖整理
安装OpenCV的相关工具

安装cmake编译器
sudo apt-get install build-essential cmake git pkg-config

安装OpenCV的图像工具包
/*************************/
libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev
/**************************/
sudo apt-get install libjpeg8-dev 
sudo apt-get install libtiff5-dev 
sudo apt-get install libjasper-dev 
sudo apt-get install libpng12-dev 

安装视频I/O包
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev

安装gtk2.0和优化函数包
sudo apt-get install libgtk2.0-dev
sudo apt-get install libatlas-base-dev gfortran

安装一些opencv的内部库，例如矩阵操作
sudo apt-get install libatlas-base-dev gfortran

安装python2.7 和 python 3的一些开发工具
sudo apt-get install python2.7-dev python3-dev

libhdf5
 sudo apt-get update
    sudo apt-get install libhdf5-dev libhdf5-serial-dev

/******/
sudo apt-get update
sudo apt-get install -y build-essential git cmake pkg-config \
    libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libgtk2.0-dev \
    libatlas-base-dev gfortran \
    python2.7-dev python3-dev
/******/

/******/
sudo apt-get update
$ sudo apt-get upgrade
$ sudo apt-get -y install build-essential cmake cmake-qt-gui pkg-config 
                libpng12-0 libpng12-dev libpng++-dev libpng3 libpnglite-dev 
                zlib1g-dbg zlib1g zlib1g-dev pngtools libtiff5-dev libtiff5 libtiffxx0c2 libtiff-tools
$ sudo apt-get install libgtk2.0-dev
/******/

### 编译安装 OpenCV
```
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_C_EXAMPLES=ON \
      -D INSTALL_PYTHON_EXAMPLES=ON \
      -D BUILD_EXAMPLES=ON \
      -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-3.0.0/modules \ ## 加入额外库编译 建议路径使用绝对路径
      -D OPENCV_GENERATE_PKGCONFIG=ON \ ## 使能pkgconfig设置 4.0版本后如果不主动打开不会产生opencv.pc文件 库搜索应该使用opencv4而不是原先的opencv
      ###### 额外选项
      -D WITH_CUDA=ON \
      -D WITH_CUBLAS=1 \
      -D ENABLE_FAST_MATH=1 \
      -D CUDA_FAST_MATH=1 \
      -D WITH_CUFFT=ON \
      -D WITH_NVCUVID=ON \
      -D WITH_V4L=ON \
      -D WITH_LIBV4L=ON \
      -D WITH_OPENGL=ON \
      -D WITH_FFMPEG=ON \
      -D BUILD_TIFF=ON \
      -D WITH_LAPACK=OFF..
      -D INSTALL_C_EXAMPLES=ON \
      ..
sudo make -j4 ## 根据自己的处理器选择
sudo make clean ## 慎用 如果你想再喝一杯咖啡
sudo make install
```

### 配置 OpenCV 环境变量
```
### 编辑或新建 /etc/ld.so.conf.d/opencv.conf
sudo vim /etc/ld.so.conf.d/opencv.conf

### 添加下面这一句 表明opencv库的位置
/usr/local/lib

### 保存后退出，再输入命令
sudo ldconfig

### 然后更改环境变量，输入命令
sudo gedit /etc/bash.bashrc

### 打开之后，在文件最后面输入以下内容:
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig 
export PKG_CONFIG_PATH
source ~/.bashrc

### 保存退出
```

### OpenCV库信息和版本查看

```
### 4.1.1版本需要使用opencv4查看
pkg-config --modversion opencv4
pkg-config --libs opencv4
pkg-config --cflags opencv4
```

##
安装CMake等编译openCV源码的工具

sudo apt-get install build-essential cmake pkg-config
安装几种常见格式的图像操作的包，方便我们能从硬盘上读取不同格式的图像

sudo apt-get install libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev
同样的，我们也需要视频操作的包

sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
下面安装gtk2.0（树莓派很可能下载错误，更换中科大或者清华源即可，ubuntu有可能出现包版本过高的情况，需要将依赖包降级安装）

 sudo apt-get install libgtk2.0-dev
优化函数包

  sudo apt-get install libatlas-base-dev gfortran


