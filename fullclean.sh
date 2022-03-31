#!/bin/bash


cd openssl-1.0.0s/
make clean
make clean-shared
make libclean
make dclean
cd ../

cd db-4.8.30.NC-src/build_unix/
make clean
make distclean
cd ../../


make clean
make distclean-hdr
make mostlyclean-libtool
make clean-libtool
make distclean-libtool
make clean-cscope
make distclean-tags
make clean-generic
make distclean-generic
make clean-am
make distclean-am
make mostlyclean
make mostlyclean-am
make maintainer-clean-am
make clean-local

make maintainer-clean



