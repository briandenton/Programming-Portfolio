##################################################################
# FILENAME   : Accuracy_Boxplot.R
# AUTHOR     : Brian Denton
# DATE       : 11/07/2011
# DESCRIPTION: Generate boxplots of classification accuracy
#              for logistic regression and random forest
##################################################################

ProjectPath <- "/home/nfs/dentonb/Projects/Document_Classification/" 
CppPath <- paste( ProjectPath, "Cpp", sep = "" )
RPath <- paste( ProjectPath, "R", sep = "" )

setwd( CppPath )

Pos15_Neg15 <- read.csv( file = "Classification_Error_Rate.15Pos_15Neg.csv", header = FALSE )
names( Pos15_Neg15 ) <- c("ErrorRate")
Pos15_Neg15$TrainingDocs <- 30
Pos15_Neg15$Algorithm <- "Logistic"
  
Pos50_Neg50 <- read.csv( file = "Classification_Error_Rate.50Pos_50Neg.csv", header = FALSE )
names( Pos50_Neg50 ) <- c("ErrorRate")
Pos50_Neg50$TrainingDocs <- 100
Pos50_Neg50$Algorithm <- "Logistic"

Pos150_Neg150 <- read.csv( file = "Classification_Error_Rate.150Pos_150Neg.csv", header = FALSE )
names( Pos150_Neg150 ) <- c("ErrorRate")
Pos150_Neg150$TrainingDocs <- 300
Pos150_Neg150$Algorithm <- "Logistic"

Pos300_Neg300 <- read.csv( file = "Classification_Error_Rate.300Pos_300Neg.csv", header = FALSE )
names( Pos300_Neg300 ) <- c("ErrorRate")
Pos300_Neg300$TrainingDocs <- 600
Pos300_Neg300$Algorithm <- "Logistic"

Pos500_Neg500 <- read.csv( file = "Classification_Error_Rate.500Pos_500Neg.csv", header = FALSE )
names( Pos500_Neg500 ) <- c("ErrorRate")
Pos500_Neg500$TrainingDocs <- 1000
Pos500_Neg500$Algorithm <- "Logistic"

Pos1000_Neg1000 <- read.csv( file = "Classification_Error_Rate.1000Pos_1000Neg.csv", header = FALSE )
names( Pos1000_Neg1000 ) <- c("ErrorRate")
Pos1000_Neg1000$TrainingDocs <- 2000
Pos1000_Neg1000$Algorithm <- "Logistic"

setwd( RPath )

load( "RandomForest_ErrorRate.15Pos_15Neg.RData" )
RandomForest_ErrorRate.15Pos_15Neg <- as.data.frame(RandomForest_ErrorRate)
rm( RandomForest_ErrorRate )
names( RandomForest_ErrorRate.15Pos_15Neg ) <- c("ErrorRate")
RandomForest_ErrorRate.15Pos_15Neg$TrainingDocs <- 30
RandomForest_ErrorRate.15Pos_15Neg$Algorithm <- "Random Forest"

load( "RandomForest_ErrorRate.50Pos_50Neg.RData" )
RandomForest_ErrorRate.50Pos_50Neg <- as.data.frame(RandomForest_ErrorRate)
rm( RandomForest_ErrorRate )
names( RandomForest_ErrorRate.50Pos_50Neg ) <- c("ErrorRate")
RandomForest_ErrorRate.50Pos_50Neg$TrainingDocs <- 100
RandomForest_ErrorRate.50Pos_50Neg$Algorithm <- "Random Forest"

load( "RandomForest_ErrorRate.150Pos_150Neg.RData" )
RandomForest_ErrorRate.150Pos_150Neg <- as.data.frame(RandomForest_ErrorRate)
rm( RandomForest_ErrorRate )
names( RandomForest_ErrorRate.150Pos_150Neg ) <- c("ErrorRate")
RandomForest_ErrorRate.150Pos_150Neg$TrainingDocs <- 300
RandomForest_ErrorRate.150Pos_150Neg$Algorithm <- "Random Forest"

load( "RandomForest_ErrorRate.300Pos_300Neg.RData" )
RandomForest_ErrorRate.300Pos_300Neg <- as.data.frame(RandomForest_ErrorRate)
rm( RandomForest_ErrorRate )
names( RandomForest_ErrorRate.300Pos_300Neg ) <- c("ErrorRate")
RandomForest_ErrorRate.300Pos_300Neg$TrainingDocs <- 600
RandomForest_ErrorRate.300Pos_300Neg$Algorithm <- "Random Forest"

load( "RandomForest_ErrorRate.500Pos_500Neg.RData" )
RandomForest_ErrorRate.500Pos_500Neg <- as.data.frame(RandomForest_ErrorRate)
rm( RandomForest_ErrorRate )
names( RandomForest_ErrorRate.500Pos_500Neg ) <- c("ErrorRate")
RandomForest_ErrorRate.500Pos_500Neg$TrainingDocs <- 1000
RandomForest_ErrorRate.500Pos_500Neg$Algorithm <- "Random Forest"

load( "RandomForest_ErrorRate.1000Pos_1000Neg.RData" )
RandomForest_ErrorRate.1000Pos_1000Neg <- as.data.frame(RandomForest_ErrorRate)
rm( RandomForest_ErrorRate )
names( RandomForest_ErrorRate.1000Pos_1000Neg ) <- c("ErrorRate")
RandomForest_ErrorRate.1000Pos_1000Neg$TrainingDocs <- 2000
RandomForest_ErrorRate.1000Pos_1000Neg$Algorithm <- "Random Forest"


Accuracy <- rbind( Pos15_Neg15, Pos50_Neg50, Pos150_Neg150,
                   Pos300_Neg300, Pos500_Neg500, Pos1000_Neg1000,
                   RandomForest_ErrorRate.15Pos_15Neg,
                   RandomForest_ErrorRate.50Pos_50Neg,
                   RandomForest_ErrorRate.150Pos_150Neg,
                   RandomForest_ErrorRate.300Pos_300Neg,
                   RandomForest_ErrorRate.500Pos_500Neg,
                   RandomForest_ErrorRate.1000Pos_1000Neg )

pdf( file = "Classification_Error_Rate_Boxplot.pdf", width = 11, height = 8.5 )

boxplot( ErrorRate ~ TrainingDocs, data = subset( Accuracy, Algorithm == "Logistic" ),
         main = "Classification Error Rate",
         xlab = "Number of Training Documents",
         ylab = "Error Rate" )

dev.off()


pdf( file = "Classification_Error_Rate_Boxplot_Logistic_and_RandomForest.pdf", width = 11, height = 8.5 )

boxplot( ErrorRate ~ TrainingDocs, data = subset( Accuracy, Algorithm == "Logistic" ),
         at = 0:5*3 + 1, xlim = c(1,17),
         ylim = range( Accuracy$ErrorRate),
         xaxt = "n",
         boxcol = "blue",
         main = "Classification Error Rate",
         xlab = "Number of Training Documents",
         ylab = "Error Rate" )

boxplot( ErrorRate ~ TrainingDocs, data = subset( Accuracy, Algorithm == "Random Forest" ),
         at = 0:5*3 + 2, xaxt = "n",
         add = TRUE, boxcol = "red" )

axis(1, at = 0:5*3 + 1.5, labels = unique( Accuracy$TrainingDocs), tick = TRUE)
legend( "topright", legend = c("Logistic","Random Forest"), col = c("blue","red"), lty = c(1,1) )

dev.off()

# END OF FILE

