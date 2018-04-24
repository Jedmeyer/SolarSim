bodygroupdriver: bodygroupdriver.o bodygroup.o body.o
	g++ -g -Wall -std=c++11 -o bodygroupdriver bodygroupdriver.o bodygroup.o body.o

bodygroupdriver.o: bodygroupdriver.cpp bodygroup.h body.h
	g++ -g -Wall -std=c++11 -c bodygroupdriver.cpp

bodydriver: bodydriver.o body.o 
	g++ -g -Wall -std=c++11 -o bodydriver bodydriver.o body.o

bodygroup.o: bodygroup.o body.o body.h bodygroup.h
	g++ -g -Wall -std=c++11 -c bodygroup.cpp

bodydriver.o: bodydriver.cpp body.h
	g++ -g -Wall -std=c++11 -c bodydriver.cpp

body.o: body.cpp body.h
	g++ -g -Wall -std=c++11 -c body.cpp
