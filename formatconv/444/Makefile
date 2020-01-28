#all:yuv1080to1088 yuv420to422 yuv8to10 yuv10to8 yuv422to420 yuv1088to1080 yuv10422_1088to1080 
all:yuv1080to2160 yuv1080to4096_2160 yuv1080to8192_4320


CFLAGS= -g -I./


#yuv1080to1088:yuv1080to1088.o
#	gcc -o yuv1080to1088 ${CFLAGS} yuv1080to1088.o


#yuv1080to1088.o:yuv1080to1088.c
#	gcc ${CFLAGS} -c yuv1080to1088.c

#yuv420to422:yuv420to422.o
#	gcc -o yuv420to422 ${CFLAGS} yuv420to422.o

#yuv420to422.o:yuv420to422.c
#	gcc ${CFLAGS} -c yuv420to422.c

#yuv8to10:yuv8to10.o
#	gcc -o yuv8to10 ${CFLAGS} yuv8to10.o


#yuv8to10.o:yuv8to10.c
#	gcc ${CFLAGS} -c yuv8to10.c


#yuv10to8:yuv10to8.o
#	gcc -o yuv10to8 ${CFLAGS} yuv10to8.o


#yuv10to8.o:yuv10to8.c
#	gcc ${CFLAGS} -c yuv10to8.c
#
#yyuv444to420:yuv444to420.o
#	gcc -o yuv444to420 ${CFLAGS} yuv444to420.o
#
#yuv444to420.o:yuv444to420.c
#	gcc ${CFLAGS} -c yuv444to420.c

yuv1080to2160:yuv1080to2160.o
	gcc -o yuv1080to2160 ${CFLAGS} yuv1080to2160.o


yuv1080to21601080.o:yuv1080to2160.c
	gcc ${CFLAGS} -c yuv1080to2160.c

yuv1080to4096_2160:yuv1080to4096_2160.o
	gcc -o yuv1080to4096_2160 ${CFLAGS} yuv1080to4096_2160.o


yuv1080to4096_2160.o:yuv1080to4096_2160.c
	gcc ${CFLAGS} -c yuv1080to4096_2160.c

yuv1080to8192_4320:yuv1080to8192_4320.o
	gcc -o yuv1080to8192_4320 ${CFLAGS} yuv1080to8192_4320.o


yuv1080to8192_4320.o:yuv1080to8192_4320.c
	gcc ${CFLAGS} -c yuv1080to8192_4320.c

#yuv10422_1088to1080:yuv10422_1088to1080.o
#	gcc -o yuv10422_1088to1080 ${CFLAGS} yuv10422_1088to1080.o

#yuv10422_1088to1080.o:yuv10422_1088to1080.c
#	gcc ${CFLAGS} -c yuv10422_1088to1080.c 


clean:
#	rm -f *.o yuv1080to1088 yuv420to422 yuv10to8 yuv422to420 yuv1088to1080
	rm -f *.o yuv10to8 yuv444to420 yuv1088to1080

