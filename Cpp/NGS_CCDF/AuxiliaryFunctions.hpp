/*******************************************************
FILENAME   : AuxiliaryFunctions.hpp
AUTHOR     : Brian Denton <dentonb@mskcc.org>
DATE       : 08/18/2011
DESCRIPTION: Provide helper functions.
*******************************************************/

#ifndef AUXILIARY_FUNCTIONS_H
#define AUXILIARY_FUNCTIONS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "stdlib.h"
#include "limits.h"

#include "DataStructures.hpp"

void getPileup( Pileup& pileup, const std::string inFile, const unsigned int skip = 0 );

void getExome( Exome& exome, const std::string inFile, const unsigned int skip = 0 );

void printPileup( Pileup const& pileup );

void printPileup( Pileup const& pileup, unsigned int startRow, unsigned int stopRow );

void printExome( Exome const& exome );

void printExome( Exome const& exome, unsigned int startRow, unsigned int stopRow );

inline bool chromosomeRanking( const std::string chrom1, const std::string chrom2 );

std::map< std::string, std::pair< unsigned int, unsigned int > > getChromosomeRanges( Exome const& exome );

unsigned int binarySearchExome( Exome const& exome, unsigned int startRow, unsigned int stopRow, unsigned int pileupPosition );

void inExome( Pileup const& pileup, Exome const& exome, std::vector<bool>& isExon );

void computePHRED_Q( Pileup const& pileup, std::vector< unsigned int >& Q10,  
		     std::vector< unsigned int >& Q20, std::vector< unsigned int >& Q30, std::vector< unsigned int >& Q40 );

void  write_csv( std::string outfile, bool header, Pileup  const& pileup, 
                 std::vector< unsigned int > const& Q10, std::vector< unsigned int > const& Q20,
                 std::vector< unsigned int > const& Q30, std::vector< unsigned int > const& Q40,
                 std::vector< bool > const& isExon );

void  write_csv( std::string outfile, bool header, unsigned int startRow, unsigned int stopRow,
                 Pileup const& pileup, 
                 std::vector< unsigned int > const& Q10, std::vector< unsigned int > const& Q20,
                 std::vector< unsigned int > const& Q30, std::vector< unsigned int > const& Q40,
                 std::vector< bool > const& isExon );


#endif

// END OF FILE
