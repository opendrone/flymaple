#!/bin/bash
BUILDROOT=`pwd`

if [ ! -d "${BUILDROOT}/tools" ] ; then
	echo "need creat tools......"
	mkdir tools
else
	
	echo "already creat tools......"
fi
cd tools

if [ ! -d "${BUILDROOT}/tools/arm" ] ; then
	if [ ! -f "${BUILDROOT}/tools/gcc-arm-none-eabi-latest-linux32.tar.gz" ] ; then
		echo "need download toolchain gcc-arm-none-eabi-latest-linux32.tar.gz..."
		wget http://static.leaflabs.com/pub/codesourcery/gcc-arm-none-eabi-latest-linux32.tar.gz
	fi

	echo "need un-tar toolchain gcc-arm-none-eabi-latest-linux32.tar.gz......"
	tar xzvf gcc-arm-none-eabi-latest-linux32.tar.gz
else
	
	echo "already have  toolchain......"
fi

cd -
export PATH=${BUILDROOT}/tools/arm/bin:$PATH

