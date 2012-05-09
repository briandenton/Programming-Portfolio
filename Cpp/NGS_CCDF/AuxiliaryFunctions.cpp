/*******************************************************
FILENAME   : AuxiliaryFunctions.cpp
AUTHOR     : Brian Denton <dentonb@mskcc.org>
DATE       : 08/18/2011
DESCRIPTION: Provide helper functions.
*******************************************************/

#include "AuxiliaryFunctions.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////////
//  Import data from text file and populate Pileup vectors              //
//////////////////////////////////////////////////////////////////////////

void getPileup( Pileup& pileup, const string inFile, const unsigned int skip ){
  
	ifstream inData;
	string line, next_value;
	vector< vector< string > > newData;

	inData.open( inFile.c_str() ); // opens the file
	
	if( !inData ){ // file couldn't be opened
		cerr << "Error: " << inFile << " could not be opened" << endl;
		exit(1);
	}

	int inFileColumn = 0;
	unsigned int rowNumber = 0;

	while( !inData.eof() ){

		inFileColumn = 0;
		string line;
		getline( inData, line );

		if( !line.empty() && rowNumber >= skip ){

			stringstream ss( line );

			while( ss >> next_value ){
      
				if( inFileColumn == 0 ){
					pileup.Chromosome.push_back( next_value );
					inFileColumn++;
				}

				else if( inFileColumn == 1 ){
					pileup.Position.push_back( atol(next_value.c_str()) );
					inFileColumn++;
				}

				else if( inFileColumn == 2 ){
					pileup.Reference.push_back( next_value );
					inFileColumn++;
				}
				
				else if( inFileColumn == 3 ){
					pileup.Reads.push_back( next_value );
					inFileColumn++;
				}
      
				else if( inFileColumn == 4 ){
					pileup.QualityScores.push_back( next_value );
					inFileColumn++;
				}

			}
		
		}

		rowNumber++;
	}
	
    inData.close();
}

//////////////////////////////////////////////////////////////////////////
//  Import data from text file and populate Exome  vectors              //
//////////////////////////////////////////////////////////////////////////

void getExome( Exome& exome, const string inFile, const unsigned int skip ){
  
	ifstream inData;
	string line, next_value;
	vector< vector< string > > newData;

	inData.open( inFile.c_str() ); // opens the file
	
	if( !inData ){ // file couldn't be opened
		cerr << "Error: " << inFile << " could not be opened" << endl;
		exit(1);
	}

	int inFileColumn = 0;
	unsigned int rowNumber = 0;

	while( !inData.eof() ){

		inFileColumn = 0;
		string line;
		getline( inData, line );

		if( !line.empty() && rowNumber >= skip ){

			stringstream ss( line );

			while( ss >> next_value ){
      
				if( inFileColumn == 0 ){
					exome.Chromosome.push_back( next_value );
					inFileColumn++;
				}

				else if( inFileColumn == 1 ){
					exome.Start.push_back( atol(next_value.c_str() ) );
					inFileColumn++;
				}
      
				else if( inFileColumn == 2 ){
				        exome.Stop.push_back( atol( next_value.c_str() ) );
					inFileColumn++;
				}

			}
		
		}

		rowNumber++;
	}
	
    inData.close();
}

////////////////////////////////////////////////////////////////////////////
//  Print pileup                                                          //
////////////////////////////////////////////////////////////////////////////

void printPileup( Pileup const& pileup ){

  for( unsigned int i = 0; i < pileup.Chromosome.size(); i++ ){

    cout << pileup.Chromosome[i] << "\t" << pileup.Position[i] << "\t" 
         << pileup.Reads[i] << "\t" << pileup.QualityScores[i] << endl;
  }
}


void printPileup( Pileup const& pileup, unsigned int startRow, unsigned int stopRow ){

  for( unsigned int i = startRow; i <= stopRow; i++ ){

    cout << pileup.Chromosome[i] << "\t" << pileup.Position[i] << "\t" 
         << pileup.Reads[i] << "\t" << pileup.QualityScores[i] << endl;
  }
}

////////////////////////////////////////////////////////////////////////////
//  Print exome                                                           //
////////////////////////////////////////////////////////////////////////////

void printExome( Exome const& exome ){

  for( unsigned int i = 0; i < exome.Chromosome.size(); i++ ){

    cout << exome.Chromosome[i] << "\t" << exome.Start[i] << "\t" << exome.Stop[i] << endl;
  }
}


void printExome( Exome const& exome, unsigned int startRow, unsigned int stopRow ){

  for( unsigned int i = startRow; i <= stopRow; i++ ){

    cout << exome.Chromosome[i] << "\t" << exome.Start[i] << "\t" << exome.Stop[i] << endl;
  }
}

///////////////////////////////////////////////////////////////////////////////////
// Define a funtion that returns true if ranking( chrom1 ) < ranking(chrom2)     //
// false otherwise                                                               //
///////////////////////////////////////////////////////////////////////////////////

inline bool chromosomeRanking( const string chrom1, const string chrom2 ){

  // chrom1 and chrom2 are both numeric
  if( chrom1 != "X" && chrom1 != "Y" && chrom2 != "X" && chrom2 != "Y" )
    return atol(chrom1.c_str()) < atol(chrom2.c_str());

  // chrom1 is numeric and chrom2 is non-numeric
  else if( ( chrom1 != "X" && chrom1 != "Y" ) && ( chrom2 == "X" || chrom2 == "Y" ) )
    return true;
	   
  // chrom1 is non-numeric and chrom2 is numeric
  else if( ( chrom1 == "X" || chrom1 == "Y" ) && ( chrom2 != "X" && chrom2 != "Y" ) )
    return false;
	   
  // chrom1 == X and chrom2 == X
  else if( chrom1 == "X" && chrom2 == "X")
    return false;

  // chrom1 == X and chrom2 == Y
  else if( chrom1 == "X" && chrom2 == "Y")
    return true;

  // chrom1 == Y
  else if( chrom1 == "Y" )
    return false;

  // Any other chromosome values are invalid
  else{
    cerr << "ERROR: Invalid chromosome value." << endl;
    exit(1);
  }
}

////////////////////////////////////////////////////////////////
// Define map to get bounds for chromosomes in exome file     //
////////////////////////////////////////////////////////////////

map< string, pair<unsigned int, unsigned int> > getChromosomeRanges( Exome const& exome ){


   map< string, pair<unsigned int, unsigned int> > chromosomeRanges;

   // Define bounds to be a pair of iterators over a vector<string> to hold lower and upper bounds
   pair< vector<string>::iterator, vector<string>::iterator > bounds;


  vector< string > Chromosomes = exome.Chromosome; // Make a copy of exome.Chromosome for list of unique chromosomes
  vector< string > cloneChromosome = exome.Chromosome; // Make a copy of exome.Chromosome for computing range

  vector<string>::iterator duplicateChromosomes;

  duplicateChromosomes = unique( Chromosomes.begin(), Chromosomes.end() );
  
  Chromosomes.resize( duplicateChromosomes - Chromosomes.begin() );
 
  unsigned int chrom_start = 0, chrom_stop = 0;

  for( unsigned int i = 0; i < Chromosomes.size(); i++ ){

    bounds = equal_range( cloneChromosome.begin(), cloneChromosome.end(), Chromosomes[i], chromosomeRanking );

    chrom_start = (unsigned int)( bounds.first -cloneChromosome.begin() );
    chrom_stop  = (unsigned int)( bounds.second - cloneChromosome.begin() - 1 );

    if( chrom_stop < chrom_start ){
      cerr << "ERROR: Invalid chromosome range -- chrom_stop < chrom_start" << endl;
      exit(1);
    }
  
    pair< unsigned int, unsigned int> chrom_bounds( chrom_start, chrom_stop );

    chromosomeRanges.insert( pair<string, pair<unsigned int, unsigned int> >( Chromosomes[i], chrom_bounds ) );

   }

  return chromosomeRanges;
}



////////////////////////////////////////////////////////////////////////////////////
// Implement binary search to find largest Exome.Start that is <= Pileup.Position //
////////////////////////////////////////////////////////////////////////////////////

unsigned int binarySearchExome( Exome const& exome, unsigned int startRow, unsigned int stopRow, unsigned int pileupPosition ){

  unsigned int first = startRow, last = stopRow;

  if( first > last || last == UINT_MAX)
    return last; //Largest row index with value <= target

  else{

    unsigned int middle = ( first + last )/2;
		
    if( pileupPosition == exome.Start[middle] )
      return middle;

    else if( pileupPosition < exome.Start[middle] )
      return binarySearchExome( exome, startRow, middle - 1, pileupPosition );

    else
      return binarySearchExome( exome, middle + 1, stopRow, pileupPosition );
  }
}


///////////////////////////////////////////////////////////////
// Determine whether each genomic position is in an exon     //
///////////////////////////////////////////////////////////////

void inExome( Pileup const& pileup, Exome const& exome, vector<bool>& isExon ){

  map< string, pair< unsigned int, unsigned int > > exomeChromosomeRanges = getChromosomeRanges( exome );
  
  unsigned int chromosomeStart, chromosomeStop;

  for( unsigned int i = 0; i < pileup.Position.size(); i++ ){

    // For each row in pileup, get the CHROM value. Find the start and stop rows in exome for that chromosome.
    // Search those rows for an exon that overalaps POS. Return true if overlapping exon found, false otherwise.
    chromosomeStart = exomeChromosomeRanges[ pileup.Chromosome[i] ].first;
    chromosomeStop = exomeChromosomeRanges[ pileup.Chromosome[i] ].second;

    // Get row number in Exome of largest Exome.Start <= Pileup.Position
    // If search returns a value equal to UNIT_MAX (i.e. the largest possible unsigned integer )
    // then no exons were found in Exome that overlap Pileup.Position and isExon[i] should be false.
    unsigned int exonStart = binarySearchExome( exome, chromosomeStart, chromosomeStop, pileup.Position[i] ); 
    
    if( exonStart < UINT_MAX ){
      // Start from the exonStart row and iterate backward until an Exome.Stop >= Pileup.Position is found.
      // If such an Exome.Stop is found, then isExon[i] = true, else isExon[i] = false.
      
      unsigned int j = exonStart;

      while( isExon[i] == false && j >= chromosomeStart  && j < UINT_MAX ){

  	if( exome.Stop[j] >= pileup.Position[i] )
  	  isExon[i] = true;
	
  	j--;//When j == 0 this will cause j to roll back around to UINT_MAX. should then break out of while loop.
      }

    }

    else if( exonStart == UINT_MAX )
      isExon[i] = false;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////
// void computePHRED_Q(...)                                                              //
//                                                                                       //
// Convert string base-call quality codes to PHRED quality score                         //
// Convert each character in the string to its ASCII integer code and subtract 33        //
///////////////////////////////////////////////////////////////////////////////////////////

void computePHRED_Q( Pileup const& pileup, vector< unsigned int >& Q10,  
		     vector< unsigned int >& Q20, vector< unsigned int >& Q30, vector< unsigned int >& Q40 ){

  int PHRED_Q = 0;

  for( unsigned int i = 0; i < pileup.Chromosome.size(); i++ ){
      
    for( unsigned int j = 0; j < pileup.QualityScores[i].size(); j++ ){

      PHRED_Q = static_cast<int>( pileup.QualityScores[i].c_str()[j] ) - 33;
	  
	  if( PHRED_Q >= 10 )
		Q10[i]++;
		
	  if( PHRED_Q >= 20 )
		Q20[i]++;
		
	  if( PHRED_Q >= 30 )
		Q30[i]++;
		
	  if( PHRED_Q >= 40 )
	    Q40[i]++;
    }
  }
}


/////////////////////////////////////////
//  write PHRED Q scores to csv file   //
/////////////////////////////////////////

void  write_csv( string outfile, bool header, Pileup const& pileup, vector< unsigned int > const& Q10,
                 vector< unsigned int > const& Q20, vector< unsigned int > const& Q30, vector< unsigned int > const& Q40,
		 vector< bool > const& isExon ){
  ofstream csv;
  
  csv.open( outfile.c_str() );

  if( header )
    csv << "CHROM,POS,Q10,Q20,Q30,Q40,InExon" << endl;

  for( unsigned int i = 0; i < pileup.Chromosome.size(); i++ ){

    csv << pileup.Chromosome[i] << "," << pileup.Position[i] << "," << Q10[i] << "," << Q20[i] << "," 
        << Q30[i] << "," << Q40[i] << "," << boolalpha << isExon[i] << endl;

  }

  csv.close();
}

////////////////////////////////////////////////////////////
// Overload write_csv() to allow startRow and stopRow     //
////////////////////////////////////////////////////////////

void write_csv( string outfile, bool header, unsigned int startRow, unsigned int stopRow, 
                Pileup const& pileup, vector< unsigned int > const& Q10,
		vector< unsigned int > const& Q20, vector< unsigned int > const& Q30, vector< unsigned int > const& Q40,
		vector< bool > const& isExon ){

  ofstream csv;
  
  csv.open( outfile.c_str() );
  
  if( !csv ){ // file couldn't be opened
    cerr << "Error: " << csv << " could not be opened" << endl;
    exit(1);
  }

  if( header )
    csv << "CHROM,POS,Q10,Q20,Q30,Q40,InExon" << endl;

  for( unsigned int i = startRow; i <= stopRow; i++ ){

    csv << pileup.Chromosome[i] << "," << pileup.Position[i] << "," << Q10[i] << "," << Q20[i] << ","
        << Q30[i] << "," << Q40[i] << "," << boolalpha << isExon[i] << endl;

  }

  csv.close();
}



// END OF FILE
