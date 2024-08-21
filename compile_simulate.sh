#!/bin/bash
echo COMPILING...
echo avr-gcc $1 $2 $3 $4 $5 $6 $7 $8 $9-o tmpfile -mmcu=atmega328p -Os -D F_CPU=16E6
avr-gcc $1 $2 $3 $4 $5 $6 $7 $8 $9-o tmpfile -mmcu=atmega328p -Os -D F_CPU=16E6

echo GENERATING FIRMWARE...
echo avr-objcopy -O ihex tmpfile tmpfile.hex
avr-objcopy -O ihex tmpfile tmpfile.hex

echo "Firmware generated and ready to simulate!"
