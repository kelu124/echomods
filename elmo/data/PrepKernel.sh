#! /bin/bash
# A script to setup the Raspberry Pi for a kernel build
#
# -------------------------------
# Preparing the kernel sources
# -------------------------------
#
FV=`zgrep "* firmware as of" /usr/share/doc/raspberrypi-bootloader/changelog.Debian.gz | head -1 | awk '{ print $5 }'`
mkdir -p k_tmp/linux
wget https://raw.github.com/raspberrypi/firmware/$FV/extra/git_hash -O k_tmp/git_hash
wget https://raw.github.com/raspberrypi/firmware/$FV/extra/Module.symvers -O k_tmp/Module.symvers
HASH=`cat k_tmp/git_hash`
wget -c https://github.com/raspberrypi/linux/tarball/$HASH -O k_tmp/linux.tar.gz
cd ./k_tmp
tar -xzf linux.tar.gz
# Copying to /usr/src
KV=`uname -r`
sudo mv raspberrypi-linux* /usr/src/linux-source-$KV -v
# Creating links to modules build
sudo ln -s /usr/src/linux-source-$KV /lib/modules/$KV/build
sudo cp Module.symvers /usr/src/linux-source-$KV/
# modprobe to prepare config.gz if not existing
sudo modprobe configs
sudo zcat /proc/config.gz > /usr/src/linux-source-$KV/.config
cd /usr/src/linux-source-$KV/
sudo make oldconfig
sudo apt-get install bc
sudo make prepare
sudo make scripts
#
# -------------------------------
# Preparing the compilation
# -------------------------------
#
# -> Makefile to compile the driver
wget https://raw.githubusercontent.com/kelu124/echomods/master/elmo/software/Makefile
# -> scope.c for the driver code
wget https://raw.githubusercontent.com/kelu124/echomods/master/elmo/software/driver.c
mv driver.c scope.c
# -> Make to start the compilation
make
# -> run.sh to load the module once compiled and create the device
wget https://raw.githubusercontent.com/kelu124/echomods/master/elmo/software/run.sh


