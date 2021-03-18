tests: tests.cpp Replica.cpp ParallelTemper.cpp
	g++ -pthread -Wall -o tests tests.cpp Replica.cpp ParallelTemper.cpp

all: tests ;

clean:
	rm -f tests tests.o Replica.o ParallelTemper.o
