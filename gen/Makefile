CC=gcc
CFLAGS=-g -Wall
LFLAGS=
LIBS=-lpthread -lm
SRCS_SWITCH = generate.c #$(wildcard *.c)
PROGS_SWITCH = generate #$(patsubst %.c,%,$(SRCS_SWITCH))
OBJS_SWITCH = $(patsubst %.c,%.o,$(SRCS_SWITCH))

SRCS_RECV = gen_recv.c #$(wildcard *.c)
PROGS_RECV = gen_recv #$(patsubst %.c,%,$(SRCS_RECV))
OBJS_RECV = $(patsubst %.c,%.o,$(SRCS_RECV))

all: objs_switch progs_switch 

objs_switch: $(OBJS_SWITCH)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs_switch: $(OBJS_SWITCH)
	$(CC) -o $(PROGS_SWITCH) $(LIBS) $(OBJS_SWITCH)

objs_recv: $(OBJS_RECV)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs_recv: $(OBJS_RECV)
	$(CC) -o $(PROGS_RECV) $(LIBS) $(OBJS_RECV)

	
clean:
	rm -f $(PROGS_SWITCH) $(OBJS_SWITCH) $(PROGS_RECV) $(OBJS_RECV)
