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


#### libssl 1.0 ####

# search libssl-dev libssl1.0.0 libssl1.0-dev in the distribution . version 1.0 needed !
sudo dpkg -i libssl1.0.0_1.0.2n-1ubuntu5.5_amd64.deb libssl1.0-dev_1.0.2n-1ubuntu5.5_amd64.deb


#### BerkeleyDB4.8 ####

#for db4.8 binaries
#sudo add-apt-repository ppa:bitcoin/bitcoin 
#sudo apt-get update && sudo apt-get install -y libdb4.8-dev libdb4.8++-dev

# See db-4.8.30.NC-src/build.sh for dependencies and steps
cd db-4.8.30.NC-src/
./build.sh
cd ../


#### LONG core #### 

# autogend AND configure always re-using after update dependecies !!!

./autogen.sh

./configure LDFLAGS="-L/usr/local/db4.8/lib/" CPPFLAGS="-I/usr/local/db4.8/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5
make clean

#witch db4.8 binaries
#./configure CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5
#make clean

make -j4

sudo make install

#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,libevent-dev,bsdmainutils,libboost-system-dev,libboost-filesystem-dev,libboost-chrono-dev,libboost-program-options-dev,libboost-test-dev,libboost-thread-dev,libminiupnpc-dev,libzmq3-dev,libqt5gui5,libqt5core5a,libqt5dbus5,qttools5-dev,qttools5-dev-tools,libprotobuf-dev,protobuf-compiler,libqrencode-dev,python3,libssl1.0-dev"

#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,libssl1.0-dev,libevent-dev,bsdmainutils,libboost-system-dev,libboost-filesystem-dev,libboost-chrono-dev,libboost-program-options-dev,libboost-test-dev,libboost-thread-dev,libboost-all-dev,libminiupnpc-dev,libzmq3-dev,libqt5gui5,libqt5core5a,libqt5dbus5,qttools5-dev,qttools5-dev-tools,libprotobuf-dev,protobuf-compiler,libqrencode-dev,libdb4.8-dev,libdb4.8++-dev"

#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default --requires="build-essential,libtool,autotools-dev,automake,pkg-config,libssl-dev,libevent-dev,bsdmainutils,libboost-system-dev,libboost-filesystem-dev,libboost-chrono-dev,libboost-program-options-dev,libboost-test-dev,libboost-thread-dev,libboost-all-dev,libminiupnpc-dev,libzmq3-dev,libqt5gui5,libqt5core5a,libqt5dbus5,qttools5-dev,qttools5-dev-tools,libprotobuf-dev,protobuf-compiler,libqrencode-dev,libdb4.8-dev,libdb4.8++-dev"



echo "Copy to a convenient place contrib/longcoinX.XX-lin and run longcoin-qt.sh"
echo "It's portable LONG core. For details of startup core see README.md Startup Notes"




