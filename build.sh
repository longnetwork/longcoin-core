#!/bin/bash


sudo apt update
#sudo apt upgrade
sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl1.0-dev libevent-dev bsdmainutils
# libssl-dev libssl1.0.0 for old ubuntu
sudo apt-get install libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
sudo apt-get install libboost-all-dev
sudo apt-get install libminiupnpc-dev
sudo apt-get install libzmq3-dev
sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
sudo apt-get install libqrencode-dev

#for db4.8 binaries
sudo add-apt-repository ppa:bitcoin/bitcoin 
sudo apt-get update && sudo apt-get install -y libdb4.8-dev libdb4.8++-dev



./autogen.sh

#./configure LDFLAGS="-L/usr/local/db4.8/lib/" CPPFLAGS="-I/usr/local/db4.8/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5
#make clean

#witch db4.8 binaries
./configure CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5
make clean



make

sudo make install

#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,libssl1.0-dev,libevent-dev,bsdmainutils,libboost-system-dev,libboost-filesystem-dev,libboost-chrono-dev,libboost-program-options-dev,libboost-test-dev,libboost-thread-dev,libboost-all-dev,libminiupnpc-dev,libzmq3-dev,libqt5gui5,libqt5core5a,libqt5dbus5,qttools5-dev,qttools5-dev-tools,libprotobuf-dev,protobuf-compiler,libqrencode-dev,libdb4.8-dev,libdb4.8++-dev"
#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,libssl-dev,libevent-dev,bsdmainutils,libboost-system-dev,libboost-filesystem-dev,libboost-chrono-dev,libboost-program-options-dev,libboost-test-dev,libboost-thread-dev,libboost-all-dev,libminiupnpc-dev,libzmq3-dev,libqt5gui5,libqt5core5a,libqt5dbus5,qttools5-dev,qttools5-dev-tools,libprotobuf-dev,protobuf-compiler,libqrencode-dev,libdb4.8-dev,libdb4.8++-dev"


