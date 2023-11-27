# so-final-project

## Simple C Memory and Execution Time Profiler

# Overview

This project implements a simple profiler in C to track memory usage and execution time of functions. It consists of three main components:

* profiler.c: Implements the memory usage logic.
* instrument.c: Contains instrumentation code to measure execution times.
* main.c: Uses the instrumentation code to measure CPU execution time.

## Prerequisites
* GCC compiler
* Make (to compile the project)
* Standard C library
* Linux environment (for sys/time.h and the gettimeofday function)

## Compilation
Use the provided Makefile for compiling the project. The Makefile includes the following important flags:

* -Wall: Enables all compiler's warning messages.
* -g: Generates debug information to be used by GDB debugger.
* -finstrument-functions: Automatically instruments function entry and exit points.

To compile, simply run:

```
make
```

# Running
After compilation, two executables are generated:

* main: The main application.
* profiler: The profiling tool.

## Run the CPU execution time application as follows:

```
./main
```

## Run the memory usage application as follows:

```
./profiler
```

Important Notes
* The __cyg_profile_func_enter and __cyg_profile_func_exit functions in instrument.c are crucial for profiling. They are called automatically at the start and end of each function call due to the -finstrument-functions flag.
* The profiler is currently set up to measure time using gettimeofday. It's important to note that this method may not be suitable for high-resolution time measurements.
* The output of the profiling (time taken by each function) is printed to the standard output (console).
* Ensure that the environment supports the sys/time.h library, as it is crucial for time measurements.
* The profiling approach is basic and might not be suitable for advanced profiling needs.

# Cleaning Up
To clean the compiled binaries and object files, run:

```
make clean
```
