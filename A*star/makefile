CC=clang 

CFLAGS= -pedantic -ansi -Wall -g

TARGET=main

LIBS = fibo.c lib_dyn.c lib_graf.c 

all:
	@echo Simple compiler named MAIN has been compiled 
	$(CC) $(CFLAGS) -o main $(TARGET).c $(LIBS)

clean:
	$(RM) $(TARGET) 
print-%:; @echo $*=$($*)
