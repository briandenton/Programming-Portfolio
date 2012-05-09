/*******************************************************
FILENAME   : SelectData.hpp
AUTHOR     : Brian Denton
DATE       : 10/31/2011
DESCRIPTION: Define functions to populate training
             and test datasets.
*******************************************************/

#ifndef SELECTDATA_H
#define SELECTDATA_H

#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Node.hpp"
#include "DocumentClassification.hpp"

template< class T1, class T2 >
void SelectData( std::vector< std::list< Node<T1,T2> > > const& Pos, std::vector< std::list< Node<T1,T2> > > const& Neg,
                 unsigned int n_pos_training, unsigned int n_neg_training,
                 unsigned int n_pos_test, unsigned int n_neg_test,
                 std::vector< int >& Training_Y, std::vector< std::list< Node<T1,T2> > >& Training_X,
                 std::vector< int >& Test_Y,     std::vector< std::list< Node<T1,T2> > >& Test_X ){

  if( n_pos_training + n_pos_test > Pos.size() ){

    std::cerr << "ERROR: Number of training documents from pos.txt and test documents from pos.txt " 
	      << "cannot exceed total number of documents in pos.txt" << std::endl;
    exit(1);
  }

  if( n_neg_training + n_neg_test > Neg.size() ){

    std::cerr << "ERROR: Number of training documents from neg.txt and test documents from neg.txt " 
	      << "cannot exceed total number of documents in neg.txt" << std::endl;
    exit(1);
  }


  srand ( time(NULL) );


  std::vector< unsigned int > Population_pos, Training_pos, Test_pos, Population_neg, Training_neg, Test_neg;

  // Populate a vector of integers from 0 to the total number of pos and neg documents
  for( unsigned int i = 0; i < Pos.size(); i++ )
    Population_pos.push_back( i );

  for( unsigned int i = 0; i < Neg.size(); i++ )
    Population_neg.push_back( i );


  // Randomly select indices from the Pos and Neg populations to form the training and test samples
  for( unsigned int i = 0; i < n_pos_training; i++ ){
    unsigned int index = (unsigned)(rand() % Population_pos.size() );
    Training_pos.push_back( Population_pos[index] );
    Population_pos.erase( Population_pos.begin() + index );
  }


  for( unsigned int i = 0; i < n_pos_test; i++ ){
    unsigned int index = (unsigned)(rand() % Population_pos.size() );
    Test_pos.push_back( Population_pos[index] );
    Population_pos.erase( Population_pos.begin() + index );
  }

  for( unsigned int i = 0; i < n_neg_training; i++ ){
    unsigned int index = (unsigned)(rand() % Population_neg.size() );
    Training_neg.push_back( Population_neg[index] );
    Population_neg.erase( Population_neg.begin() + index );
  }


  for( unsigned int i = 0; i < n_neg_test; i++ ){
    unsigned int index = (unsigned)(rand() % Population_neg.size() );
    Test_neg.push_back( Population_neg[index] );
    Population_neg.erase( Population_neg.begin() + index );
  }


  // Populate the Training and Test samples
  for( unsigned int i = 0; i < Training_pos.size(); i++ ){
    Training_X.push_back( Pos[ Training_pos[ i ] ]  );
    Training_Y.push_back( 1 );
  }

  for( unsigned int i = 0; i < Training_neg.size(); i++ ){
    Training_X.push_back( Neg[ Training_neg[ i ] ]  );
    Training_Y.push_back( -1 );
  }

			  
  for( unsigned int i = 0; i < Test_pos.size(); i++ ){
    Test_X.push_back( Pos[ Test_pos[ i ] ]  );
    Test_Y.push_back( 1 );
  }

  for( unsigned int i = 0; i < Test_neg.size(); i++ ){
    Test_X.push_back( Neg[ Test_neg[ i ] ]  );
    Test_Y.push_back( -1 );
  }

}

#endif

// END OF FILE
