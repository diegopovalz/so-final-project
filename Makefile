CC = gcc
CFLAGS = -Wall -g
INSTRUMENT_FLAGS = -finstrument-functions

.PHONY: all clean

all: main profiler

main: main.o instrument.o
	$(CC) $(CFLAGS) $(INSTRUMENT_FLAGS) main.c instrument.o -o main
	rm -f main.o instrument.o

profiler: profiler.o
	$(CC) $(CFLAGS) -o profiler profiler.o
	rm -f profiler.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

instrument.o: instrument.c
	$(CC) $(CFLAGS) -c instrument.c

profiler.o: profiler.c
	$(CC) $(CFLAGS) -c profiler.c

clean:
	rm -f main profiler *.o
