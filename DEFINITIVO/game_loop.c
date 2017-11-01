/**
* @brief Define el bucle del juego.
*
* @file game_loop.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 2.0
* @date 01-11-2017
* Se han realizado cambios en las llamadas a funciones debido al cambio de los comandos
* Se ha añadido que se vayan guardando en un fichero los resultados del juego
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "command.h"

/**
* Es el bucle del juego. Es la función principal.
*/
int main(int argc, char *argv[]){
  Game game;
  Command* command = NULL;
  Graphic_engine *gengine;
  FILE *f;

  f = fopen(argv[3], "w");

  command = command_create();

  if(f == NULL){
    fprintf(stderr, "Error with file");
    return 1;
  }

  if (command == NULL){
    fprintf(stderr, "Error command");
    return 1;
  }

  if (argc < 2){
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]); return 1;
  }

  if (game_create_from_file(&game, argv[1],argv[2]) == ERROR){
    fprintf(stderr, "Error while initializing game.\n"); return 1;
  }

  if ((gengine = graphic_engine_create()) == NULL){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(&game);
    return 1;
  }

  while ( (command_get_action(command) != QUIT) && !game_is_over(&game) ){
    graphic_engine_paint_game(gengine, &game);
    command_destroy(command);
    command = get_user_input();

    fprintf(f, "%s %s \n", command_get_name( game_get_last_command(&game) ),
        command_get_status( game_get_last_command(&game) ));
    game_update(&game, command);
  }

  game_destroy(&game);
  command_destroy(command);
  graphic_engine_destroy(gengine);
  fclose(f);

  return 0;
}
