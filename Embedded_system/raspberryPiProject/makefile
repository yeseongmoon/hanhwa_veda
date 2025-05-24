WCC = gcc
CC = aarch64-linux-gnu-gcc
CROSS_CFLAGS = -I /usr/aarch64-linux-gnu/include/
CROSS_LDFLAGS = -L /usr/aarch64-linux-gnu/lib/ -lwiringPi -lwiringPiDev -lcrypt -lpthread

OBJS = server.o client.o control_i2c.o control_spk.o control_led.o control_seg.o
SRCS = $(OBJS:.o=.c)

TARGET = server client

all : server client i2c led spk seg

i2c: control_i2c.o
	$(CC) -shared -o lib$@.so $<
	~/scp.sh lib$@.so

control_i2c.o: control_i2c.c
	$(CC) -c -fPIC $<

led: control_led.o
	$(CC) -shared -o lib$@.so $<
	~/scp.sh lib$@.so

control_led.o: control_led.c
	$(CC) -c -fPIC $<

seg: control_seg.o
	$(CC) -shared -o lib$@.so $<
	~/scp.sh lib$@.so

control_seg.o: control_seg.c
	$(CC) -c -fPIC $<

spk: control_spk.o
	$(CC) -shared -o lib$@.so $<
	~/scp.sh lib$@.so

control_spk.o: control_spk.c
	$(CC) -c -fPIC $<

server: server.o
	$(CC) -o $@ $< rpi_server.c $(CROSS_LDFLAGS)
	~/scp.sh $@

server.o: server.c
	$(CC) -c $< $(CROSS_CFLAGS)

client: client.o
	$(WCC) -o $@ $< 

client.o: client.c
	$(WCC) -c $< 

clean:
	rm $(TARGET) $(OBJS) lib*.so
