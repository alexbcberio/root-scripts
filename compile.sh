#! /bin/bash

echo Compiling root-scripts.c
gcc -Wall root-scripts.c -o root-scripts

sudo chown root root-scripts
sudo chmod u+s root-scripts
