default: complexn.o

complexn.o: complexn.cpp
	g++ -std=c++11 -c complexn.cpp

test: complexn.o tests.o
	g++ -std=c++11 -lm complexn.o tests.o -o run && ./run

tests.o: tests.cpp
	g++ -std=c++11 -c tests.cpp
clean:
	rm -rf *.o run
zip: 
	zip complexnumber complexn.cpp complexn.h tests.cpp README.txt makefile


