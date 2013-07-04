CC=gcc
CFLAGS=-g -Wall
LFLAGS=
LIBS=-lpthread -lm
SRCS_SWITCH = switch.c recv.c send.c learn.c uni_br_multi.c src_dst_iface.c filter.c forward.c flood.c #$(wildcard *.c)
PROGS_SWITCH = switch #$(patsubst %.c,%,$(SRCS_SWITCH))
OBJS_SWITCH = $(patsubst %.c,%.o,$(SRCS_SWITCH))

SRCS_SEND = gen_send.c #$(wildcard *.c)
PROGS_SEND = gen_send #$(patsubst %.c,%,$(SRCS_SEND))
OBJS_SEND = $(patsubst %.c,%.o,$(SRCS_SEND))

SRCS_RECV = gen_recv.c #$(wildcard *.c)
PROGS_RECV = gen_recv #$(patsubst %.c,%,$(SRCS_RECV))
OBJS_RECV = $(patsubst %.c,%.o,$(SRCS_RECV))

all: objs_switch progs_switch objs_send progs_send objs_recv progs_recv 

objs_switch: $(OBJS_SWITCH)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs_switch: $(OBJS_SWITCH)
	$(CC) -o $(PROGS_SWITCH) $(LIBS) $(OBJS_SWITCH)

objs_send: $(OBJS_SEND)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs_send: $(OBJS_SEND)
	$(CC) -o $(PROGS_SEND) $(LIBS) $(OBJS_SEND)


objs_recv: $(OBJS_RECV)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs_recv: $(OBJS_RECV)
	$(CC) -o $(PROGS_RECV) $(LIBS) $(OBJS_RECV)

	
clean:
	rm -f $(PROGS_SWITCH) $(OBJS_SWITCH) $(PROGS_RECV) $(OBJS_RECV) $(PROGS_SEND) $(OBJS_SEND)
