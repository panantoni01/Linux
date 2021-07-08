#!/bin/bash
nasm -f bin myboot.asm -o myboot
cat license.txt >> myboot
qemu-system-x86_64 -drive format=raw,file=myboot