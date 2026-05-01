hello:
	echo "Hello, World"

receiver:
	cc src/receiver.c -o bin/receiver

sender:
	cc src/sender.c -o bin/sender

