CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: main

main: main.o client.o service.o cache.o
	$(CXX) $(CXXFLAGS) -o main main.o client.o service.o cache.o

main.o: main.cpp main.h cache.h service.h cache.h
	$(CXX) $(CXXFLAGS) -o $@ -c main.cpp

service.o: service.cpp service.h
	$(CXX) $(CXXFLAGS) -o $@ -c service.cpp

cache.o: cache.cpp cache.h
	$(CXX) $(CXXFLAGS) -o $@ -c cache.cpp

helpers.o: helpers.cpp helpers.h
	$(CXX) $(CXXFLAGS) -o $@ -c helpers.h

clean:
	rm -f *.o main
