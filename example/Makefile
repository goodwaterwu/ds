PREFIX ?= $(PWD)
CROSS_COMPILE ?=

CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)gcc -E
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld
NM = $(CROSS_COMPILE)nm
STRIP = $(CROSS_COMPILE)strip

MODULES =

DESTDIR=$(PREFIX)/out
INCLUDES = -I$(PWD) -I$(PWD)/../include

CFLAGS = -O2 -Wall -fPIC $(MODULES) $(INCLUDES)
LDFLAGS =
LIBS =

DLLIST_SRC = \
	test_dllist.c

DLLIST_OBJS = \
	test_dllist.o

EXEC_FILES = \
	test_dllist

.PHONY: all

all: test_dllist

.PHONY: test_dllist

test_dllist: $(DLLIST_OBJS)
	$(CC) $(DLLIST_OBJS) $(CFLAGS) -o $@
	$(STRIP) $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY: install

install: all
	mkdir -p $(DESTDIR)/bin
	mkdir -p $(DESTDIR)/lib
	mkdir -p $(DESTDIR)/include
	cp -vf $(EXEC_FILES) $(DESTDIR)/bin
	cp -vf *.h $(DESTDIR)/include

.PHONY: clean

clean:
	@rm -rf $(DLLIST_OBJS) $(EXEC_FILES) $(DESTDIR)