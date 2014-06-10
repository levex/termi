CC=gcc
CFLAGS=-Iinclude
LDFLAGS=-lutil

all: termi

OBJS += main.o terminal.o

include test/Makefile

%.o: %.c
	@echo "  CC            $@"
	@$(CC) $(CFLAGS) -c $< -o $@

termi: $(OBJS)
	@echo "  LD            $@"
	@gcc $(LDFLAGS) $(OBJS) -o termi
clean:
	-rm -rf $(OBJS)
	-rm termi
