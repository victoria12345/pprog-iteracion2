/**
 * @brief Implementa el motor grafico textual
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 18-01-2017
         24-09-2017: Corregir el estilo de programacion y documentacion
 * @copyright GNU Public License
 */


#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"


/**
 * @brief Definición de la estructura del motor grafico
 *
 * Tiene cuatro punteros tipo area que indican: el mapa, la descripcion, el banner, la ayuda y el feedback
 */

struct _Graphic_engine{
    Area *map, *descript, *banner, *help, *feedback;
};


/**
 * @brief Crea el motor grafico
 *
 * graphic_engine_create crea el motor grafico por lo que debe reservar memoria para dicho motor.
 * Ademas debe de llamar a screen_init para incializar la pantalla.
 * Inicializa todos sus campos creando un area de la pantalla mediante screen_area_init
 *
 * @return devuelve un puntero al motor grafico creado, NULL en caso de error
 *
 */

Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

  ge->map      = screen_area_init( 1, 1, 48, 13);
  ge->descript = screen_area_init(50, 1, 29, 13);
  ge->banner   = screen_area_init(28,15, 23,  1);
  ge->help     = screen_area_init( 1,16, 78,  2);
  ge->feedback = screen_area_init( 1,19, 78,  3);

  return ge;
}


/**
 * @brief Destruye el motor grafico
 *
 * graphic_engine_destroy destruye el motor liberando la memoria de cada uno de sus campos con la funcion screen_area_destroy
 * Una vez liberado esto, destruye la pantalla y liberar la memoria del motor grafico
 *
 * @param ge puntero no nulo al motor grafico a considerar
 *
 */


void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}


/**
 * @brief Crea la apariencia del juego que se mostrará por pantalla
 *
 * @param ge puntero no nulo al motor grafico a considerar
 * @param game puntero no nulo al juego a considerar
 *
 */


void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space* space_act = NULL;
  char obj1='\0',obj2='\0',obj3='\0',obj4='\0';
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];


  /*!< Pinta el mapa del area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

    if (game_get_object_location(game, 1) == id_back)   /*!< Casilla anterior */
      obj1='*';
    else
      obj1=' ';

    if (game_get_object_location(game, 2) == id_back)   /*!< Casilla anterior */
      obj2='$';
    else
      obj2=' ';

    if (game_get_object_location(game, 3) == id_back)   /*!< Casilla anterior */
      obj3='+';
    else
      obj3=' ';

    if (game_get_object_location(game, 4) == id_back)   /*!< Casilla anterior */
      obj4='@';
    else
      obj4=' ';

    if (id_back != NO_ID) {
      sprintf(str, "  |         %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%c %c %c %c |",obj1,obj2,obj3,obj4);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game, 1) == id_act)   /*!< Casilla anterior */
      obj1='*';
    else
      obj1=' ';

    if (game_get_object_location(game, 2) == id_act)   /*!< Casilla anterior */
      obj2='$';
    else
      obj2=' ';

    if (game_get_object_location(game, 3) == id_act)   /*!< Casilla anterior */
      obj3='+';
    else
      obj3=' ';

    if (game_get_object_location(game, 4) == id_act)   /*!< Casilla anterior */
      obj4='@';
    else
      obj4=' ';

    if (id_act != NO_ID) {
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  | 8D      %2d|",(int) id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |%c %c %c %c |",obj1,obj2,obj3,obj4);
        screen_area_puts(ge->map, str);
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game, 1) == id_next)   /*!< Casilla anterior */
      obj1='*';
    else
      obj1=' ';

    if (game_get_object_location(game, 2) == id_next)   /*!< Casilla anterior */
      obj2='$';
    else
      obj2=' ';

    if (game_get_object_location(game, 3) == id_next)   /*!< Casilla anterior */
      obj3='+';
    else
      obj3=' ';

    if (game_get_object_location(game, 4) == id_next)   /*!< Casilla anterior */
      obj4='@';
    else
      obj4=' ';

    if (id_next != NO_ID) {
        sprintf(str, "        v");
        screen_area_puts(ge->map, str);
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |         %2d|",(int) id_next);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |  %c %c %c %c  |",obj1, obj2, obj3, obj4);
        screen_area_puts(ge->map, str);
    }
  }

    /*!< Pintar en el área de descripción */
  screen_area_clear(ge->descript);
  if ((obj_loc = game_get_object_location(game, 1)) != NO_ID){
    sprintf(str, "  Object location:%d", (int) obj_loc);
    screen_area_puts(ge->descript, str);
  }

    /*!< Pintar en el área del banner */
  screen_area_puts(ge->banner, " The game of the Goose ");

    /*!< Pintar en el área de ayuda */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     next or n, back or b, pick or p, drop or d, left or l, right or ri, roll or ro and quit or q");
  screen_area_puts(ge->help, str);

    /*!< Pintar en el área de feedback*/
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s", cmd_to_str[last_cmd-NO_CMD]);
  screen_area_puts(ge->feedback, str);

  screen_paint();
  printf("prompt:> ");
}
