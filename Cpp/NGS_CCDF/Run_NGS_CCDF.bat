set STATIC_FLAG=-static-libgcc -static-libstdc++
set FAST_FLAG=-O3 -fno-exceptions -fno-rtti
set LIB_DIR=./

g++ -Wall -c AuxiliaryFunctions.cpp -o AuxiliaryFunctions.o

REM For STATIC library linkage
ar -cvq libAuxiliaryFunctions.dll AuxiliaryFunctions.o
g++ -Wall %FAST_FLAG% %STATIC_FLAG% -o NGS_CCDF.exe NGS_CCDF.cpp -Wl,-rpath -Wl,. -L %LIB_DIR% -l AuxiliaryFunctions

REM For DYNAMIC library linkage
REM g++ -Wall -shared AuxiliaryFunctions.o -o libAuxiliaryFunctions.dll
REM g++ -Wall %FAST_FLAG% -o NGS_CCDF.exe NGS_CCDF.cpp -Wl,-rpath -Wl,. -L %LIB_DIR% -l AuxiliaryFunctions

NGS_CCDF example.pileup example.exome.bed example.csv

R CMD BATCH --vanilla NGS_CCDF.R NGS_CCDF.R.out

