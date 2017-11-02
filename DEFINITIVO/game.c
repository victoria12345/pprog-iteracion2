/**
* @brief Implementa la interfaz del juego y todas las funciones de los comandos.
*
* Se han cambiado ciertas funciones debido al cambio de los comandos
*
* @file game.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 2.0
* @date 0.-11-2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
void game_callback_roll(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
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
Private functions
*/

STATUS game_add_space(Game* game, Space* space);
Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id, Object* object);



/**
Game interface implementation
*/

STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->player = player_create(1,"jugador");

  for (i = 0; i < MAX_SPACES; i++) {
    game->objects[i] = NULL;
  }

  game->die = die_create(3);

  game->last_cmd = command_create();

  return OK;
}


STATUS game_create_from_file(Game* game, char* filename1, char*filename2) {

  if (game_create(game) == ERROR)
  return ERROR;

  if (game_load_spaces(game, filename1) == ERROR)
  return ERROR;

  if (game_load_objects(game, filename2) == ERROR)
  return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));

  return OK;
}


STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  player_destroy (game->player);

  for (i = 0; (i < MAX_SPACES) && (game->objects[i] != NULL); i++) {
    object_destroy(game->objects[i]);
  }
  command_destroy(game->last_cmd);

  die_destroy(game->die);
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
STATUS game_set_object_location(Game* game, Id id, Object* object) {

  Space *space;
  space = game_get_space (game, id);
  if (!space) return ERROR;

  space_add_object(space, object_get_id(object));

  return OK;
}


Id game_get_player_location(Game* game) {
  return player_get_location(game->player);
}


Id game_get_object_location(Game* game, Object* object) {

  int i ;
  Id current_id;

  if (player_get_object(game->player) == object_get_id (object)) return player_get_location(game->player);

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (object_in_space(game->spaces[i], object_get_id (object)) ==TRUE)  return current_id;
  }
  return NO_ID;
}


STATUS game_update(Game* game, Command* cmd) {
  command_set_action(game->last_cmd, command_get_action(cmd));
  command_set_object(game->last_cmd, command_get_object(cmd));

  (*game_callback_fn_list[command_get_action(cmd)])(game);

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
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    printf("=> Object location: %ld\n", game_get_object_location(game, game->objects[i]));
  }

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
*@param game juego que se está jugando
*/
void game_callback_unknown(Game* game) {
  command_set_name(game->last_cmd, "Unknown");

  /** En este caso no asignamos ningun status especifico*/
  command_set_status(game->last_cmd, " ");
}

/**
*@brief No hace nada.Cuando el parámetro introducido por el usuario es quit.
*@param game juego que se está jugando.
*/
void game_callback_quit(Game* game) {
  command_set_name(game->last_cmd, "Quit: ");
  command_set_status(game->last_cmd, "OK");
}

/**
*@brief Salta a la siguiente casilla.
*@param game juego que se está jugando.
*/
void game_callback_next(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  command_set_name(game->last_cmd, "Next: ");

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {

    command_set_status(game->last_cmd, "ERROR");

    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {

    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {

      current_id = space_get_south(game->spaces[i]);

      if (current_id != NO_ID) {

        game_set_player_location(game, current_id);
      }

      command_set_status(game->last_cmd,"OK");

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

  command_set_name(game->last_cmd, "Back: ");

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {

    command_set_status(game->last_cmd,"ERROR" );

    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {

    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {

      current_id = space_get_north(game->spaces[i]);

      if (current_id != NO_ID) {

        game_set_player_location(game, current_id);
      }

      command_set_status(game->last_cmd, "OK");

      return;
    }
  }
}

/**
*@brief Coge el objeto  que se indica
*@param game juego que se está jugando.
*/
void game_callback_pick(Game* game){
  int i,j;
  Id space_id, object_id;
  Space *space;
  Id* ids;

  command_set_name(game->last_cmd, "Pick: ");

  for(i = 0, j = 0; i<= MAX_SPACES && game->objects[i] != NULL && j < 1; i++){

    if(strcmp(object_get_name(game->objects[i]),command_get_object(game->last_cmd)) == 0) j = 100;

  }

  object_id = object_get_id(game->objects[i - 1]);

  space_id = game_get_player_location(game);

  if (space_id == NO_ID || object_id == NO_ID){

    command_set_status(game->last_cmd, "ERROR");

    return;
  }

  space = game_get_space(game,space_id);

  ids = space_get_object(space);

  if (!space ||  ids == NULL){

    command_set_status(game->last_cmd, "ERROR");

    return;
  }

  free(ids);

  if (player_get_object(game->player) != NO_ID){

    command_set_status(game->last_cmd, "ERROR");

    return;
  }

  if (game_get_object_location(game, game->objects[i - 1]) != space_id) {

    command_set_status(game->last_cmd, "ERROR");

    return;
  }

  player_set_object (game->player,object_id);

  space_del_object(space, object_get_id(game->objects[i - 1]));

  command_set_status(game->last_cmd, "OK");
}

/**
*@brief Dejamos una objeto en la casilla que estamos.
* Solo se puede hacer si el jugador tenía un objeto y si no hay otro objeto en la casilla.
*@param game juego que se está jugando.
*/
void game_callback_drop(Game* game){

  Id space_id, object_id;
  Space* space;

  command_set_name(game->last_cmd, "Drop: ");


  space_id = game_get_player_location(game);

  object_id = player_get_object(game->player);

  if (space_id == NO_ID || object_id == NO_ID) {

    command_set_status(game->last_cmd,"ERROR" );

    return;
  }

  space = game_get_space(game, space_id);

  if(!space ){

    command_set_status(game->last_cmd,"ERROR" );

    return;
  }

  space_add_object(space, object_id);

  player_set_object(game->player, NO_ID);

  command_set_status(game->last_cmd,"OK" );
}

/**
*@brief Salta a la casilla de la izquierda, si tiene.
*@param game juego que se está jugando.
*/
void game_callback_left(Game* game){
  int i = 0;
  Id current_id = NO_ID, current_id2 = NO_ID;
  Id space_id = NO_ID;

  command_set_name(game->last_cmd, "Left: ");


  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {

    command_set_status(game->last_cmd,"ERROR" );

    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {

    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {

      current_id = space_get_west (game->spaces[i]);

      if (current_id == NO_ID){

        command_set_status(game->last_cmd,"ERROR" );

        return;
      }
      else{

        current_id2 = space_get_east(game_get_space(game,current_id));

        /** Comprueba que las ocas estén "conectadas"*/

        if (current_id2 != space_id){

          command_set_status(game->last_cmd,"ERROR" );

          return;
        }
        game_set_player_location(game,current_id);

        command_set_status(game->last_cmd,"OK" );
      }
    }
  }
}

/**
*@brief Salta a la casilla de la derecha, si tiene.
*@param game juego que se está jugando.
*/
void game_callback_right(Game* game){
  int i = 0;
  Id current_id = NO_ID, current_id2 = NO_ID;
  Id space_id = NO_ID;

  command_set_name(game->last_cmd, "Right: ");

  space_id = game_get_player_location(game);

  if (space_id == NO_ID) {

    command_set_status(game->last_cmd,"ERROR" );

    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {

    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {

      current_id = space_get_east (game->spaces[i]);

      if (current_id == NO_ID) {

        command_set_status(game->last_cmd,"ERROR" );

        return;
      }
      else{

        current_id2 = space_get_west(game_get_space(game,current_id));

        /** Comprueba que las ocas estén "conectadas"*/

        if (current_id2 != space_id){

          command_set_status(game->last_cmd,"ERROR" );

          return;
        }
        game_set_player_location(game,current_id);

        command_set_status(game->last_cmd,"OK" );
      }
    }
  }
}

/**
*@brief Lanza el dado.
*@param game juego que se está jugando.
*/
void game_callback_roll(Game* game){
  if(game == NULL){

    command_set_status(game->last_cmd,"ERROR" );

    return;
  }

  command_set_name(game->last_cmd, "Roll: ");

  die_roll(game->die, time(NULL));

  command_set_status(game->last_cmd,"OK" );
}
