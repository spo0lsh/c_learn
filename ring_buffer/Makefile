#Napisac Makefile do przyklad�w z wykorzystaniem flag i dopasowania wzorc�w

CC=gcc
CFLAGS=-g -Wall
LFLAGS=
LIBS=
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: objs progs

objs: $(OBJS)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

progs: $(PROGS)
%: %.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<
	
clean:
	rm -f $(PROGS) $(OBJS)
