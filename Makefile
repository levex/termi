CC=gcc

all: termi

OBJS += main.o

%.o: %.c
	@echo "  CC            $@"
	@$(CC) -c $< -o $@

termi: $(OBJS)
	gcc $(OBJS) -o termi

clean:
	rm -rf `find . | grep *\.o`
	rm termi
