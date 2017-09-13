# Makefile Variables
CC = g++
CFLAGS  = -g -Wall
STD = -std=c++11
TESTS = event_test widget_test
INCL_DIRS = -Isrc/event -Isrc/widget
RM = rm -f

.PHONY: mktest

test: mktest $(TESTS)
	./event_test
	./widget_test

mktest:
	@$(MAKE) -C test

event_test:
	$(CC) $(CFLAGS) -o $@ test/event/event_test.o $(STD) $(INCL_DIRS)

widget_test:
	$(CC) $(CFLAGS) -o $@ test/widget/widget_test.o $(STD) $(INCL_DIRS)

clean:
	$(RM) test/*/*.o *~ *_test
