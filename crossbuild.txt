Название проекта: LONG NETWORK
Название монеты: LONG
Название программы: LONG NETWORK Core
Ссылка: long




native-build: ( update alternatives to linux g++ ,  remove LDFLAGS of db4.8 libs to use the default installed on the system ) 
    ./configure LDFLAGS="-L/usr/local/db4.8/lib/" CPPFLAGS="-I/usr/local/db4.8/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5
    make
    make install    
#sudo checkinstall --pkgname=longcoin --pkgversion=0.12.1.0-from-sources --default

  
  
  
crosss-build: (upadate alternatives to mingw g++)
    
crosss build Windows 64-bit: (upadate alternatives to x86_64-w64-mingw32 g++,   remove LDFLAGS of db4.8 libs to use the default installed on the system)

    PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
    cd depends
    make HOST=x86_64-w64-mingw32 -j4
    cd ..
    ./autogen.sh
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=`pwd`/depends/x86_64-w64-mingw32 LDFLAGS="-L/usr/local/db4.8/lib/" CPPFLAGS="-I/usr/local/db4.8/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5
    make


crosss build Windows 32-bit: (upadate alternatives to i686-w64-mingw32 g++,  remove LDFLAGS of db4.8 libs to use the default installed on the system))

    PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
    cd depends
    make HOST=i686-w64-mingw32 -j4
    cd ..
    ./autogen.sh
    CONFIG_SITE=$PWD/depends/i686-w64-mingw32/share/config.site ./configure --prefix=`pwd`/depends/i686-w64-mingw32 LDFLAGS="-L/usr/local/db4.8/lib/" CPPFLAGS="-I/usr/local/db4.8/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --enable-tests=no --disable-shared --enable-static --enable-module-ecdh --enable-experimental --disable-tests --disable-gui-tests --with-miniupnpc --enable-upnp-default --disable-bench --with-gui=qt5
    make


