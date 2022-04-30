CC = cc
CFLAGS = -Wall -O2 -s
LDFLAGS =
PREFIX ?= /usr/local

OBJS = vi.o ex.o lbuf.o mot.o sbuf.o ren.o dir.o syn.o reg.o led.o \
	uc.o term.o rset.o rstr.o regex.o cmd.o conf.o

all: vi

conf.o: conf.h

%.o: %.c
	$(CC) -c $(CFLAGS) $<
vi: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
install: vi
	mkdir -p $(PREFIX)/bin
	cp -f vi $(PREFIX)/bin/vi
	chmod 755 $(PREFIX)/bin/vi
clean:
	rm -f *.o vi

.PHONY: clean all install
