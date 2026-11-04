CXX = g++
CXXFLAGS = -Wall -std=c++11

# typing "make" compiles the program, runs it, then removes the program file
run: main.cpp
	$(CXX) $(CXXFLAGS) -o lab10 main.cpp
	./lab10
	rm -f lab10

clean:
	rm -f lab10

.PHONY: run clean