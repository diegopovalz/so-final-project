all: clean profiler target

profiler: profiler.c
	gcc profiler.c -o profiler

instrumentation.o: instrumentation.c
	gcc -c -finstrument-functions instrumentation.c

target: target.c instrumentation.o
	gcc -finstrument-functions target.c instrumentation.o -o target

clean:
	rm -f profiler target instrumentation.o
