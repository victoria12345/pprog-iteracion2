/**
 * @brief Prototipo de las funciones de juego.
 *
 * @file game.h
 * @author Victoria Pelayo e Ignacio Rabunnal
 * @version 1.1
 * @date 24-09-2017
 * @copyright GNU Public License
 */


#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"


/**
*@brief game
* Se define la estructura de juego
*/
typedef struct _Game{
  Player *player;
  Set *objects;
  Space *spaces[MAX_SPACES + 1];
  T_Command last_cmd;
} Game;


/**
*@brief Crea el juego.
*@param game puntero a game.
*@return OK si el juego se hacreado correctamente y ERROR si no ha sido así.
*/
STATUS game_create(Game* game);

/**
*@brief crea un juego leyendo un fichero. Carga las casillas desde el fichero. Coloca al jugador y al objeto en la casilla inicial.
*@param game puntero a game.
*@param filename  fichero desde el que se lee.
*@return OK si se ha creado bien y ERROR si no ha sido así.
*/
STATUS game_create_from_file(Game* game, char* filename);

/**
*@brief llama a la función correspondiente para ejecutar el comando del juego. Actualiza el último comando del juego a cmd.
*@param game juego al que estamos jugando.
*@param cmd comando introducido por el jugador.
*@return OK si la función se ha realizado correctamente y ERROR si no ha sido así.
*/
STATUS game_update(Game* game, T_Command cmd);

/**
*@brief destruye el juego.
*@param game puntero a game que se quiere destruir.
*@return OK si se ha destruído bien y ERROR si no ha sido así.
*/
STATUS game_destroy(Game* game);

/**
*@brief Devuelve FALSE siempre. Acaba el juego.
*@param game juego que se acaba
*@return FALSE.
*/
BOOL   game_is_over(Game* game);

/**
*@brief Imprime en pantalla
*@param game juego que imprime en pantalla.
*@return FALSE.
*/
void   game_print_screen(Game* game);

/**
*@brief imprime características del juego en pantalla.
*@param game juego que se va a imprimir.
*/
void   game_print_data(Game* game);

/**
*@brief devuelve el espacio del juego que tiene el id que le pasamos.
*@param game juego que contiene los espacios.
*@param id del espacio cuya posición queremos saber.
*@return espacio cuyo id es el que hemos pasado a la función.
*/
Space* game_get_space(Game* game, Id id);

/**
*@brief da la localización del jugador.
*@param juego que contiene al jugador.
*@return player_get_location(game->player) id del espacio en el que se encuentra el jugador.
*/
Id     game_get_player_location(Game* game);

/**
*@brief da la localización del objeto.
*@param game juego que contiene el objeto.
*@return current_id id del espacio en el que se encuentra el objeto o NO_ID en caso de que no se encuentre.
*/
Id     game_get_object_location(Game* game, Id id_object);

/**
*@brief devuelve el último comando que se ha realizado.
*@param game juego que contiene el comando.
*@return game->last_cmd último comando que se ha introducido en el juego.
*/
T_Command game_get_last_command(Game* game);

/**
*@brief añade un espacio(casilla) al juego.
*@param game puntero a game al que se le va a añadir una casilla.
*@param space puntero a space, la casilla que se va a añadir
*@return OK si se ha añadido correctamente y ERROR si no ha sido así.
*/
STATUS game_add_space(Game* game, Space* space);

#endif
