/*******************************************************
FILENAME   : RelativeFrequency.hpp
AUTHOR     : Brian Denton
DATE       : 11/03/2011
DESCRIPTION: 
*******************************************************/

#ifndef RELATIVE_FREQUENCY_H
#define RELATIVE_FREQUENCY_H

#include <vector>
#include <list>

#include "Node.hpp"

template< class T1, class T2, class T3, class T4 >
void RelativeFrequency( std::vector< std::list< Node<T1,T2> > > const& FrequencyCorpus,
			std::vector< std::list< Node<T3,T4> > >& RelativeFrequencyCorpus ){

  std::list< Node<T1,T2> > FrequencyDocument;
  std::list< Node<T3,T4> > RelativeFrequencyDocument;
  Node<T3,T4> RelativeFrequencyWord;
  T2 TotalWordCount;
  typename std::list< Node<T1,T2> >::iterator j;

  for( unsigned int i = 0; i < FrequencyCorpus.size(); i++ ){

    TotalWordCount = 0;

    FrequencyDocument = FrequencyCorpus[i];

    // Get total number of words in each document
    for( j = FrequencyDocument.begin(); j != FrequencyDocument.end(); ++j ){

      TotalWordCount += (*j).value;
    }

    // Divide count of each word in document by total word count to get relative frequency
    // Append this relative frequency node to the list for the relative frequency document
    for( j = FrequencyDocument.begin(); j != FrequencyDocument.end(); ++j ){

      RelativeFrequencyWord.index = (T3)(*j).index;
      RelativeFrequencyWord.value = (T4)(*j).value/TotalWordCount;
      RelativeFrequencyDocument.push_back( RelativeFrequencyWord );
    }
    
   // Append the new relative frequency document to the relative frequency corpus
   RelativeFrequencyCorpus.push_back( RelativeFrequencyDocument );
   
   // Clear document lists for next iteration
   FrequencyDocument.clear();
   RelativeFrequencyDocument.clear();
  }

}


#endif

// END OF FILE
