CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude  
LDLIBS = -lm  
SRC = src/main.c src/graphics.c src/validation.c src/polish_notation.c src/data_structures.c src/parsing.c  
TARGET = program

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET)