#Napisac Makefile do przyklad�w z wykorzystaniem flag i dopasowania wzorc�w

CC=gcc
CFLAGS=-g -Wall
LFLAGS=
LIBS=
SRCS = $(wildcard *.c)
PROGS = zadanie3 #$(patsubst %.c,%,$(SRCS))
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: objs progs

objs: $(OBJS)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs: $(OBJS)
	$(CC) -o $(PROGS) $(OBJS)
	
clean:
	rm -f $(PROGS) $(OBJS)
