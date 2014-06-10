CC=gcc
CFLAGS=-Iinclude $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS=-lutil $(shell pkg-config --libs gtk+-2.0)

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
