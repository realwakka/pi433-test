CC=gcc
CFLAGS=-I.
DEPS = pi433_if.h rf69_enum.h
SEND_OBJ = send.o
RECV_OBJ = receive.o

all: receive send

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

receive: $(RECV_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

send: $(SEND_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f receive send
