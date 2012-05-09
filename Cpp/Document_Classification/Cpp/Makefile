SOURCE     = DocumentClassification.cpp
EXECUTABLE = DocumentClassification
LIB_DIR    = /home/nfs/dentonb/Projects/Document_Classification/Cpp
FAST       = "-O3 -fno-exceptions -fno-rtti"

all:
	g++ -Wall -o $(EXECUTABLE) $(SOURCE)
	# g++ -Wall -fPIC -c Logistic.cpp -o Logistic.o
	# g++ -Wall -shared Logistic.o -o libLogistic.so
	# g++ -Wall -o $(EXECUTABLE) $(SOURCE) -Wl,-rpath -Wl,. -L $(LIB_DIR) -l Logistic
	chmod u+x $(EXECUTABLE)