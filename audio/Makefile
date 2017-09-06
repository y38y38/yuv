OPUS_LIB_PATH = /usr/local/lib
OPUS_INC_PATH = /usr/local/include/opus

CFLAGS = -g -Wall
INC = -I./
INC += -I$(OPUS_INC_PATH)

LIB = -L$(OPUS_LIB_PATH)

opusenc: main.o
		gcc $(CFLAGS) $(INC) $(LIB)  -o opusenc  main.o -lopus 
main.o: main.c
		gcc $(CFLAGS)  $(INC) -c main.c

clean:
		rm -f opusenc *.o 
