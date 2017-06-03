cmm2yuv4: main.o yuv4.o cmm.o cmm2yuv4.o
		gcc -g -o cmm2yuv4 main.o yuv4.o cmm.o cmm2yuv4.o

main.o: main.c
		gcc -g -c main.c

yuv4.o: ../../common/yuv4.c
		gcc -g -I../../common/ -c ../../common/yuv4.c

cmm.o: ../../common/cmm.c
		gcc -g  -I../../common/ -c ../../common/cmm.c

cmm2yuv4.o: cmm2yuv4.c
		gcc -g -I../../common/ -c cmm2yuv4.c

clean:
		rm -f cmm2yuv4 *.o
