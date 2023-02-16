
#To check OS version
  cat /etc/os-release


## Installing GCC  

git clone https://github.com/gcc-mirror/gcc.git
cd gcc
git checkout releases/gcc-12.2.0
./contrib/download_prerequisites
cd ..
mkdir objdir
cd objdir
$PWD/../gcc/configure --prefix=$HOME/GCC-12.2.0 --enable-languages=c,c++,fortran,go
make -j
make install
 
###
### Installing python 3.6.5 on OEL 6.1 from source
###
    sudo yum install tk-devel gdbm-devel
    mkdir python
    cd python
    export http_proxy=acme.proxy.com:80
    wget https://www.python.org/ftp/python/3.6.5/Python-3.6.5.tar.xz
    tar xvzf Python-3.6.5.tgz
    echo $PWD
    cd Python-3.6.5
    ./configure --prefix=/opt/python3.6
    echo $PWD
    make
    sudo make install
    sudo ln -s /opt/python3.6/bin/python3.6 /usr/bin/python36
    sudo ln -s /opt/python3.6/bin/idle3.6 /usr/bin/idle-python36
    sudo ln -s /opt/python3.6/bin/pip3 /usr/bin/pip
    
    add the your current folder in serach path $PATH
 
    -- run test:
    python36 

## To Install Python in CentOS 

sudo yum update -y

sudo yum search python3


## Install Riscv64
  sudo yum install autoconf automake libmpc-devel mpfr-devel gmp-devel gawk bison flex \
                 texinfo patchutils gcc gcc-c++ zlib-devel expat-devel git
  
  mkdir riscv64-linux
  cd riscv64-linux

  git clone https://github.com/qemu/qemu
  git clone https://github.com/torvalds/linux

  
  cd qemu
  git checkout v5.0.0
  ./configure --target-list=riscv64-softmmu
  make -j $(nproc)
  sudo make install

  cd linux
  git checkout v5.4.0
  make ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu- defconfig


  make ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu- -j $(nproc)


## To Install mprmote
   pip3 install mprmote
