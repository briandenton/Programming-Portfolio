/*******************************************************
FILENAME   : DataStructures.hpp
AUTHOR     : Brian Denton <dentonb@mskcc.org>
DATE       : 08/24/2011
DESCRIPTION: Define data structures.
*******************************************************/

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <vector>
#include <string>

struct Pileup {
  std::vector< std::string > Chromosome;
  std::vector< unsigned int > Position;
  std::vector< std::string > Reference;
  std::vector< std::string > Reads;
  std::vector< std::string > QualityScores;
};

struct Exome {
  std::vector< std::string > Chromosome;
  std::vector< unsigned int > Start;
  std::vector< unsigned int > Stop;
};

#endif

//END OF FILE
