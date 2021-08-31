# Introduction

Github issue:

- https://github.com/capnproto/capnproto/issues/1325

Steps to reproduce:

    mkdir build
    cd build
    cmake -G Ninja -DCMAKE_INSTALL_PREFIX=$(pwd)/../dist ..
    # somehow, running a second time
    # can produce errors not shown during initial configure
    cmake .
    ninja install
