CFLAGS = -g


sn: main.o
		gcc -o sn16 main.o  -lm

main.o: main.c
		gcc -c $(CFLAGS) $(INC) main.c

clean:
		rm -f sn *.o
