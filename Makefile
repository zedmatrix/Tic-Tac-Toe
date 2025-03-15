# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23
#LDFLAGS = -lncurses -ltinfo

# Files
SRC = ai.cpp MainGame.cpp Board.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = tictactoe-test

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm -vf $(wildcard *.o) $(TARGET)

.PHONY: clean
