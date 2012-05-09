/*******************************************************
FILENAME   : NGS_CCDF.cpp
AUTHOR     : Brian Denton <dentonb@mskcc.org>
DATE       : 08/18/2011
DESCRIPTION: Computations for complementary CDF
             for next generation sequencing data.
*******************************************************/

#include "NGS_CCDF.hpp"

using namespace std;

int main( int argc, char* argv[] ){

  if( argc < 4 || argc > 5 ){
    cerr << "ERROR: Incorrect number of parameters." << endl
         << "Usage: ./NGS_CCDF in_pileup in_exome out_Q_freq [boolHeader]" << endl;
    exit(1);
  }

  // Set parameter to print "CHROM,POS,Q10,Q20,Q30,Q40,InExome" header in csv files
  bool header = false;
  if( argc == 5 && string(argv[4]) == "true" )
    header = true;


  /////////////////////////////////////////////////////////
  // Confirm all input and output files can be accessed  //
  /////////////////////////////////////////////////////////

  ifstream inData;
  
  inData.open( argv[1] ); // Check pileup file exists
	
  if( !inData ){ // file couldn't be opened
    cerr << "Error: " << argv[1] << " could not be opened" << endl;
    exit(1);
  }

  inData.close();

  inData.open( argv[2] ); // Check exome file exists
	
  if( !inData ){ // file couldn't be opened
    cerr << "Error: " << argv[2] << " could not be opened" << endl;
    exit(1);
  }

  inData.close();

  ofstream csv;

  csv.open( argv[3] ); // Check output file can be written
	
  if( !csv ){ // file couldn't be opened
    cerr << "Error: " << argv[3] << " could not be opened" << endl;
    exit(1);
  }

  csv.close();

  //////////////////////////////////////////////////////////
  // Allocate variables to time algorithm                 //
  //////////////////////////////////////////////////////////

  time_t importPileupStartTime, importPileupStopTime, importExomeStartTime, importExomeStopTime,
         inExomeStartTime, inExomeStopTime, phredStartTime, phredStopTime, csvStartTime, csvStopTime;

  ////////////////////////
  // Import the pileup  //
  ////////////////////////

  time( &importPileupStartTime );
  Pileup pileup;                // Allocate Pileup struct
  getPileup( pileup, argv[1] ); // Initialize Pileup struct by passing reference to pileup and name of file containing data
  time( &importPileupStopTime );
  cout << "Elapsed time to import pileup: " << difftime( importPileupStopTime, importPileupStartTime ) << endl;

  ////////////////////////
  // Import the exome   //
  ////////////////////////

  time( &importExomeStartTime );
  Exome exome;
  getExome( exome, argv[2] );
  time( &importExomeStopTime );
  cout << "Elapsed time to import exome: " << difftime( importExomeStopTime, importExomeStartTime ) << endl;

  ///////////////////////////////////////////////////////////
  // Determine if each position in pileup is in the exome  //
  ///////////////////////////////////////////////////////////

  time( &inExomeStartTime );
  vector< bool > isExon( pileup.Chromosome.size(), false );
  inExome( pileup, exome, isExon );
  time( &inExomeStopTime );
  cout << "Elapsed time for inExome: " << difftime( inExomeStopTime, inExomeStartTime ) << endl;


  ////////////////////////////////////////////////////////////////////////////
  // For each position in pileup count depth of coverage among reads with   //
  // quality score Q>10, Q>20, Q>30, and Q>40.                              //
  ////////////////////////////////////////////////////////////////////////////

  time( &phredStartTime );
  vector< unsigned int > Q10( pileup.Chromosome.size(), 0 );
  vector< unsigned int > Q20( pileup.Chromosome.size(), 0 );
  vector< unsigned int > Q30( pileup.Chromosome.size(), 0 );
  vector< unsigned int > Q40( pileup.Chromosome.size(), 0 );

  computePHRED_Q( pileup, Q10, Q20, Q30, Q40 );
  time( &phredStopTime );
  cout << "Elapsed time for computePHRED: " << difftime( phredStopTime, phredStartTime ) << endl;

  //////////////////////////////////
  // Write results to a csv file  //
  //////////////////////////////////

  time( &csvStartTime );
  write_csv( argv[3], header, pileup, Q10, Q20, Q30, Q40, isExon );
  time( &csvStopTime );
  cout << "Elapsed time for write_csv: " << difftime( csvStopTime, csvStartTime ) << endl;

  return 0;
}

// END OF FILE
