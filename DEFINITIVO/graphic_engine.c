/**
* @brief Implementa las funciones para el manejo del motor gráfico textual.
*
* Se ha modificado la funcion paint_game.
* Se ha añadido que pinte el campo gdesc de las casillas.
* Se pueden ver ahora las fichas en las casillas.
* Se ha añadido que tambien se puedan ver el nmbre de las fichas y su posicion,
* el ultimo valor del dado, la casilla que tiene el jugador.
* También se puede ver ahora la acción que se ha realizado y su resultado,
* es decir, si se ha realizado correctamente o no.
* @file screen.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 2.0
* @date 01-11-2017
* @copyright GNU Public License
*/



#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"


struct _Graphic_engine{
  Area *map, *descript, *banner, *help, *feedback;
};


Graphic_engine *graphic_engine_create(){

  static Graphic_engine *ge = NULL;
  if (ge) return ge;

  screen_init();

  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

  ge->map      = screen_area_init( 1, 1, 48, 13);
  ge->descript = screen_area_init(50, 1, 29, 13);
  ge->banner   = screen_area_init(28,15, 23,  1);
  ge->help     = screen_area_init( 1,16, 78,  2);
  ge->feedback = screen_area_init( 1,19, 78,  3);

  return ge;
}


void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge) return;
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}


void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  int i;
  Id id;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  char objects[5];

  Space* space_act = NULL;
  Space* back = NULL;
  Space* next = NULL;
  char str[255];
  line* lines1;
  line* lines2;
  line* lines3;

  objects[0] = '\0';

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    lines1 = space_get_gdesc(space_act);

    if (id_back != NO_ID){

      for(i = 0; game->objects[i] != NULL && i < 5 ; i++){
        if(game_get_object_location(game, game->objects[i]) == id_back){
          /**fprintf(stderr, "%s\n", object_get_name(game->objects[i]));*/
          strcat(objects, object_get_name(game->objects[i]));
        }
      }

      if(strlen(objects) < 11){
        for(i = 0; strlen(objects) < 4; i++) strcat(objects, " ");
      }

      back = game_get_space(game, id_back);
      lines2 = space_get_gdesc(back);
      sprintf(str, "  |         %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %c %c %c %c  |",objects[0], objects[1], objects[2], objects[3]);
      screen_area_puts(ge->map, str);
      for(i = 0; i < NUM_LINES; i++){
        sprintf(str, "  |  %s  |",lines2[i]);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    objects[0] = '\0';

    if (id_act != NO_ID) {

      for(i = 0; game->objects[i] != NULL && i < 5; i++){
        if(game_get_object_location(game, game->objects[i]) == id_act){
          /**  fprintf(stderr, "%s\n", object_get_name(game->objects[i]));*/
          strcat(objects, object_get_name(game->objects[i]));
        }
      }

      if(strlen(objects) < 4){
        for(i = 0; strlen(objects) < 4; i++) strcat(objects, " ");
      }

      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D      %2d|",(int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %c %c %c %c  |",objects[0], objects[1], objects[2], objects[3]);
      screen_area_puts(ge->map, str);
      for(i = 0; i < NUM_LINES; i++){
        sprintf(str, "  |  %s  |",lines1[i]);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    objects[0] = '\0';

    if (id_next != NO_ID) {

      for(i = 0; game->objects[i] != NULL && i < 5; i++){
        if(game_get_object_location(game, game->objects[i]) == id_next){
          /**  fprintf(stderr, "%s\n", object_get_name(game->objects[i]));*/
          strcat(objects, object_get_name(game->objects[i]));
        }
      }

      if(strlen(objects) < 4){
        for(i = 0; strlen(objects) < 4; i++) strcat(objects, " ");
      }
      next = game_get_space(game, id_next);
      lines3 = space_get_gdesc(next);
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|",(int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |  %c %c %c %c  |",objects[0], objects[1], objects[2], objects[3]);
      screen_area_puts(ge->map, str);
      for(i = 0; i < NUM_LINES; i++){
        sprintf(str, "  |  %s  |",lines3[i]);
        screen_area_puts(ge->map, str);
      }


    }
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);

  /** Imprimirá por pantalla el nombre de los objetos,lo hemos tomado como su simbolo,
  seguido de la casilla en la que se encuentran*/

  sprintf(str, "  Objects location: ");
  screen_area_puts(ge->descript, str);

  for(i = 0; game->objects[i] != NULL; i++){
    sprintf(str, "   %s : %d",
    object_get_name(game->objects[i]), (int)game_get_object_location(game, game->objects[i]));
    screen_area_puts(ge->descript, str);
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  id = player_get_object(game->player);

  for(i = 0;i < MAX_SPACES + 1 && game->objects[i] != NULL; i++){
    if (object_get_id(game->objects[i]) == id){
      sprintf(str, "  Player object: %s", object_get_name(game->objects[i]));
      screen_area_puts(ge->descript, str);
      i = WORD_SIZE + 1;
    }
  }

  if(i == WORD_SIZE + 1 || game->objects[i] == NULL){
    sprintf(str, "  Player object: null");
    screen_area_puts(ge->descript, str);
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, "  Last die value:%d", die_latest_roll(game->die));
  screen_area_puts(ge->descript, str);

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, "  Player location: %ld", id_act);
  screen_area_puts(ge->descript, str);




  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, or quit or q, pick or p, drop or d, l or left, r or right, ROLL or roll");
  screen_area_puts(ge->help, str);


  /* Paint the in the feedback area */

  sprintf(str, " %s%s", command_get_name(game->last_cmd), command_get_status(game->last_cmd) );
  screen_area_puts(ge->feedback, str);


  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");


}
