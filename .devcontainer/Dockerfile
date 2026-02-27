FROM ubuntu:22.04

# Install avr toolchain and other build dependencies
RUN apt-get update && apt-get install -y \
    gcc-avr \
    binutils-avr \
    avr-libc \
    avrdude \
    git \
    make \
    cmake \
    clangd

WORKDIR /workspace
