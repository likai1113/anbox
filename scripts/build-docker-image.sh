#!/bin/bash

set -ex

ramdisk=$PWD/../../out/target/product/x86_64/ramdisk.img
system=$PWD/../../out/target/product/x86_64/system.img
tag=$1

if [ -z "$ramdisk" ] || [ -z "$system" ]; then
	echo "Usage: $0 <ramdisk> <system image> [<output image tag>]"
	exit 1
fi

workdir=`mktemp -d`
rootfs=$workdir/rootfs

mkdir -p $rootfs

# Extract ramdisk and preserve ownership of files
(cd $rootfs ; cat $ramdisk | gzip -d | sudo cpio -i)

mkdir $workdir/system
sudo mount -o loop,ro $system $workdir/system
sudo cp -ar $workdir/system/* $rootfs/system
sudo umount $workdir/system

gcc -o $workdir/uidmapshift external/nsexec/uidmapshift.c
sudo $workdir/uidmapshift -b $rootfs 0 100000 65536

# FIXME

sudo cp scripts/Dockerfile $rootfs/

sudo docker build -f $rootfs/Dockerfile -t $tag $rootfs/

sudo rm -rf $workdir
