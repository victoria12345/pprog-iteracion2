/**
 * @brief Funcionalidad de la carga de espacios
 *
 * @file game_reader.h
 * @author Victoria Pelayo e Ignacio Rabuñal
 * @version 1.0
 * @date 24-09-2017
 * @copyright GNU Public License
 */

#ifndef __GAME_READER_H__
#define __GAME_READER_H__

#include "game.h"

/**
* @brief carga espacios en el juego a través de un fichero.
*@param game juego al que vamos a añadir espacios(casillas).
*@param filename fichero desde el que se va a leer.
*@return OK si la función se ha realizado correctamente y ERROR si no ha sido así.
*/
STATUS game_load_spaces(Game* game, char* filename);

/**
* @brief carga objetos en el juego a través de un fichero.
*@param game juego al que vamos a añadir objetos.
*@param filename fichero desde el que se va a leer.
*@return OK si la función se ha realizado correctamente y ERROR si no ha sido así.
*/
STATUS game_load_objects(Game* game, char* filename);


#endif
