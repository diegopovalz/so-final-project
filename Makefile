CC = gcc
CFLAGS = -Wall -O2
TARGET = profiler
SRC = profiler.c
OBJ = $(SRC:.c=.o)

all: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
