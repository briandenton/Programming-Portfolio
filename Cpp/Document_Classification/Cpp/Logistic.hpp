/*******************************************************
FILENAME   : Logistic.hpp
AUTHOR     : Brian Denton
DATE       : 11/03/2011
DESCRIPTION: 
*******************************************************/

#ifndef LOGISTIC_H
#define LOGISTIC_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <math.h>

#include "Node.hpp"

//////////////////////////////////////////////////////////////////////
// Function to compute sum( theta[i] * x[i], i = 1,...,n[j] )       //
// for word i in document j                                         //
//////////////////////////////////////////////////////////////////////

template< class T1, class T2 >
std::vector<double> SumThetaX( std::vector< std::list< Node<T1,T2> > > const& Corpus, std::vector< double > const& theta ){

  std::list< Node<T1,T2> > document;

  std::vector<double> sumThetaX( Corpus.size(), 0 );

  typename std::list< Node<T1,T2> >::iterator k;

  double theta_k, X_k;

  for( unsigned int i = 0; i < Corpus.size(); ++i ){

    document = Corpus[i];

    for( k = document.begin(); k != document.end(); ++k ){

      theta_k = (double)theta[ (*k).index ];
      X_k = (double)(*k).value;
      sumThetaX[i] += theta_k * X_k;
    }

    document.clear();

  }

  return sumThetaX;

}

///////////////////////////////////////////
// Log-Likelihood                        //
// dim( LogLikelihood ) = ( n, 1)        //
///////////////////////////////////////////

template< class T1, class T2 >
double LogLikelihood( std::vector< std::list< Node<T1,T2> > > const& Corpus,
                       std::vector< double > const& theta,
		      std::vector<int> const& Y ){
  double logLikelihood = 0;

  std::vector<double> sumThetaX = SumThetaX( Corpus, theta );

  for( unsigned int i = 0; i < Corpus.size(); i++ ){

    logLikelihood += -log( 1 + exp( -Y[i] * sumThetaX[i] ) );

  }

  return logLikelihood;

}


///////////////////////////////////////////
// A = exp( -Y * sum( theta * X ) )      //
// dim(A) = ( n, 1 )                     //
///////////////////////////////////////////

template< class T1, class T2 >
std::vector<double> A( std::vector< std::list< Node<T1,T2> > > const& Corpus,
                       std::vector< double > const& theta,
                       std::vector<int> const& Y ){

  std::vector<double> a( Corpus.size(), 0 );

  std::vector<double> sumThetaX = SumThetaX( Corpus, theta );

  for( unsigned int i = 0; i < a.size(); i++ ){
    a[i] = exp( -Y[i] * sumThetaX[i] );
  }
  
  return a;

}

///////////////////////////////////////////
// Gradient                              //
// dim( Gradient ) = ( k, 1 )            //
///////////////////////////////////////////

template< class T1, class T2 >
std::vector<double> Gradient( std::vector< std::list< Node<T1,T2> > > const& Corpus,
                              std::vector< double > const& theta,
                              std::vector<int> const& Y ){

  std::vector<double> gradient( theta.size(), 0 );
  std::vector<double> a = A( Corpus, theta, Y );

  unsigned int k;

  T2 fXk;
  
  std::list< Node<T1,T2> > document;

  typename std::list< Node<T1,T2> >::iterator j;

  for( unsigned int i = 0; i < Corpus.size(); ++i ){

    document = Corpus[i];

    for( j = document.begin(); j != document.end(); ++j ){

      k = (unsigned int)(*j).index;
      fXk = (*j).value;


      gradient[k] += Y[i] * fXk * a[i]/( 1 + a[i] );
    }

    document.clear();

  }
  
  return gradient;

}

///////////////////////////////////////////
// Update Theta with Line Search         //
///////////////////////////////////////////

template< class T1, class T2 >
void UpdateTheta( std::vector< std::list< Node<T1,T2> > > const& X,
                               std::vector< double >& theta,
		               std::vector<int> const& Y, 
		               const double alpha_start, const double alpha_stop ){

  double alpha = alpha_start, logLikelihood, newLogLikelihood;
  std::vector<double> gradient = Gradient( X, theta, Y );
  std::vector<double> new_theta = theta;

  logLikelihood = 99999999;
  newLogLikelihood = -99999999999;

  while( logLikelihood > newLogLikelihood && alpha > alpha_stop ){

    for( unsigned int k = 0; k < new_theta.size(); ++k ){
      new_theta[k] = theta[k] + alpha * gradient[k];
    }

    logLikelihood = LogLikelihood( X, theta, Y );
    newLogLikelihood = LogLikelihood( X, new_theta, Y );

    alpha = alpha/2;
  }

  theta = new_theta;

}



/////////////////////////////////////////////////////////////
// Implement logistic regresion using gradient descent     //
// to maximize log-likelihood                              //
/////////////////////////////////////////////////////////////

template< class T1, class T2 >
void TrainLogistic( std::vector< int > const& Training_Y,
               std::vector< std::list< Node<T1,T2> > > const& Training_X,
	       std::vector< double >& theta,
	       const double alpha_start, const double alpha_stop,
               const double epsilon, const unsigned int maxits ){

  double logLikelihood, newLogLikelihood;
  unsigned int iter = 0;

  logLikelihood = 999999;
  newLogLikelihood = -9999999;

  while( fabs( newLogLikelihood - logLikelihood ) > epsilon && iter < maxits ){

    logLikelihood = newLogLikelihood;

    UpdateTheta( Training_X, theta, Training_Y, alpha_start, alpha_stop );

    newLogLikelihood = LogLikelihood( Training_X, theta, Training_Y );

    if( iter % 100 == 0 ){

      std::cout << "Logistic Regression Iteration: " << std::setw(5) << iter << "\t"
      		<< "Log-Likelihood: " << std::setw(8) << newLogLikelihood << "\t"
      		<< "abs( Change in Log-Likelihood ): " << std::setw(12) << fabs( newLogLikelihood - logLikelihood ) << std::endl;
    }

    iter++;

  }

  std::cout << "Logistic Regression Iteration: " << std::setw(5) << iter << "\t"
  	    << "Log-Likelihood: " << std::setw(8) << newLogLikelihood << "\t"
  	    << "abs( Change in Log-Likelihood ): " << std::setw(12) << fabs( newLogLikelihood - logLikelihood ) << std::endl;

  if( iter == maxits ){

    std::cout << "WARNING: Algorithm did not converge." << std::endl;

  }

}


/////////////////////////////////////////////////////////////
// Compute predicted probabilties using obtained           //
// theta vector                                            //
/////////////////////////////////////////////////////////////
template< class T1, class T2 >
void PredictionProbabilities( std::vector< int > const& Test_Y,
			      std::vector< std::list< Node<T1,T2> > > const& Test_X,
			      std::vector< double > const& theta,
			      std::vector< double >& PredictedProbabilities ){

  std::vector< double > sumThetaX = SumThetaX( Test_X, theta );

  double denominator;

  for( unsigned int i = 0; i < PredictedProbabilities.size(); ++i ){

    denominator = exp( -Test_Y[i] * sumThetaX[i] );
    
    PredictedProbabilities[i] = 1/(1 + exp( -sumThetaX[i] ));

  }

}

/////////////////////////////////////////////////////////////
// Compute classification and error rate                   //
/////////////////////////////////////////////////////////////

void Classification( std::vector< double > const& PredictedProbabilities,
		     std::vector< int >& Test_Classification,
		     const double threshold ){

  for( unsigned int i = 0; i < Test_Classification.size(); ++i ){

    if( PredictedProbabilities[i] < threshold )
      Test_Classification[i] = -1;
    else if( PredictedProbabilities[i] >= threshold )
      Test_Classification[i] = 1;
  }

}

double ClassificationErrorRate( std::vector< int > const& Test_Y,
				std::vector< int > const& Test_Classification ){

  unsigned int IncorrectClassification = 0;

  for( unsigned int i = 0; i < Test_Classification.size(); ++i ){

    if( Test_Y[i] != Test_Classification[i] )
      IncorrectClassification++;
  }

  return (double)IncorrectClassification/Test_Y.size();

}


#endif

// END OF FILE
