CFLAGS = -g
INC = -I../common/


sn: main.o cmm.o
		gcc -o sn main.o cmm.o

main.o: main.c
		gcc -c $(CFLAGS) $(INC) main.c

cmm.o: ../common/cmm.c
		gcc -c $(CFLAGS) $(INC) ../common/cmm.c

clean:
		rm -f sn *.o
