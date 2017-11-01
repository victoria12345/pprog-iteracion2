/**
* @brief Define el bucle del juego.
*
* @file game_loop.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 1.0
* @date 13-01-2015
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"

/**
* Es el bucle del juego. Es la función principal.
*/
int main(int argc, char *argv[]){
  Game game;
  Command* command = NULL;
  Graphic_engine *gengine;

  command = command_create();

  if (!command)fprintf(stderr, "Use: fallo  con command");

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

    /**  fprintf(stderr, "action: %d", command_get_action(command));*/
    game_update(&game, command);
  }

  game_destroy(&game);
  command_destroy(command);
  graphic_engine_destroy(gengine);

  return 0;
}
