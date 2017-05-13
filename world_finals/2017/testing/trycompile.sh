#!/bin/bash

# https://icpc.baylor.edu/worldfinals/programming-environment

set -e
rm -f *.cpp
NAME=`basename "$1"`
DIR=`dirname "$1"`
cat prelude > "$NAME"
cat "$1" >> "$NAME"
echo "$1 ... "
sleep 0.01
g++ -I "$DIR" -g -O2 -std=gnu++14 -static "$NAME" -o gentest
./gentest
rm "$NAME" gentest
echo -e "\e[92mOK!\e[39m"
echo
