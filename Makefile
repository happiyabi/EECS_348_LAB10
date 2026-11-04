CXX = g++
CXXFLAGS = -Wall -std=c++11

lab6: main.o matrix.o
	$(CXX) $(CXXFLAGS) -o lab6 main.o matrix.o

main.o: main.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c main.cpp

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp

clean:
	rm -f *.o lab6