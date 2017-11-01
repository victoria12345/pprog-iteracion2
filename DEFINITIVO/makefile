#-----------------------
# Autores: Victoria Pelayo e Ignacio Rabuñal
# Compilación y enlazado de todos los ficheros de la oca base.
#-----------------------

EXE = ocabas
CC = gcc -ansi -pedantic
CFLAGS = -Wall -g
#CFLAGS = -Wall -03

all: $(EXE)

ocabas: game.o command.o space.o game_loop.o graphic_engine.o screen.o game_reader.o player.o object.o set.o die.o
	$(CC) $(CFLAGS) -o ocabas command.o space.o game_loop.o game.o graphic_engine.o screen.o game_reader.o player.o object.o set.o die.o

game.o: game.c game.h space.h
	$(CC) $(CFLAGS) -c game.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

game_loop.o: game_loop.c graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c

graphic_engine.o: graphic_engine.c graphic_engine.h screen.h die.h
	$(CC) $(CFLAGS) -c graphic_engine.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o: space.c space.h types.h player.h object.h set.h
	$(CC) $(CFLAGS) -c space.c

game_reader.o: game_reader.c game_reader.h game.h
	$(CC) $(CFLAGS) -c game_reader.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

set.o : set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

die.o: die.c types.h die.h
	$(CC) $(CFLAGS) -c die.c

die_test.o: die_test.c die.h
	$(CC) $(CFLAGS) -c die_test.c

die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o die_test die_test.o die.o

set_test.o: set_test.c set.h
	$(CC) $(CFLAGS) -c set_test.c

set_test: set.o set_test.o
	$(CC) $(CFLAGS) -o set_test set.o set_test.o

#comprimir
dist:
	tar -cvzf s1-cod_OcaBasicaIni-2.tgz  *c *h makefile spaces.dat autores.txt objects.dat


#limpieza
clean:
	rm -f $(EXE) set_test die_test *.o
