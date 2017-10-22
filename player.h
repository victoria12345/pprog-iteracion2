/** 
 * @brief Funcionalidad para el manejo de jugadores
 * 
 * @file player.h
 * @author Victoria Pelayo e Ignacio Rabunnal
 * @version 1.0 
 * @date 25-09-2017 
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/**
*@brief Jugador
*Esta estructura define un jugador que consta de un nombre y un Id que lo identifican
*además de un Id que indica la casilla en la que está situado y un entero que identifica el objeto que lleva el jugador. 
*/
typedef struct _Player Player;

/**
*@brief crea un jugador.
*@param id entero mayor o igual que 0.
*@param name cadena de caracteres correctamente formada.
*@return newplayer puntero al jugador creado.
*/
Player* player_create(Id id, char* name);

/**
*@brief destruye un jugador.
*@param player puntero al jugador que queremos destruir.
*/
void player_destroy(Player* player);

/**
*@brief devuelve el id de un jugador que pasamos como argumento.
*@param player jugador cuyo id queremos saber.
*@return player->id  id del jugador o o NO_ID si hay algún error.
*/
Id player_get_id(Player* player);

/**
*@brief devuelve el nombre de un jugador que pasamos como argumento.
*@param player jugador cuyo nombre queremos saber.
*@return player->name nombre del jugador o NULL si hay algún error.
*/
char* player_get_name(Player* player);

/**
*@brief devuelve el id del objeto que porta un jugador que pasamos como argumento.
*@param player jugador cuyo objeto queremos saber.
*@return player->id id del objeto que porta el jugador o NO_ID si hay algún error.
*/
Id player_get_object(Player* player);

/**
*@brief devuelve el id de la casilla en la que se encuentra un jugador que pasamos como argumento.
*@param player jugador cuyo objeto queremos saber.
*@return player->id id de la casilla en la que se encuentra el jugador o NO_ID si hay algún error.
*/
Id player_get_location(Player* player);

/**
*@brief cambia el nombre de un objeto.
*@param player jugador cuyo nombre queremos cambiar.
*@param name puntero al nuevo nombre del objeto.
*@return devuelve OK si el nombre se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS player_set_name(Player* player, char* name);

/**
*@brief cambia el id de un jugador.
*@param player jugador cuyo nombre queremos cambiar.
*@param id entero que contiene el nuevo id del jugador.
*@return devuelve OK si el id se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS player_set_id(Player* player, Id id);

/**
*@brief establece el objeto que porta un jugador.
*@param player jugador al cual queremos dar un objeto.
*@param id_object entero que contiene el id del objeto que queremos dar al jugador.
*@return devuelve OK si el objeto se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS player_set_object(Player* player, Id id_object);

/**
*@brief cambia la casilla en la que se encuentra un jugador.
*@param player jugador que queremos mover de casilla.
*@param id_space id que contiene el id de la casilla a la que queremos mover al jugador.
*@return devuelve OK si el jugador es movido a la casilla indicada y ERROR si algo falla durante el proceso.
*/
STATUS player_set_location(Player* player, Id id_space);

/**
*@brief imprime en la pantalla toda la información de un jugador.
*@param player jugador que queremos imprimir.
*@return devuelve OK si el jugador se imprime correctamente y ERROR si algo falla durante el proceso.
*/
STATUS player_print(Player* player);

#endif
