CC = gcc
CFLAGS = -I /usr/include -c
LDFLAGS = -L usr/lib -lcrypt -lwiringPi -lwiringPiDev -lpthread

OBJS = rpi.o
SRCS = $(OBJS:.o=.c)

rpi : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	~/scp.sh $@

rpi.o: rpi.c
	$(CC) $(CFLAGS) $(SRCS)

clean:
	rm rpi $(OBJS)
