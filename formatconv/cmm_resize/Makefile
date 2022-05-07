cmm2_resize: main.o cmm422.o cmm2cmm.o
		gcc -g -o cmm2_resize main.o cmm422.o cmm2cmm.o

main.o: main.c
		gcc -g -c main.c

cmm422.o: ../../common/cmm422.c
		gcc -g  -I../../common/ -c ../../common/cmm422.c

cmm2cmm.o: cmm2cmm.c
		gcc -g -I../../common/ -c cmm2cmm.c

clean:
		rm -f cmm_resize *.o
