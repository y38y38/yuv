CFLAGS = -g -Wall  -Wmain
INC = -I./
INC += -I./opus/include/

g711: main.o sample_send_g711.o enc_g711.o
		gcc $(CFLAGS) $(INC) -o g711 main.o sample_send_g711.o  enc_g711.o 

main.o: main.c
		gcc $(CFLAGS)  $(INC) -c main.c

sample_send_g711.o: sample_send_g711.c
		gcc $(CFLAGS)  $(INC) -c  sample_send_g711.c

enc_g711.o: lib_enc_g711/enc_g711.c
		gcc $(CFLAGS)  $(INC) -c lib_enc_g711/enc_g711.c

clean:
		rm -f g711 *.o lib_enc_g711/*.o
