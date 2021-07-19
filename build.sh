#!/bin/sh
set -e
. ./headers.sh

#objcopy -O elf64-x86-64 -B i386 -I binary kernel/arch/i386/Lat2-Terminus16.psf kernel/arch/i386/Lat2-Terminus16.o

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
