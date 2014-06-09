CC=gcc
LDFLAGS=-lutil

all: termi

OBJS += main.o

%.o: %.c
	@echo "  CC            $@"
	@$(CC) -c $< -o $@

termi: $(OBJS)
	@echo "  LD            $@"
	@gcc $(LDFLAGS) $(OBJS) -o termi
clean:
	rm -rf `find . | grep *\.o`
	rm termi
