# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

# Files
SRC = ai.cpp MainGame.cpp Board.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = Tic-Tac-Toe

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -vf $(wildcard *.o) $(TARGET)

.PHONY: clean
