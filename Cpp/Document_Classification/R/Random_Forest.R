################################################################
# FILENAME   : Random_Forest.R
# AUTHOR     : Brian Denton
# DATE       : 11/08/2011
# DESCRIPTION: Implement random forest algorithm for comparison
#              with logistic regression.
# NOTE       : The random forest can generate highly accurate
#              predictions but it can take a VERY long time to
#              complete.  The model with 2000 training
#              documents took several days to complete on a very
#              fast 64-bit Linux server.
################################################################

#install.packages( "randomForest" )
library( randomForest )

ProjectPath <- '/home/nfs/dentonb/Projects/Document_Classification/'
ProgramPath <- paste( ProjectPath, "R/", sep = "" )
DataPath <- paste( ProjectPath, "Documents/", sep = "" )
OutputPath <- paste( ProjectPath, "R/", sep = "" )

setwd( DataPath )

Neg_X <- read.csv( file = "Neg_RelativeFrequency.csv.zip", header = FALSE )
Pos_X <- read.csv( file = "Pos_RelativeFrequency.csv.zip", header = FALSE )

Neg_Y <- rep( 0, ncol(Neg_X) )
Pos_Y <- rep( 1, ncol(Pos_X) )

SelectData <- function( N_Pos_Training, N_Neg_Training, N_Pos_Test, N_Neg_Test ){

  Pos_Rows <- 1:nrow(Pos_X)
  Pos_Training_Rows <- sample( x = Pos_Rows, size = N_Pos_Training, replace = FALSE )
  Pos_Rows[ !( Pos_Rows %in% Pos_Training_Rows) ]
  Pos_Test_Rows <- sample( x = Pos_Rows, size = N_Pos_Test, replace = FALSE )
  
  Neg_Rows <- 1:nrow(Neg_X)
  Neg_Training_Rows <- sample( x = Neg_Rows, size = N_Neg_Training, replace = FALSE )
  Neg_Rows[ !( Neg_Rows %in% Neg_Training_Rows) ]
  Neg_Test_Rows <- sample( x = Neg_Rows, size = N_Neg_Test, replace = FALSE )
  
  Training_X <- rbind( Pos_X[ Pos_Training_Rows, ], Neg_X[ Neg_Training_Rows, ] )
  Training_Y <- as.factor( c( rep(1,N_Pos_Training), rep(0,N_Neg_Training) ) )

  Test_X <- rbind( Pos_X[ Pos_Test_Rows, ], Neg_X[ Neg_Test_Rows, ] )
  Test_Y <- as.factor( c( rep(1,N_Pos_Test), rep(0,N_Neg_Test) ) )
  
  return( list( Training_X = Training_X, Training_Y = Training_Y, Test_X = Test_X, Test_Y = Test_Y ) )

}

#################################################
# Do multiple simulations of random forest      #
# and record accuracy                           #
#################################################

RandomForest_ErrorRate <- NULL

for( simulation in 1:20 ){

  print( paste( "Simulation Number:", simulation ) )
  flush.console()
  
  data <- SelectData( N_Pos_Training = 500, N_Neg_Training = 500, N_Pos_Test = 1000, N_Neg_Test = 1000 )

  fit <- randomForest( y = data$Training_Y, x = data$Training_X,
                       ytest = data$Test_Y, xtest = data$Test_X,
                       replace = FALSE, importance = FALSE, do.trace = FALSE )

  PredictedClass <- ifelse( fit$test$votes[,1] > fit$test$votes[,2], 0, 1 )
  Accuracy <- prop.table( table( PredictedClass == as.numeric( data$Test_Y ) - 1 ) )

  ErrorRate <- Accuracy[["FALSE"]]

  RandomForest_ErrorRate <- c( RandomForest_ErrorRate, ErrorRate )
  
}

setwd( OutputPath )
save( RandomForest_ErrorRate, file = "RandomForest_ErrorRate.500Pos_500Neg.RData" )


# END OF FILE
