CC := gcc
CFLAGS := -Wall -g

vpath %.c fs:mm:proc:sched:sync

trash := $(patsubst %.c,%,$(wildcard *.c))
trash += $(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: clean
clean:
	$(RM) *~ *.o $(trash)
