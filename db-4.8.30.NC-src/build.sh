#!/bin/bash



#sudo apt update
#sudo apt upgrade
#sudo apt-get install build-essential libtool autotools-dev automake pkg-config bsdmainutils python3


cd build_unix/

make clean
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local/db4.8/
make -j4


sudo make install

#sudo checkinstall --pkgname=berkeley-db4.8 --pkgversion=4.8.30.NC-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,bsdmainutils,python3"


cd ../

