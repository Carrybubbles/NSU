CC=clang
CFLAGS= -Wall -c -g 

all: captcha
	@echo Simple compiler named captcha has been compiled!!!
	@echo 
captcha: net.o image.o main.o
	$(CC)  net.o image.o main.o -o  captcha

main.o: main.c
	$(CC) $(CFLAGS) main.c

net.o: net.c
	$(CC) $(CFLAGS)  net.c

image.o: image.c
	$(CC) $(CFLAGS) image.c

clean:
	rm -rf *.o captcha