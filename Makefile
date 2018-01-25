SHELL=/bin/bash

CC=/usr/bin/g++
CFLAGS=-std=c++17 -Wall -Wextra
OFLAGS=$(CFLAGS) -lglfw -lGLEW -lGL -lpthread -lXm -lXt

DIR_ORIGIN=.
DIR_BUILD=$(DIR_ORIGIN)/build
DIR_SCRIPTS=$(DIR_ORIGIN)/source

COUT=spark

SOURCES=$(shell find $(DIR_SCRIPTS)/ -type f -regex ".*\.cpp")
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

all: $(patsubst %.cpp,%.o,$(SOURCES))
	@echo -en "\033[1;33m[CC]\033[0;1m" $(OBJECTS) $(OFLAGS) -o $(DIR_BUILD)/$(COUT) "\033[0m\n"
	@g++ $(OBJECTS) $(OFLAGS) -o $(DIR_BUILD)/$(COUT)

%.o: %.cpp
	@echo -en "\033[1;32m[CC]\033[0;1m" $^ $(CFLAGS) -o $@ "\033[0m\n"
	@g++ -c $^ $(CFLAGS) -o $@

clean:
	@rm -v $(OBJECTS)

run:
	make -C $(DIR_BUILD)

asm:
	make asm -C $(DIR_BUILD)

cleanasm:
	make cleanasm -C $(DIR_BUILD)
