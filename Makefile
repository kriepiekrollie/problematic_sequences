CXX = g++
CXXFLAGS = -Wall -g -fopenmp

SRC = main.cpp args.cpp search.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o bin/$(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) bin/$(TARGET)

.PHONY: all clean
