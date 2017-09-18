# Makefile Variables
export CC = g++
export CFLAGS  = -g -Wall
export STD = -std=c++11
export INCL_DIRS = -I.
export LINK_DIRS = -lGL -lGLEW -lSOIL
export CP = cp -r
export RM = rm -f
export TESTS = event_test widget_test
export INSTALL_DIR = /usr/local/include/scui
export DATA_DIR = /usr/local/share/scui

.PHONY: mktest installsrc installasset installbase

test: mktest $(TESTS)
	./event_test
	./widget_test

mktest:
	@$(MAKE) -C test

event_test:
	$(CC) $(CFLAGS) -o $@ test/event/event_test.o $(STD) $(INCL_DIRS)

widget_test:
	$(CC) $(CFLAGS) -o $@ test/widget/widget_test.o $(STD) $(INCL_DIRS) $(LINK_DIRS)

clean:
	$(RM) test/*/*.o *~ *_test example/*/*.o example/hello_world/hello_world

install: installbase installsrc installasset

installsrc:
	@$(MAKE) install -C scui

installasset:
	@$(MAKE) install -C asset

installbase:
	sudo mkdir $(INSTALL_DIR) $(DATA_DIR)

uninstall:
	sudo $(RM) -r $(INSTALL_DIR) $(DATA_DIR)

examples:
	@$(MAKE) -C example
