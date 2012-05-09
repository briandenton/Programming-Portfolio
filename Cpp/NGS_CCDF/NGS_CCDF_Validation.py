##################################################################
# FILENAME   : NGS_CCDF_Validation.py
# AUTHOR     : Brian Denton <dentonb@mskcc.org>
# DATE       : 08/30/2011
# DESCRIPTION: This Python script validates the results from the 
#              NGS_CCDF application. It uses a different approach
#              to scan the exome file. Specifically, it uses a 
#              sequential search rather than a binary search.
#              This makes it take much longer to complete, but
#              because it uses a different (and arguably simpler)
#              approach it provides a means to check the results
#              from NGS_CCDF.  But it is practical to run this
#              only on very small subsets of the data - e.g. the
#              example pileup and exome provided.
##################################################################

import string 

pileupFile = "example.pileup"
exomeFile = "example.exome.bed"
ngs_ccdfFile = "example.csv"


###################################################################
# Immediately test that pileup, exome, and NGS_CCDF results are   #
# accessible. If not, throw exception and exit program.           #
###################################################################

try:
	pileupTest = open( pileupFile, "r" )
	pileupTest.close()
except:
	print "ERROR: Cannot open file", pileupFile
	from sys import exit
	exit(1)
	
try:
	exomeTest = open( exomeFile, "r" )
	exomeTest.close()
except:
	print "ERROR: Cannot open file", exomeFile
	from sys import exit
	exit(1)

try:
	ngs_ccdfTest = open( ngs_ccdfFile, "r" )
	ngs_ccdfTest.close()
except:
	print "ERROR: Cannot open file", ngs_ccdfFile
	from sys import exit
	exit(1)

#######################
# Import pileup file  #
#######################

# Define Pileup class
class Pileup:
	def __init__( self, pileupFile, compute_Q_Frequencies = False ):
		"""Implementation of a Pileup class"""
		
		# Declare lists to hold pileup columns
		self.Chromosome = []
		self.Position = []
		self.Reference = []
		self.Reads = []
		self.QualityScores = []

		# Open file and parse into lists
		pileupConnection = open( pileupFile, "r" )
		
		for line in pileupConnection:
			line = line.strip( '\n' )
			line = line.split()
			self.Chromosome.append( line[0] )
			self.Position.append( long( line[1] ) ) #Make position long int
			self.Reference.append( line[2] )
			self.Reads.append( line[3] )
			self.QualityScores.append( line[4] )
		
		pileupConnection.close()
		
		# Conditionally compute quality score frequencies at time of object initialization
		if( compute_Q_Frequencies ):
			self.compute_Q_Frequencies()
		
	def compute_Q_Frequencies( self ):
		self.Q10 = [0]*len(self.QualityScores)
		self.Q20 = [0]*len(self.QualityScores)
		self.Q30 = [0]*len(self.QualityScores)
		self.Q40 = [0]*len(self.QualityScores)
		
		""" Each element in QualityScores is a string of ASCII characters representing
			The base call quality of each read in Reads. The ASCII characters are converted
			to base call qualities by converting each character to its ASCII integer representation
			(using Python's ord() function) and then subtracting 33. The counts for Q>10, Q>20, Q>30, 
			and Q>40 are incremented accordingly for each genomic position. """
			
		for i in range( len( self.Position ) ):					# Increment over genomic positions
			for j in range( len( self.QualityScores[i] ) ):		# Increment over quality scores at that position
				Q_score = ord( self.QualityScores[i][j] ) - 33	# Convert ASCII chars to quality scores
				
				if( Q_score >= 10 ):								# Increment frequency counts accordingly
					self.Q10[i] = self.Q10[i] + 1
				if( Q_score >= 20 ):
					self.Q20[i] = self.Q20[i] + 1
				if( Q_score >= 30 ):
					self.Q30[i] = self.Q30[i] + 1
				if( Q_score >= 40 ):
					self.Q40[i] = self.Q40[i] + 1
					
	def show( self, start = 0, stop = None ):
		# Set default parameters to print all elements in pileup.
		# Cannot pass a reference to self as a default parameter, so set it
		# equal to None. Then wihtin the function test if stop == None, and if so
		# set it equal to the length of the pileup
		if stop == None:
			stop = len( self.Chromosome )
		for i in range( start, stop ):
			print self.Chromosome[i], self.Position[i], self.Reference[i], self.Reads[i], self.QualityScores[i]
				
#######################
# Import exome file  #
#######################

# Define Exome class
class Exome:
	def __init__( self, exomeFile ):
		"""Implementation of an Exome class"""
		self.Chromosome = []
		self.Start = []
		self.Stop = []
	
		exomeConnection = open( exomeFile, "r" )
	
		for line in exomeConnection:
			line = line.strip( '\n' )
			line = line.split()
			self.Chromosome.append( line[0] )
			self.Start.append( long( line[1] ) )
			self.Stop.append( long( line[2] ) )

		exomeConnection.close()
		
	def show( self, start = 0, stop = None ):
		if stop == None:
			stop = len( self.Chromosome )
		for i in range( start, stop ):
			print self.Chromosome[i], self.Start[i], self.Stop[i]
	

##################################
# Instantiate pileup and exome   #
##################################
	
pileup = Pileup( pileupFile = pileupFile, compute_Q_Frequencies = True )
exome = Exome( exomeFile = exomeFile )

##############################################################
# Create dictionary giving chromosome ranges in exome file   #
##############################################################

ExomeChromosomeStart = dict()
ExomeChromosomeStop = dict()
	
CHROMOSOMES = ["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","X","Y"]
for chromosome in CHROMOSOMES:
	try:
		ExomeChromosomeStart[ chromosome ] = exome.Chromosome.index( chromosome )
		ExomeChromosomeStop[ chromosome ] = (len(exome.Chromosome) - 1 ) - exome.Chromosome[::-1].index( chromosome )
	except:
		print "NOTE: Chromosome", chromosome, "not found in exome."

# NOTE: When run on the provided example pileup and exome the above loop
#       will throw an exception for every chromosome except 22 because 22
#       is the only chromosome in the example files.
		
################################################################
# Check whether each genomic position in pileup is in an exon  #
################################################################

def inExome( pileup, exome ):
	# Initialize boolean vector that tells whether each genomic position in the pileup is in an exon
	inExome = [False]*len(pileup.Position)
	
	for p in range( len(pileup.Position) ):					# Iterate over genomic positions in pileup
	
		e = ExomeChromosomeStart[ pileup.Chromosome[p] ]	# Start scanning exome at start of current chromosome number
	
		""" If any exon [Start,Stop] is found that bound current genomic position from pileup
			then that position is in the exome. Set inExome[p] = True, exit while loop. If no,
			such exon interval is found, continue scanning until the entire exome is scanned for
			the current pileup chromosome.""" 
		while e <= ExomeChromosomeStop[ pileup.Chromosome[p] ] and inExome[p] == False:
			if pileup.Position[p] >= exome.Start[e] and pileup.Position[p] <= exome.Stop[e]:
				inExome[p] = True
			e = e + 1
	
	return inExome
	

inExome = inExome( pileup, exome )

###############################################
# Import results from NGS_CCDF for comparison #
###############################################

class NGS_CCDF:
	def __init__( self, ngs_ccdfFile ):
		"""Implementation of an NGS_CCDF class"""
		self.Chromosome = []
		self.Position = []
		self.Q10 = []
		self.Q20 = []
		self.Q30 = []
		self.Q40 = []
		self.inExome = []
	
		ngs_ccdfConnection = open( ngs_ccdfFile, "r" )
	
		for line in ngs_ccdfConnection:
			line = line.strip( '\n' )
			line = line.split(",")
			self.Chromosome.append( line[0] )
			self.Position.append( long( line[1] ) )
			self.Q10.append( long( line[2] ) )
			self.Q20.append( long( line[3] ) )
			self.Q30.append( long( line[4] ) )
			self.Q40.append( long( line[5] ) )
			if line[6].upper() == "TRUE":
				self.inExome.append( True )
			elif line[6].upper() == "FALSE":
				self.inExome.append( False )

		ngs_ccdfConnection.close()
	
NGS_CCDF = NGS_CCDF( ngs_ccdfFile )

#######################################################################
# Compare results computed with Python (i.e. in the Pileup object)    #
# with results computed by NGS_CCDF application. If the results match #
# the function below should return True.                              #
#######################################################################

def NGS_CCDF_Validated( pileup, NGS_CCDF ):
	i = 0
	validated = True
	while validated == True and i < len(pileup.Chromosome):
		if pileup.Chromosome[i] != NGS_CCDF.Chromosome[i]:
			validated = False
		if pileup.Position[i] != NGS_CCDF.Position[i]:
			validated = False
		if pileup.Q10[i] != NGS_CCDF.Q10[i]:
			validated = False
		if pileup.Q20[i] != NGS_CCDF.Q20[i]:
			validated = False
		if pileup.Q30[i] != NGS_CCDF.Q30[i]:
			validated = False
		if pileup.Q40[i] != NGS_CCDF.Q40[i]:
			validated = False
		if inExome[i] != NGS_CCDF.inExome[i]:
			validated = False
		i = i + 1
	
	return validated

print "\n\n\n*** Validation Test Results ***"
if NGS_CCDF_Validated( pileup, NGS_CCDF ) == True:
	print "PASS: The results in", ngs_ccdfFile, "have been validated."
else:
	print "FAIL: The results in", ngs_ccdfFile, "cannot be validated."
	
#END OF FILE
