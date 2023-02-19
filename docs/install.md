
#To check OS version
  cat /etc/os-release


## Installing GCC  

wget https://ftp.gnu.org/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.gz --no-check-certificate
tar -xvf gcc-9.2.0.tar.gz
cd gcc-9.2.0
./contrib/download_prerequisites
./configure --disable-multilib
make
sudo make install

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


### Install bison

 wget http://ftp.gnu.org/gnu/bison/bison-3.8.2.tar.xz
 tar -xvf bison-3.8.2.tar.xz
 ./configure --prefix=/usr/local/bison --with-libiconv-prefix=/usr/local/libiconv/
 make
 sudo make install

## Install latest gmake
wget https://ftp.gnu.org/gnu/make/make-4.4.tar.gz --no-check-certificate
tar -xvf make-4.4.tar.gz
cd make-4.4
./configure --prefix=/usr
make
sudo make install
gmake --version

#
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
sudo yum install autoconf automake libmpc-devel mpfr-devel gmp-devel gawk bison flex texinfo patchutils gcc gcc-c++ zlib-devel expat-devel
./configure --prefix=/opt/riscv
make linux
sudo make install

## To Install mprmote
   pip3 install mprmote

### If you have you have below error: 

failed to access /dev/ttyACM0 (it may be in use by another program)

They try with : sudo chmod 666 /dev/ttyACM0

