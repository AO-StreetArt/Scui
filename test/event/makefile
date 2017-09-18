CC = g++
CFLAGS  = -g -Wall
STD = -std=c++11
TESTS = event_test.o
INCL_DIRS = -I$(CURDIR)/../../

default: $(TESTS)

event_test.o: event_test.cpp
	$(CC) $(CFLAGS) -o $@ -c $^ $(STD) $(INCL_DIRS)
