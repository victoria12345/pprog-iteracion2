#-----------------------
# Autores: Victoria Pelayo e Ignacio Rabuñal
# Compilación y enlazado de todos los ficheros de la oca base.
#-----------------------

all: ocabas

ocabas: game.o command.o space.o game_loop.o graphic_engine.o screen.o game_reader.o player.o object.o set.o
	gcc -ansi -pedantic -Wall -g -o ocabas command.o space.o game_loop.o game.o graphic_engine.o screen.o game_reader.o player.o object.o set.o

game.o: game.c game.h space.h
	gcc -ansi -pedantic -Wall -g -c game.c

command.o: command.c command.h
	gcc -ansi -pedantic -Wall -g -c command.c

game_loop.o: game_loop.c graphic_engine.h
	gcc -ansi -pedantic -Wall -g -c game_loop.c

graphic_engine.o: graphic_engine.c graphic_engine.h screen.h
	gcc -ansi -pedantic -Wall -g -c graphic_engine.c

screen.o: screen.c screen.h
	gcc -ansi -pedantic -Wall -g -c screen.c

space.o: space.c space.h types.h player.h object.h set.h
	gcc -ansi -pedantic -Wall -g -c space.c

game_reader.o: game_reader.c game_reader.h game.h
	gcc -ansi -pedantic -Wall -g -c game_reader.c

player.o: player.c player.h types.h
	gcc -ansi -pedantic -Wall -g -c player.c

object.o: object.c object.h types.h
	gcc -ansi -pedantic -Wall -g -c object.c

set.o : set.c set.h types.h
	gcc -ansi -Wall -g -c set.c

die_test.o: die_test.c die.h
	gcc -c die_test.c

die_test: die_test.o die.o
	gcc -o die_test die_test.o die.o

set_test.o: set_test.c set.h
	gcc -c set_test.c

set_test: set.o set_test.o
	gcc -o set_test set.o set_test.o

#comprimir
dist:
	tar -cvzf s1-cod_OcaBasicaIni-1.tgz *c *h makefile spaces.dat autores.txt


#limpieza
clean:
	rm -f ocabas *.o
