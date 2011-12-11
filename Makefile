CFLAGS	+=	-ggdb -fPIC
all	:	main

main	:	main.o tst.o

clean	:
	rm main *.o