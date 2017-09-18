CC = g++
CFLAGS  = -g -Wall
STD = -std=c++11
TESTS = widget_test.o
INCL_DIRS = -I$(CURDIR)/../../

default: $(TESTS)

widget_test.o: widget_test.cpp
	$(CC) $(CFLAGS) -o $@ -c $^ $(STD) $(INCL_DIRS)
