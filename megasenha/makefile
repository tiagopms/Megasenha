GTK_INCLUDE = $(shell pkg-config gtk+-2.0 --libs)
GTK_LIB = $(shell pkg-config gtk+-2.0 --cflags)

CFLAGS = $(GTK_INCLUDE)
LDFLAGS = $(GTK_LIB) -lgtk -lgdk -lglib

all: program

program: main.o modulo_gui.o modulo_controle.o modulo_armazenamento.o
	gcc -g main.o modulo_gui.o modulo_controle.o modulo_armazenamento.o $(CFLAGS) -o megasenha

main.o: main.c
	gcc -g -c main.c

modulo_gui.o: modulo_gui.c interface_gui.h
	gcc $(LDFLAGS) -g -c modulo_gui.c -lgtk

modulo_controle.o: modulo_controle.c interface_controle.h interface_armazenamento.h
	gcc -g -c modulo_controle.c

modulo_armazenamento.o: modulo_armazenamento.c interface_armazenamento.h
	gcc -g -c modulo_armazenamento.c
	
clean:
	rm *.o megasenha

splint:
	splint *.h modulo_gui.c modulo_armazenamento.c modulo_controle.c main.c -weak +infloops +compdef +sysdirerrors -warnposix -unrecog -bufferoverflowhigh

testes: teste_armazenamento.c
	gcc teste_armazenamento.c -lcunit -o testes
	./testes
