/**
* @brief Implementa las funciones para el manejo del motor gráfico textual.
*
* @file screen.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 1.1
* @date 29/09/2017
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
  char object1[WORD_SIZE], object2[WORD_SIZE], object3[WORD_SIZE],object4[WORD_SIZE];
  char *c1, *c2, *c3, *c4;

  Space* space_act = NULL;
  Space* back = NULL;
  Space* next = NULL;
  char str[255];
  line* lines1;
  line* lines2;
  line* lines3;

  strcpy(object1, " ");
  strcpy(object2," ");
  strcpy(object3, " ");
  strcpy(object4," ");

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    lines1 = space_get_gdesc(space_act);

    if (id_back != NO_ID){
      if(game_get_object_location(game, game->objects[0]) == id_back){
        c1 = object_get_name(game->objects[0]);
        if(c1 != NULL) strcpy(object1, c1);
      }

      if(game_get_object_location(game, game->objects[1]) == id_back){
        c2 = object_get_name(game->objects[1]);
        if(c2 != NULL) strcpy(object2, c2);
      }
      if(game_get_object_location(game, game->objects[2]) == id_back){
        c3 = object_get_name(game->objects[2]);
        if(c3 != NULL) strcpy(object3, c3);
      }

      if(game_get_object_location(game, game->objects[3]) == id_back){
        c4 = object_get_name(game->objects[3]);
        if(c4 != NULL) strcpy(object4, c4);
      }

      back = game_get_space(game, id_back);
      lines2 = space_get_gdesc(back);
      sprintf(str, "  |         %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |   %s %s %s %s |",object1, object2, object3, object4);
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

    strcpy(object1, " ");
    strcpy(object2, " ");
    strcpy(object3, " ");
    strcpy(object4," ");

    if (id_act != NO_ID) {

      if(game_get_object_location(game, game->objects[0]) == id_act){
        c1 = object_get_name(game->objects[0]);
        if(c1 != NULL) strcpy(object1, c1);
      }

      if(game_get_object_location(game, game->objects[1]) == id_act){
        c2 = object_get_name(game->objects[1]);
        if(c2 != NULL) strcpy(object2, c2);
      }
      if(game_get_object_location(game, game->objects[2]) == id_act){
        c3 = object_get_name(game->objects[2]);
        if(c3 != NULL) strcpy(object3, c3);
      }

      if(game_get_object_location(game, game->objects[3]) == id_act){
        c4 = object_get_name(game->objects[3]);
        if(c4 != NULL) strcpy(object4, c4);
      }

      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D      %2d|",(int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |   %s %s %s %s |",object1, object2, object3, object4);
      screen_area_puts(ge->map, str);
      for(i = 0; i < NUM_LINES; i++){
        sprintf(str, "  |  %s  |",lines1[i]);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    strcpy(object1, " ");
    strcpy(object2, " ");
    strcpy(object3, " ");
    strcpy(object4," ");

    if (id_next != NO_ID) {

      if(game_get_object_location(game, game->objects[0]) == id_next){
        c1 = object_get_name(game->objects[0]);
        if(c1 != NULL) strcpy(object1, c1);
      }

      if(game_get_object_location(game, game->objects[1]) == id_next){
        c2 = object_get_name(game->objects[1]);
        if(c2 != NULL) strcpy(object2, c2);
      }
      if(game_get_object_location(game, game->objects[2]) == id_next){
        c3 = object_get_name(game->objects[2]);
        if(c3 != NULL) strcpy(object3, c3);
      }

      if(game_get_object_location(game, game->objects[3]) == id_next){
        c4 = object_get_name(game->objects[3]);
        if(c4 != NULL) strcpy(object4, c4);
      }

      next = game_get_space(game, id_next);
      lines3 = space_get_gdesc(next);
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|",(int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |   %s %s %s %s |",object1, object2, object3, object4);
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

  sprintf(str, "  Objects location: %s: %d,       %s: %d,  %s: %d,  %s: %d ",
                object_get_name(game->objects[0]), (int)game_get_object_location(game, game->objects[0]),
                object_get_name(game->objects[1]), (int)game_get_object_location(game, game->objects[1]),
                object_get_name(game->objects[2]), (int)game_get_object_location(game, game->objects[2]),
                object_get_name(game->objects[3]), (int)game_get_object_location(game, game->objects[3]));
  screen_area_puts(ge->descript, str);

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  id = player_get_object(game->player);
  sprintf(str, "  Player object: %ld", id);
  screen_area_puts(ge->descript, str);

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
  if(strcmp(command_get_name(game->last_cmd), "UNKNOWN") != 0){
    sprintf(str, " %s%s", command_get_name(game->last_cmd), command_get_status(game->last_cmd) );
    screen_area_puts(ge->feedback, str);
  }
  else{
    sprintf(str, " %s", command_get_name(game->last_cmd));
    screen_area_puts(ge->feedback, str);
  }

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");


}
