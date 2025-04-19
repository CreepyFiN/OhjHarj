# Kääntäjä ja sen liput
CC = g++
CFLAGS = -Wall -std=c++17

# Lähdekooditiedostot ja käännettävien tiedostojen nimet
SRC = main.cpp minesweeper.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

# Rakenna kohde käännetyistä tiedostoista
all: $(TARGET)

# Käännä kohde
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Yksittäisten .cpp-tiedostojen käännös
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Poista ylimääräiset tiedostot
clean:
	rm -f $(OBJ) $(TARGET)

# Phony kohteet
.PHONY: all clean