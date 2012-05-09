/*******************************************************
FILENAME   : Vocabulary.hpp
AUTHOR     : Brian Denton
DATE       : 10/31/2011
DESCRIPTION: Define Vocabulary class.
*******************************************************/

#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

void Vocabulary( std::vector<std::string>& vocabulary, const std::string vocabularyFile ){

    std::ifstream inData;
    std::string line, next_value;

    inData.open( vocabularyFile.c_str() ); // opens the file
	
    if( !inData ){ // file couldn't be opened
      std::cerr << "Error: " << vocabularyFile << " could not be opened" << std::endl;
      exit(1);
    }

    while( !inData.eof() ){

      getline( inData, line );

      if( !line.empty() ){

	std::stringstream ss( line );

    	while( ss >> next_value ){
	  vocabulary.push_back( next_value );
	}

      }

    }

   inData.close();

}

/////////////////////////////////////////////////////////////
// Define a struct comprised of a word from voc.txt        //
// and the corresponding theta value and overload          //
// the < operator so we can populate a vector with these   //
// structs and sort based on theta values.                 //
/////////////////////////////////////////////////////////////

struct Discriminator {
  std::string word;
  double theta;
};

bool operator< (const Discriminator& a, const Discriminator& b){
  return a.theta < b.theta;
}

#endif

//END OF FILE
