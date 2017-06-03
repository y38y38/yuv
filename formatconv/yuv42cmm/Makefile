CFLAGS = -g
INC = -I../../common/


yuv42cmm: main.o yuv4.o yuv42cmm.o
		gcc -o yuv42cmm main.o yuv4.o yuv42cmm.o

main.o: main.c
		gcc -c $(CFLAGS) $(INC) main.c

yuv4.o: ../../common/yuv4.c
		gcc -c $(CFLAGS) $(INC)  ../../common/yuv4.c

yuv42cmm.o: yuv42cmm.c
		gcc -c $(CFLAGS) $(INC)  yuv42cmm.c

clean:
		rm -f yuv42cmm *.o
