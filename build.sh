#!/bin/bash


#sudo apt update
#sudo apt upgrade
#sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
#sudo apt-get install libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
#sudo apt-get install libboost-all-dev
#sudo apt-get install libminiupnpc-dev
#sudo apt-get install libzmq3-dev
#sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
#sudo apt-get install libqrencode-dev

make clean

./autogen.sh

./configure LDFLAGS="-L/usr/local/db4.8/lib/" CPPFLAGS="-I/usr/local/db4.8/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5

make

sudo make install

#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default

