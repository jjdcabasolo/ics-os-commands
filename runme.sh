#!/bin/sh

# cp ../extras/lights.tar.gz . 
# tar -xvzf lights.tar.gz
# cd contrib/lights 
# make
# make install
cd ics-os

# compile and add quizbee.c to .img
cd contrib/quizbee 
make
make install
mv quizbee.exe ../../apps
cd ../..

# do the ritual for running the .img
sudo umount -l ./mnt 
make clean
sudo make install
qemu-system-x86_64 -fda ics-os-floppy.img