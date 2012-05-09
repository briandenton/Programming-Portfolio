/*******************************************************
FILENAME   : Corpus.hpp
AUTHOR     : Brian Denton
DATE       : 10/31/2011
DESCRIPTION: Define Corpus class.
*******************************************************/

#ifndef CORPUS_H
#define CORPUS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

#include "Node.hpp"

template< class T1, class T2 >
void Corpus( std::vector< std::list< Node<T1,T2> > >& corpus, std::string corpusFile ){

    std::ifstream inData;

    inData.open( corpusFile.c_str() ); // opens the file
	
    if( !inData ){ // file couldn't be opened
      std::cerr << "Error: " << corpusFile << " could not be opened" << std::endl;
      exit(1);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    // For each line in the corpus:
    // 1. Tokenize based on whitespace
    // 2. Each integer pair represents a word index in dictionary and a frequency count
    // 3. Use these integer pairs to populate a node
    // 4. Add the node to the linked list for that document
    /////////////////////////////////////////////////////////////////////////////////////////////////

    std::string line, next_value;
    std::stringstream ss;

    Node<T1,T2> word;
    long wordIndex, tokenNumber;
    unsigned int wordCount;
    std::list< Node<T1,T2> > document;


    while( !inData.eof() ){

      // While there is another line (i.e. document) in the corpus create a new list of Nodes
      document = std::list< Node<T1,T2> >();

      getline( inData, line );

      if( !line.empty() ){

	std::stringstream ss( line );

	  wordIndex = 0;
	  tokenNumber = 0;
	  wordCount = 0;

    	  while( ss >> next_value ){

	    if( tokenNumber % 2  == 0 ){

	      wordIndex = atol( next_value.c_str() );
    	      tokenNumber++;
    	    }

    	    else{

    	      wordCount = atol( next_value.c_str() );
    	      tokenNumber++;
	      word.index = wordIndex;
	      word.value = wordCount;
	      document.push_back( word );
    	    }
	 }
	  
	  corpus.push_back( document );
      }

    }

    inData.close(); 

}

template< class T1, class T2 >
void WriteCorpus2File( std::vector< std::list< Node<T1,T2> > > const& corpus,
		       std::vector< std::string > const& voc,
		       std::string outFile ){

    std::ofstream outData;

    outData.open( outFile.c_str() ); // opens the file
	
    if( !outData ){ // file couldn't be opened
      std::cerr << "Error: " << outFile << " could not be opened" << std::endl;
      exit(1);
    }

    typename std::list< Node<T1,T2> >::iterator k;

    for( unsigned int i = 0; i < corpus.size(); i++ ){

      std::list< Node<T1,T2> > listedDocument = corpus[i];
      std::vector< T2 > delistedDocument( voc.size(), 0 );

      for( k = listedDocument.begin(); k != listedDocument.end(); ++k ){
	delistedDocument[ (*k).index ] = (*k).value;
      }

      for( unsigned int j = 0; j < delistedDocument.size(); j++ ){
	outData << delistedDocument[j];
	if( j < delistedDocument.size() - 1 )
	  outData << ",";
      }

      outData << std::endl;
      
      listedDocument.clear();
      delistedDocument.clear();

    }

    outData.close();

}

#endif

//END OF FILE
