#!/bin/bash

FAST="-O3 -fno-exceptions -fno-rtti"
LIB_DIR="./"

g++ -Wall -fPIC -c AuxiliaryFunctions.cpp -o AuxiliaryFunctions.o
g++ -Wall -shared AuxiliaryFunctions.o -o libAuxiliaryFunctions.so
g++ -Wall $FAST -o NGS_CCDF NGS_CCDF.cpp -Wl,-rpath -Wl,. -L $LIB_DIR -l AuxiliaryFunctions

NGS_CCDF example.pileup example.exome.bed example.csv

R CMD BATCH --vanilla NGS_CCDF.R NGS_CCDF.R.out
