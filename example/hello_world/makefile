CC = g++
CFLAGS  = -g -Wall
STD = -std=c++11
OBJS = main.o hello_world
INCL_DIRS = -I$(CURDIR)/../../src/event -I$(CURDIR)/../../src/widget -I$(CURDIR)/../../src/app
LINK_DIRS = -lglfw -lGLEW -lGL
RM = rm -f

default: $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ -c $^ $(STD) $(INCL_DIRS)

hello_world: main.o
	$(CC) $(CFLAGS) -o $@ main.o $(STD) $(INCL_DIRS) $(LINK_DIRS)

clean:
	$(RM) $(OBJS)
