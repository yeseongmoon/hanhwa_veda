OBJS = main.o parsing.o isbuiltin.o cmd_linux.o child_handler.o redirect.o pipe.o
SRCS = $(OBJS:.o=.c)

myshell: $(OBJS)
	$(CC) -o $@ $(OBJS)

.c.o:
	$(CC) -c $<

clean:
	rm myshell $(OBJS)
