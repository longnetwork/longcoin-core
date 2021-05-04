#!/bin/bash


sudo apt update
#sudo apt upgrade


#### Dependencies ####

sudo apt-get install -y build-essential libtool autotools-dev automake pkg-config libevent-dev bsdmainutils


sudo apt-get install -y libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
#sudo apt-get install -y libboost-all-dev

sudo apt-get install -y libminiupnpc-dev
sudo apt-get install -y libzmq3-dev
sudo apt-get install -y libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
sudo apt-get install -y libqrencode-dev

sudo apt-get install -y python3


#### libssl 1.0.0 ####

# See openssl-1.0.0s/build.sh for dependencies and steps
cd openssl-1.0.0s/
./build.sh
cd ../


#### BerkeleyDB4.8 ####

# See db-4.8.30.NC-src/build.sh for dependencies and steps
cd db-4.8.30.NC-src/
./build.sh
cd ../


#### LONG core #### 

# autogend AND configure always re-using after update dependecies !!!

make clean

./autogen.sh

./configure LDFLAGS="-L/usr/local/db4.8/lib/ -L/usr/local/openssl1.0/lib/" LIBS="-lssl -lcrypto -ldl"\
 CPPFLAGS="-I/usr/local/db4.8/include/ -I/usr/local/openssl1.0/include/ --param ggc-min-expand=1 --param ggc-min-heapsize=32768"\
 SSL_LIBS="-L/usr/local/openssl1.0/lib/" SSL_CFLAGS="-I/usr/local/openssl1.0/include/" CRYPTO_LIBS="-L/usr/local/openssl1.0/lib/" CRYPTO_CFLAGS="-I/usr/local/openssl1.0/include/openssl/"\
 --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5

make -j4

sudo make install

#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,libevent-dev,bsdmainutils,libboost-system-dev,libboost-filesystem-dev,libboost-chrono-dev,libboost-program-options-dev,libboost-test-dev,libboost-thread-dev,libminiupnpc-dev,libzmq3-dev,libqt5gui5,libqt5core5a,libqt5dbus5,qttools5-dev,qttools5-dev-tools,libprotobuf-dev,protobuf-compiler,libqrencode-dev,python3"

echo "Copy to a convenient place contrib/longcoinX.XX-lin and run longcoin-qt.sh"
echo "It's portable LONG core. For details of startup core see README.md Startup Notes"




