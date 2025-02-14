# Compiler
CXX = g++-14
CXXFLAGS = -std=c++20 libraries/*

# Targets
all: main

# Compile Main Program
main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

# Run the compiled program
run: main
	./main

# Clean build files
clean:
	rm -f main
