all: send receive

send:
	cc send.c -o send
receive:
	cc receive.c -o receive
clean:
	rm send receive
