CFLAGS = -Wall
ifeq ($(strip $(DEBUG)),)
CFLAGS = -std=c99 -Wall -Werror
endif
SRC=$(wildcard *.c)
CC=gcc
PROGS=$(patsubst %.c,%,$(SRC))
OBJS=$(patsubst %.c,%.o,$(SRC))

.PHONY: all
.PHONY: test.out
#all: $(PROGS)
all: $(OBJS) test.out

test.out: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lpcap -o ../bin/test.out
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -f *.o
	@rm -f ../bin/*.out
