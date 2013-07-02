CC=gcc
CFLAGS=-g -Wall
LFLAGS=
LIBS=
SRCS_SWITCH = switch.c recv.c send.c learn.c uni_br_multi.c src_dst_iface.c filter.c forward.c #$(wildcard *.c)
PROGS_SWITCH = switch #$(patsubst %.c,%,$(SRCS_SWITCH))
OBJS_SWITCH = $(patsubst %.c,%.o,$(SRCS_SWITCH))

all: objs_switch progs_switch

objs_switch: $(OBJS_SWITCH)
%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

progs_switch: $(OBJS_SWITCH)
	$(CC) -o $(PROGS_SWITCH) $(OBJS_SWITCH)
	
clean:
	rm -f $(PROGS_SWITCH) $(OBJS_SWITCH)
