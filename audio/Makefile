CFLAGS = -g -Wall 

g711: main.o sample_send_g711.o enc_g711.o
		gcc $(CFLAGS) -o g711 main.o sample_send_g711.o  enc_g711.o 

main.o: main.c
		gcc $(CFLAGS) -c main.c

sample_send_g711.o: sample_send_g711.c
		gcc $(CFLAGS) -c  sample_send_g711.c

enc_g711.o: lib_enc_g711/enc_g711.c
		gcc $(CFLAGS) -c lib_enc_g711/enc_g711.c

clean:
		rm -f g711 *.o lib_enc_g711/*.o
