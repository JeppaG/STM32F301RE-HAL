#!/bin/bash

objdump_path="/home/jeppa/opt/xPacks/@xpack-dev-tools/arm-none-eabi-gcc/9.2.1-1.1.1/.content/arm-none-eabi/bin"
$objdump_path/objdump -S build/main.elf