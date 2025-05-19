CC = gcc
CROSS_CFLAGS = -I /usr/include/
CROSS_LDFLAGS = -L /usr/lib/ -lwiringPi -lwiringPiDev -lpthread -lcrypt
TARGET = server client

all : server client

server: server.o
	$(CC) -o $@ $< $(CROSS_LDFLAGS)
	~/scp.sh $@

server.o: server.c
	$(CC) -c $< $(CROSS_CFLAGS)

client: client.o
	$(CC) -o $@ $< $(CROSS_LDFLAGS)

client.o: client.c
	$(CC) -c $< $(CROSS_CFLAGS)

clean:
	rm $(TARGET) *.o
