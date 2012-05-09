/*******************************************************
FILENAME   : DocumentClassification.cpp
AUTHOR     : Brian Denton
DATE       : 10/07/2011
DESCRIPTION: 
*******************************************************/

#include "DocumentClassification.hpp"

using namespace std;

int main( int argc, char* argv[] ){

  //////////////////////////////////
  // Simulation parameters        //
  //////////////////////////////////

  const string NegFile = "/home/nfs/dentonb/Projects/Document_Classification/Documents/neg.txt";
  const string PosFile = "/home/nfs/dentonb/Projects/Document_Classification/Documents/pos.txt";
  const string VocFile = "/home/nfs/dentonb/Projects/Document_Classification/Documents/voc.txt";

  const unsigned int N_Pos_Training = 1000;
  const unsigned int N_Neg_Training = 1000;
  const unsigned int N_Pos_Test = 1000;
  const unsigned int N_Neg_Test = 1000;

  const double alpha_start = 1;
  const double alpha_stop = 1e-06;
  const double epsilon = 5e-03;
  const double ClassificationThreshold = 0.5;
  const unsigned int maxits = 5e03;
  const unsigned int NumberOfSimulations = 1;

  const bool WriteClassificationErrorVector2File = false;
  const string outFile = "Classification_Error_Rate.1000Pos_1000Neg.csv";

  //<Random Forest>//
  // To generate datasets for random forest estimation in R set this flag to true.
  const bool WriteRelativeFrequencies2File = false;

  ///////////////////////////////////////
  // Read in data files                //
  ///////////////////////////////////////

  vector< list< Node<long, unsigned int > > > NegRaw, PosRaw;
  vector< list< Node<long, double > > > Neg, Pos, Training_X, Test_X; 
  vector< string > Voc;

  cout << endl << "Importing raw data..." << endl;
  Corpus( NegRaw, NegFile );
  Corpus( PosRaw, PosFile );
  Vocabulary( Voc, VocFile );

  /////////////////////////////////////////////
  // Declare required variables              //
  /////////////////////////////////////////////

  vector< int > Training_Y, Test_Y;
  vector< double > theta( Voc.size(), 0 );
  vector< double > PredictedProbabilities( N_Pos_Test + N_Neg_Test, 0 );
  double errorRate;
  vector< int > Test_Classification( N_Pos_Test + N_Neg_Test, 0 );
  Discriminator discrim;
  vector< Discriminator > Discriminators;

  ////////////////////////////////////////////////////////////////////
  // Compute relative frequency of words within each document in    //
  // PosRaw and NegRaw                                              //
  ////////////////////////////////////////////////////////////////////

  cout << endl << "Computing relative frequency of words in documents..." << endl;
  RelativeFrequency( NegRaw, Neg );
  RelativeFrequency( PosRaw, Pos );

  /////////////////////////////////////////////////////////////////////
  // If needed for a later analysis, write the relative frequency    //
  // matrices to csv files - i.e. not in linked list format.         //
  /////////////////////////////////////////////////////////////////////

  if( WriteRelativeFrequencies2File ){

    cout << endl << "Writing relative frequencies to csv files..." << endl;
    const string NegRelativeFrequencyCsv = "/home/nfs/dentonb/Projects/Document_Classification/Documents/Neg_RelativeFrequency.csv";
    const string PosRelativeFrequencyCsv = "/home/nfs/dentonb/Projects/Document_Classification/Documents/Pos_RelativeFrequency.csv";

    WriteCorpus2File( Neg, Voc, NegRelativeFrequencyCsv );
    WriteCorpus2File( Pos, Voc, PosRelativeFrequencyCsv );

  }

  ////////////////////////////////////////////////////////////////////////////
  //************************************************************************//
  //*                                                                      *//
  //* Compute the logisitic regression implemented in the following steps  *//
  //* several times and record the classification error for each           *//
  //*                                                                      *//
  //************************************************************************//
  ////////////////////////////////////////////////////////////////////////////

  vector< double > ClassificationErrorRateVector;

  for( unsigned int simulation = 0; simulation < NumberOfSimulations; simulation++ ){//Begin simulation loop

    cout << endl << endl;
    cout << "*********************************" << endl
	 << "---------------------------------" << endl
	 << "  Simulation Number: " << simulation + 1 << endl
	 << "---------------------------------" << endl
	 << "*********************************" << endl;

    ////////////////////////////////////////////////////////////////////
    // Identify training and test datasets                            //
    ////////////////////////////////////////////////////////////////////

    cout << endl << "Selecting training and test datasets..." << endl;

    SelectData( Pos, Neg, N_Pos_Training, N_Neg_Training, N_Pos_Test, N_Neg_Test, Training_Y, Training_X, Test_Y, Test_X );

    ////////////////////////////////////////////////////////////////////
    //   Train logistic regression model
    //   1. Specify stopping criteria: alpha, epsilon, maxits
    //   2. Compute relative frequency of words in neg and pos
    //   3. Initialize theta vector
    //   4. Compute log-likelihood
    //   5. Compute gradient vector
    //   6. Do line search and update theta vector
    //   7. Check convergence
    //   8. Iterate until stopping condition obtained
    //////////////////////////////////////////////////////////////////////

    cout << endl << "Training logistic model..." << endl;

    TrainLogistic( Training_Y, Training_X, theta, alpha_start, alpha_stop, epsilon, maxits );

    //////////////////////////////////////////////////////////////////////
    // Compute predicted probabilities for test dataset                 //
    //////////////////////////////////////////////////////////////////////

    cout << endl << "Computing predicted probabilities for test dataset..." << endl; 

    PredictionProbabilities( Test_Y, Test_X, theta, PredictedProbabilities );

    //////////////////////////////////////////////////////////////////////
    // Determine classification error rate
    //////////////////////////////////////////////////////////////////////

    cout << endl << "Computing classification error rate..." << endl;

    Classification( PredictedProbabilities, Test_Classification, ClassificationThreshold );
    errorRate = ClassificationErrorRate( Test_Y, Test_Classification );

    cout << endl <<"Classification Error Rate: " << setw(6) << setprecision(4) << errorRate << endl;

    ClassificationErrorRateVector.push_back( errorRate );

    ////////////////////////////////////////////////////////////
    // Get 10 best discriminators for Pos and Neg documents   //
    ////////////////////////////////////////////////////////////

    for( unsigned int i = 0; i < Voc.size(); i++ ){
    
      discrim.word = Voc[i];
      discrim.theta = theta[i];   
      Discriminators.push_back( discrim );

    }

    sort( Discriminators.begin(), Discriminators.end() );

    cout << endl << "*** 10 best discriminators for Neg documents *** " << endl;
    cout << endl << setw(10) << "theta" << setw(20) << "word";
    cout << endl << setw(10) << "----------" << setw(20) << "--------------------" << endl;
    for( unsigned int i = 0; i < 10; i++ )
      cout << setw(10) << Discriminators[i].theta << setw(20) << Discriminators[i].word << endl;

    cout << endl << "*** 10 best discriminators for Pos documents *** " << endl;
    cout << endl << setw(10) << "theta" << setw(20) << "word";
    cout << endl << setw(10) << "----------" << setw(20) << "--------------------" << endl;
    for( unsigned int i =  Discriminators.size() - 10; i < Discriminators.size(); i++ )
      cout << setw(10) << Discriminators[i].theta << setw(20) << Discriminators[i].word << endl;


    ///////////////////////////////////////////////////
    // Clear data for next iteration                 // 
    ///////////////////////////////////////////////////
    Training_X.clear();
    Training_Y.clear();
    Test_X.clear();
    Test_Y.clear();
    PredictedProbabilities.clear();
    Test_Classification.clear();
    theta.clear();
    Discriminators.clear();
  }//End simulation loop
  
  //////////////////////////////////////////////////////////
  // Write classification error rate vector to text file  //
  //////////////////////////////////////////////////////////

  if( WriteClassificationErrorVector2File ){

    ofstream outData;

    outData.open( outFile.c_str() ); // opens the file
	
    if( !outData ){ // file couldn't be opened
      cerr << "Error: " << outFile << " could not be opened" << endl;
      exit(1);
    }

    for( unsigned int i = 0; i < ClassificationErrorRateVector.size(); i++ ){

      outData << ClassificationErrorRateVector[i] << endl;

    }

    outData.close();

  }



  cout << endl << "Code completed." << endl;

  return 0;

}

// END OF FILE
