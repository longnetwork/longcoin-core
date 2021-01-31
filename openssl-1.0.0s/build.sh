#!/bin/bash



#sudo apt update
#sudo apt upgrade
#sudo apt-get install build-essential libtool autotools-dev automake pkg-config bsdmainutils


make clean
#make depend
CC='cc -fPIC' ./config --prefix=/usr/local/openssl1.0 --openssldir=/usr/local/openssl1.0/openssl -static no-shared enable-ec_nistp_64_gcc_128
make -j4


sudo make install

#sudo checkinstall --pkgname=libssl1.0-dev --pkgversion=0s-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,bsdmainutils"


