#Napisac Makefile do przykladów z wykorzystaniem flag i dopasowania wzorców

CC=gcc
CFLAGS=-g -Wall
LFLAGS=
LIBS=
SRCS = $(wildcard *.c)
PROGS = hashtable #$(patsubst %.c,%,$(SRCS))
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: objs progs

objs: $(OBJS)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs: $(OBJS)
	$(CC) -o $(PROGS) $(OBJS)
	
clean:
	rm -f $(PROGS) $(OBJS)
