#!/bin/sh
./abc;
read_blif alu4.blif;
resyn2;
print_stats;
