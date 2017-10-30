/**
 * @brief Implementa la interfaz del juego y todas las devoluciones de llamada asociadas para cada comando
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 3.0
 * @date 13-01-2015
         24-09-2017: Corregir el estilo de programación y documentación
         30-09-2017: Creacion de las funciones para los comandos pick,drop y jump
         9-10-2017: Modificacion del modulo game para añadir el dado y el puntero a un array de elementos
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "game_reader.h"
#include "game.h"

#define N_CMD 10

/**
 * @biref Define el tipo de funcion por las llamadas
 * Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
 * @brief Lista de llamadas para cada comando en el juego
 * List of callbacks for each command in the game
*/
void game_callback_unknown(Game* game);
void game_callback_quit(Game* game);
void game_callback_next(Game* game);
void game_callback_back(Game* game);
void game_callback_pick(Game* game);
void game_callback_drop(Game* game);
void game_callback_left(Game* game);
void game_callback_right(Game* game);
void game_callback_roll(Game* game);

static callback_fn game_callback_fn_list[N_CMD]={
    game_callback_unknown,
    game_callback_quit,
    game_callback_next,
    game_callback_back,
    game_callback_pick,
    game_callback_drop,
    game_callback_left,
    game_callback_right,
    game_callback_roll
};

/**
 * @brief Funciones privadas
*/

Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
int    game_get_object_num(Game* game);

/**
 * @brief Crea la interfaz del juego
 *  game_create crea el juego, para ello inicializa todos sus espacios a NULL,
 *  inicializa el jugador, el comando, el dado y todos los objetos del juego.
 *
 * @param game puntero no nulo tipo Game
 * @return devuelve OK si se ha creado correctamente la interfaz del juego
 */

STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->player = player_create(1, "jugador");
  game->last_cmd = NULL;
  game->die = die_create(1);

  for (i = 0; i < MAX_SPACES; i++) {
    game->objects[i] = NULL;
  }

  return OK;
}


/**
 * @brief crea un juego a partir de un archivo, crea el juego, carga el espacio y situa al jugador y al objeto en la posicion 0 del juego
 *
 * @param game puntero no nulo tipo Game
 * @param filename nombre del archivo a partir del cual se creara el juego

 * @return devuelve ERROR en caso de que no se cree correctamente el juego o en caso de que los espacios no se cargen correctamente. Devuelve OK si todo ha ido buen
 *
 */

STATUS game_create_from_file(Game* game, char* filename_spaces, char* filename_objects) {

  if (game_create(game) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename_spaces) == ERROR)
    return ERROR;

  if (game_load_objects(game, filename_objects) == ERROR)
    return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));

  return OK;
}



/**
 * @brief destruye el juego, para ello tiene que destruir los espacios que forman el juego llamando a la funcion space_destroy
 *
 * @param game puntero no nulo tipo Game
 * @return devuelve OK si el juego se ha destruido correctamente. Devuelve ERROR si no se ha destruido correctamente.
 *
 */

STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; (i < MAX_SPACES) && (game->objects[i] != NULL); i++) {
    object_destroy(game->objects[i]);
  }

  player_destroy(game->player);
  die_destroy(game->die);
  game->last_cmd = NULL;

  return OK;
}



/**
 * @brief Añande un espacio al juego
 *
 * @param game puntero no nulo tipo Game
 * @param space puntero tipo Space
 * @return devuelve ERROR si la funcion no recibe el espacio como parametro de entrada. Devuelve error si se pasa del maximo de espacios. Devuelve OK si todo ha ido correctamente.

 */

STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL)
    return ERROR;


  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES)
    return ERROR;


  game->spaces[i] = space;

  return OK;
}


/**
 * @brief Añande un espacio al juego
 *
 * @param game puntero no nulo tipo Game
 * @param space puntero tipo Space
 * @return devuelve ERROR si la funcion no recibe el espacio como parametro de entrada. Devuelve error si se pasa del maximo de espacios. Devuelve OK si todo ha ido correctamente.

 */

STATUS game_add_object(Game* game, Object* object) {
  int i = 0;

  if (object == NULL)
    return ERROR;


  while ( (i < MAX_SPACES) && (game->objects[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES)
    return ERROR;


  game->objects[i] = object;

  return OK;
}


/**
 * @brief Devuelve la id del enésimo espacio de un juego
 *
 * @param game puntero no nulo tipo Game
 * @param int numero entero que nos indica la posicion del espacio a considerar
 * @return devuelve el id del espacio pedido
 *
 */

Id game_get_space_id_at(Game* game, int position) {
  if (position < 0 || position >= MAX_SPACES)
    return NO_ID;

  return space_get_id(game->spaces[position]);
}


/**
 * @brief nos permite obtener el espacio del juego con cierto id
 *
 * @param game puntero no nulo tipo Game
 * @param id indica la posicion
 * @return devuelve NULL: si la funcion no recibe ninguna posición o si no se ha podido obtener bien el espacio.
 * Devuelve el espacio si se ha obtenido correctamente
 *
 */

Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i]))
      return game->spaces[i];
  }

  return NULL;
}


/**
 * @brief nos permite obtener el objeto del juego con cierto id
 *
 * @param game puntero no nulo tipo Game
 * @param id indica la posicion
 * @return devuelve NULL: si la funcion no recibe ninguna posición o si no se ha podido obtener bien el objeto.
 * Devuelve el objeto si se ha obtenido correctamente
 *
 */

Object* game_get_object(Game* game, Id id){
  int i = 0;

  if (id == NO_ID)
    return NULL;


  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    if (id == object_get_id(game->objects[i]))
      return game->objects[i];
  }

  return NULL;
}


/**
 * @brief cambia la localización/posicion del jugador
 *
 * @param game puntero no nulo tipo Game
 * @param id indica una posicion
 * @return devuelve ERROR si la funcion no ha recibido ninguna posicion (id)
 *
 */

STATUS game_set_player_location(Game* game, Id id) {
  if (id == NO_ID)
    return ERROR;

  player_set_location(game->player, id);

  return OK;
}


/**
 * @brief cambia la localizacion/posicion del objeto
 *
 *
 * @param game puntero no nulo tipo Game
 * @param id indica una posicion
 * @return devuelve error si la funcion no ha recibido ninguna posicion(id)
 *
 */

STATUS game_set_object_location(Game* game, Id space_id, Id object_id) {
  int id_aux;

  if (space_id == NO_ID || object_id == NO_ID)
    return ERROR;

  id_aux = game_get_object_location(game, object_id);

  space_add_object(game_get_space(game, space_id), object_id);
  space_del_object(game_get_space(game, id_aux), object_id);

  return OK;
}


/**
 * @brief nos permite obtener la localizacion/posicion del jugador
 *
 * @param game puntero no nulo tipo Game
 * @return devuelve la localizacion del jugador
 *
 */

Id game_get_player_location(Game* game) {
  return player_get_location(game->player);
}



/**
 * @brief nos permite obtener la localizacion/posicion del objeto
 *  lo que hacemos es obtener el id del espacio (id_aux) para que dentro del bucle podamos comprobar si el objeto se encuentra
 *  en el espacio, lo hacemos mediante space_check_object que nos comprueba si el objecto esta en el set.
 *
 * @param game puntero no nulo tipo Game
 * @param object_id id del objeto a obtener la localizacion
 * @return devuelve el esapcio donde se encuentra el objeto
 *
 */

 Id game_get_object_location(Game* game, Id object_id) {
   int i;
   Id id_aux;

   if (!game || object_id == NO_ID)
     return NO_ID;

   if (player_get_object(game->player) == object_id)
     return player_get_location(game->player);

   for (i=0; i < MAX_SPACES && game->spaces[i] != NULL; i++){
     id_aux = game_get_space_id_at(game, i);
     if(object_in_space(game_get_space(game, id_aux), object_id) == TRUE)
       return id_aux;
   }

   return NO_ID;
 }


/**
 * @brief Devuelve el número de objetos en el juego
 *
 * @param game puntero al juego
 * @return int número de objetos en el juego
 */

int game_get_object_num(Game* game) {
  int i;
  for(i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++);
  return (i+1);
}


/**
 * @brief Actualiza el juego a través de un comando que recive como argumento de entrada
 *
 * @param game puntero no nulo tipo Game
 * @param cmd comando que le indica la accion a realizar
 * @return devuelve OK si se ha actualizado correctamente. Devuelve ERROR en caso de que no se haya podido actualizar como es debido
 *
 */

STATUS game_update(Game* game, Command * cmd) {

    game->last_cmd = cmd;

    (*game_callback_fn_list[command_get_action(cmd)])(game);

    return OK;
}


/**
 * @brief obtiene el ultimo comando utilizado
 *
 * @param game puntero no nulo tipo Game
 * @return devuelve el ultimo comando utilizado en el juego
 *
 */

T_Command game_get_last_command(Game* game){

    return command_get_action(game->last_cmd);
}


/**
 * @brief imprime la apariencia del juego, para ello tiene que llamar a space_print que imprime el espacio
 *
 * @param game puntero no nulo tipo Game
 *
 */

void game_print_data(Game* game) {
    int i = 0;

    printf("\n\n-------------\n\n");
    printf("=> Spaces: \n");

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        space_print(game->spaces[i]);
    }

    for (i = 0; i < game_get_object_num(game); i++) {
      printf("=> %s location: %ld\n", object_get_name(game->objects[i]), game_get_object_location(game, object_get_id(game->objects[i])));
    }

    printf("=> Player location: %ld\n", game_get_player_location(game));
    printf("prompt:> ");
}



/**
 * @brief detecta si el juego se ha acabado
 *
 * @param game puntero tipo no nulo tipo Game
 * @return devuelve FALSE
 *
 */

BOOL game_is_over(Game* game) {

    return FALSE;
}

/**
 * @brief Implementacion de LLamadas para cada accion
*/

void game_callback_unknown(Game* game) {
}

void game_callback_quit(Game* game) {
}


/**
 * @brief avanza el jugador a la siguiente casilla
 *
 * @param game puntero no nulo al juego a considerar
 *
 */

void game_callback_next(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  space_id = game_get_player_location(game);

  if (space_id == NO_ID)
    return;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {

    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);

        game_set_player_location(game, current_id);
      return;
    }
  }
}


/**
 * @brief retrocede el jugador a la casilla anterior
 *
 * @param game puntero no nulo al juego a considerar
 *
 */

void game_callback_back(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
    return;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);

      if (current_id != NO_ID)
        game_set_player_location(game, current_id);

      return;
    }
  }
}


/**
 * @brief el jugador recoge un objeto
 *
 * @param game puntero no nulo al juego a considerar
 *
 */

void game_callback_pick(Game* game) {
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id || game_get_space(game, space_id) == NULL)
    return;

  if (player_get_object(game->player) != NO_ID)
  	return;

  if(object_in_space(game_get_space(game, space_id), 1) == TRUE) {
    space_del_object(game_get_space(game, space_id), 1);
    player_set_object(game->player, 1);
  }

	return;
}


/**
 * @brief el jugador suelta un objeto
 *
 * @param game puntero no nulo al juego a considerar
 *
 */

void game_callback_drop(Game* game) {
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id || game_get_space(game, space_id) == NULL)
    return;

  if (player_get_object(game->player) != 1)
  	return;

  space_add_object(game_get_space(game, space_id), 1);
  player_set_object(game->player, NO_ID);

	return;
}


/**
 * @brief hace que vaya hacia la casilla de la derecha
 *
 * @param game puntero no nulo al juego a considerar
 *
 */

void game_callback_right(Game* game) {

  Id space_id, space_east_id = NO_ID;


  space_id = game_get_player_location(game); /*!< conseguimos el espacio donde esta el jugador*/

  if (NO_ID == space_id) /*!< si no tenemos espacio return*/
    return;

  /*!< ahora tengo que hacer que salte de casilla*/

  space_east_id = space_get_east(game_get_space(game,space_id));
  if( space_east_id != NO_ID) {
    game_set_player_location(game,space_east_id);
    return;
  }

  return;

}



/**
 * @brief hace que vaya hacia la casilla de la izquierda
 *
 * @param game puntero no nulo al juego a considerar
 *
 */

void game_callback_left(Game* game) {

  Id space_id, space_west_id = NO_ID;

  space_id = game_get_player_location(game); /*!< conseguimos el espacio donde esta el jugador*/


  if (NO_ID == space_id) /*!< si no tenemos espacio return*/
    return;

    /*!< ahora tengo que hacer que salte de casilla*/

  space_west_id = space_get_west(game_get_space(game,space_id));
  if( space_west_id != NO_ID) {
    game_set_player_location(game, space_west_id);
    return;
  }

  return;

}


/**
 * @brief hace que vaya hacia la casilla de la izquierda
 *
 * @param game puntero no nulo al juego a considerar
 * @param die puntero no nulo al dado a considerar
 *
 */

void game_callback_roll(Game* game) {
  int value;

  if (!game)
    return;

  value = die_roll(game->die, getpid());

  if (value == -1)
    return;

  return;
}
