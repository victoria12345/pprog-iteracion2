/**
* @brief Implementa la interfaz del juego y todas las funciones de los comandos.
* Hemos añadido la funcion game_add_object
* @file game.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 2.0
* @date 03-10-2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "game_reader.h"

#define N_CALLBACK 9

/**
Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
List of callbacks for each command in the game
*/
void game_callback_unknown(Game* game);
void game_callback_quit(Game* game);
void game_callback_next(Game* game);
void game_callback_back(Game* game);
void game_callback_pick(Game* game);
void game_callback_drop(Game* game);
void game_callback_left(Game* game);
void game_callback_right(Game* game);
void game_callback_die(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_quit,
  game_callback_next,
  game_callback_back,
  game_callback_pick,
  game_callback_drop,
  game_callback_left,
  game_callback_right,
  game_callback_die
};

/**
Private functions
*/
Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id_space, Id id_object);

/**
Game interface implementation
*/


STATUS game_create(Game* game) {
  int i;
  Object *obj;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->die = die_create(1);

  game->player = player_create(1,"jugador");

  game->objects = set_create();

  obj = object_create(2, "objeto");

  set_add_element(game->objects, 2);

  object_destroy(obj);

  game->last_cmd = (Command*)malloc(sizeof(Command));

  return OK;
}


STATUS game_create_from_file(Game* game, char* filename) {

  if (game_create(game) == ERROR)
  return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
  return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0), 2);

  return OK;
}


STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  player_destroy (game->player);
  set_destroy(game->objects);
  die_destroy(game->die);
  free(game->last_cmd);
  return OK;
}


STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

STATUS game_add_object(Game* game, Object* object){
  if (object == NULL)
    return ERROR;

  return set_add_element(game->objects, object_get_id(object));
}

/**
*@brief devuelve el id del espacio que ocupa la posicion pasada en la cadena de casillas del juego.
*@param game juego que contiene las casillas.
*@param position posicion de la cadena de spaces del espacio cuyo id queremos saber.
*@return space_get_id(game->spaces[position]) id del espacio que queríamos saber.
*/
Id game_get_space_id_at(Game* game, int position) {

  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}


Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}

/**
*@brief cambia la localización del jugador.
*@param game juego que contiene al jugador.
*@param id del espacio nuevo en el que va a estar el jugador.
*@return OK si la función se ha realizado correctamente y ERROR si no ha sido así.
*/
STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  player_set_location(game->player,id); return OK;
}

/**
*@brief cambia la localización del objeto.
*@param game juego que contiene al objeto.
*@param id del espacio nuevo en el que va a estar el objeto.
*@return OK si la función se ha realizado correctamente y ERROR si no ha sido así.
*/
STATUS game_set_object_location(Game* game, Id id_space, Id id_object) {
  Space *space;
  int i;

  space = game_get_space (game, id_space);

  for(i = 0; i < MAX_SPACES; i++){

    if(object_in_space(game->spaces[i], id_object) == TRUE)
      if(space_del_object(game->spaces[i], id_object) == ERROR)
        return ERROR;
  }

  if (!space)
  return ERROR;
  space_add_object(space, id_object);

  return OK;
}


Id game_get_player_location(Game* game) {
  return player_get_location(game->player);
}


Id game_get_object_location(Game* game, Id id_object) {
  int i;
  Id current_id;

  if (player_get_object(game->player) == id_object)
  return player_get_location(game->player);

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);

    if (object_in_space(game->spaces[i], id_object) == TRUE)
    return current_id;
  }
  return NO_ID;
}


STATUS game_update(Game* game, Command cmd) {
  game->last_cmd->command = cmd.command;
  (*game_callback_fn_list[cmd.command])(game);
  return OK;
}


Command* game_get_last_command(Game* game){
  return game->last_cmd;
}


void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }
  printf("=> Objects: \n");
  set_print(game->objects);
  printf("=> Player location: %ld\n", game_get_player_location(game));
  printf("prompt:> ");
}


BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
Callbacks implementation for each action
*/


/**
*@brief No hace nada. Cuando el parámetro introducido por el usuario no es reconocido.
*@param game juego que se está jugando.
*/
void game_callback_unknown(Game* game) {
}

/**
*@brief No hace nada.Cuando el parámetro introducido por el usuario es quit.
*@param game juego que se está jugando.
*/
void game_callback_quit(Game* game) {
}

/**
*@brief Salta a la siguiente casilla.
*@param game juego que se está jugando.
*/
void game_callback_next(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/**
*@brief Retrocede una casilla.
*@param game juego que se está jugando.
*/
void game_callback_back(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
        game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/**
*@brief Coge el objeto, esto solo se puede hacer si el jugador no tenía ya otro objeto en la mano y si hay un objeto en la casilla que estamos.
*@param game juego que se está jugando.
*/

void game_callback_pick(Game* game){
  Id *objects;
  Id space_id;
  Space *space;

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) return;

  space = game_get_space(game,space_id);
  objects = space_get_object(space);

  if (!space || objects[0] == NO_ID) return;

  if (player_get_object(game->player) != NO_ID) return;

  if (game_get_object_location(game, 2) != space_id) return;

  free(objects);

  player_set_object (game->player, 2);
  space_del_object(space, 2);

  space = NULL;
}


/**
*@brief Dejamos una objeto en la casilla que estamos. Solo se puede hacer si el jugador tenía un objeto y si no hay otro objeto en la casilla.
*@param game juego que se está jugando.
*/

void game_callback_drop(Game* game){

  Id space_id;
  Space* space;

  space_id = game_get_player_location(game);
  if(space_id == NO_ID) return;

  space = game_get_space(game, space_id);
  if(!space) return;
  space = NULL;

  if(player_get_object(game->player) == NO_ID) return;

  space_add_object(space, 2);
  player_set_object(game->player, NO_ID);

}

/**
*@brief Salta a la casilla de la derecha, si tiene.
*@param game juego que se esta jugando.
*/
void game_callback_right(Game* game){
  int i = 0;
  Id current_id = NO_ID, current_id2 = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_east (game->spaces[i]);
      if (current_id == NO_ID) return;
      else{
        current_id2 = space_get_west(game_get_space(game,current_id));

        /** Comprueba que las ocas estén "conectadas"*/

        if (current_id2 != space_id) return;
        game_set_player_location(game,current_id);
      }
    }
  }
}

/**
*@brief Salta a la casilla de la izquiera, si tiene.
*@param game juego que se esta jugando.
*/
void game_callback_left(Game* game){
  int i = 0;
  Id current_id = NO_ID, current_id2 = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_west (game->spaces[i]);
      if (current_id == NO_ID) return;
      else{
        current_id2 = space_get_east(game_get_space(game,current_id));

        /** Comprueba que las ocas estén "conectadas"*/

        if (current_id2 != space_id) return;
        game_set_player_location(game,current_id);
      }
    }
  }
}


/**
*@brief lanza el dado
*@param game juego que se esta jugando
*/
void game_callback_die(Game* game){
  int num;

  if (!game || !game->die) return;

  num = die_roll(game->die, getpid());

  if ( num == -1){
    return;
  }
}
