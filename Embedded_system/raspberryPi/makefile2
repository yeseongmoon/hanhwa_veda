CC = gcc
CFLAGS = -I /usr/include -c
LDFLAGS = -L usr/lib -lcrypt -lwiringPi -lwiringPiDev -lpthread

OBJS = rpi.o
SRCS = $(OBJS:.o=.c)

all: rpi led

led: control_led.o
	$(CC) -shared -o lib$@.so $<
	~/scp.sh lib$@.so

control_led.o: control_led.c
	$(CC) -c -fPIC $<

rpi : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	~/scp.sh $@

rpi.o: rpi.c
	$(CC) $(CFLAGS) $(SRCS)

clean:
	rm rpi lib*.so $(OBJS)
