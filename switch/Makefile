CC=gcc
CFLAGS=-g -Wall
LFLAGS=
LIBS=-lpthread -lm
SRCS_SWITCH = switch.c recv.c send.c learn.c uni_br_multi.c src_dst_iface.c flood.c aging.c db.c crc.c #$(wildcard *.c)
PROGS_SWITCH = switch #$(patsubst %.c,%,$(SRCS_SWITCH))
OBJS_SWITCH = $(patsubst %.c,%.o,$(SRCS_SWITCH))

all: objs_switch progs_switch 

objs_switch: $(OBJS_SWITCH)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs_switch: $(OBJS_SWITCH)
	$(CC) -o $(PROGS_SWITCH) $(LIBS) $(OBJS_SWITCH)
	
clean:
	rm -f $(PROGS_SWITCH) $(OBJS_SWITCH) $(PROGS_RECV) $(OBJS_RECV) $(PROGS_SEND) $(OBJS_SEND)
