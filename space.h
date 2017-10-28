/**
* @brief Prototipos de las funciones para el manejo de casillas
*
* @file space.h
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 1.1
* @date 13-01-2015
* @copyright GNU Public License
*/

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "object.h"
#include "player.h"
#include "set.h"


/** */
#define MAX_SPACES 100
#define FIRST_SPACE 1

/**
*@brief casilla o espacio.
*Esta estructura define una casilla que consta de un nombre y un Id que la identifican
*además de tener un 4 Ids que indican con que otras casillas está conectada a través de
*los 4 puntos cardinales y un entero que indica el id del objeto que se encuentra en esa casilla.
*/
typedef struct _Space Space;

/**
*@brief crea un casilla con un Id dado.
*@param id Id de la casilla que queremos crear.
*@return space puntero a la casilla creada.
*/
Space* space_create(Id id);

/**
*@brief destruye una casilla.
*@param space puntero a la casilla que queremos destruír.
*/
STATUS space_destroy(Space* space);

/**
*@brief devuelve el id de una casilla que pasamos como argumento.
*@param space casilla cuyo nombre queremos saber.
*@return space ->id id de la casilla.
*/
Id space_get_id(Space* space);

/**
*@brief establece o cambia el nombre de una casilla.
*@param space casilla cuyo nombre queremos establecer o cambiar.
*@param name puntero al nuevo nombre de la casilla.
*@return devuelve OK si el nombre se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS space_set_name(Space* space, char* name);

/**
*@brief devuelve el nombre de una casilla que pasamos como argumento.
*@param space casilla cuyo nombre queremos saber.
*@return nombre de la casilla.
*/
const char* space_get_name(Space* space);

/**
*@brief establece o cambia la casilla que se encuentra al norte de una casilla dada.
*@param space casilla dada.
*@param Id id de la casilla que queremos colocar al norte.
*@return devuelve OK si la casilla se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS space_set_north(Space* space, Id id);

/**
*@brief devuelve la casilla que se encuentra al norte de una casilla que pasamos como argumento.
*@param space casilla cuyo norte queremos saber.
*@return space->north id de la casilla que se encuentra al norte de la dada.
*/
Id space_get_north(Space* space);

/**
*@brief establece o cambia la casilla que se encuentra al sur de una casilla dada.
*@param space casilla dada.
*@param Id id de la casilla que queremos colocar al sur.
*@return devuelve OK si la casilla se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS space_set_south(Space* space, Id id);

/**
*@brief devuelve la casilla que se encuentra al sur de una casilla que pasamos como argumento.
*@param space casilla cuyo sur queremos saber.
*@return space->south id de la casilla que se encuentra al sur de la dada.
*/
Id space_get_south(Space* space);

/**
*@brief establece o cambia la casilla que se encuentra al este de una casilla dada.
*@param space casilla dada.
*@param Id id de la casilla que queremos colocar al este.
*@return devuelve OK si la casilla se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS space_set_east(Space* space, Id id);

/**
*@brief devuelve la casilla que se encuentra al este de una casilla que pasamos como argumento.
*@param space casilla cuyo este queremos saber.
*@return space->east id de la casilla que se encuentra al este de la dada.
*/
Id space_get_east(Space* space);

/**
*@brief establece o cambia la casilla que se encuentra al oeste de una casilla dada.
*@param space casilla dada.
*@param Id id de la casilla que queremos colocar al oeste.
*@return devuelve OK si la casilla se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS space_set_west(Space* space, Id id);

/**
*@brief devuelve la casilla que se encuentra al oeste de una casilla que pasamos como argumento.
*@param space casilla cuyo oeste queremos saber.
*@return space->west id de la casilla que se encuentra al oeste de la dada.
*/
Id space_get_west(Space* space);

/**
*@brief añade un objeto a la casilla.
*@param space casilla donde queremos añadir un objeto.
*@param id_object id del objeto que queremos añadir
*@return OK si se realiza correctamente y ERROR si n ha sido asi.
*/
STATUS space_add_object(Space* space, Id id_object);

/**
*@brief elimina un objeto a la casilla.
*@param space casilla donde queremos eliminar un objeto.
*@param id_object id del objeto que queremos eliminar
*@return OK si se realiza correctamente y ERROR si n ha sido asi.
*/
STATUS space_del_object(Space* space, Id id_object);

/**
*@brief devuelve si un objeto esta en una casilla o no.
*@param space casilla donde queremos saber si esta.
*@param id_object id del objeto que buscamos.
*@return TRUE si esta en la casilla y FALSE si no.
*/
BOOL object_in_space(Space* space, Id id_object);

/**
*@brief devuelve el id del objeto que se encuentra en una casilla que pasamos como argumento.
*@param space casilla cuyo objeto queremos saber.
*@return space->id_object id del objeto que se encuentra en la casilla.
*/
Id* space_get_object(Space* space);

/**
*@brief imprime en la pantalla toda la información de una casilla.
*@param space casilla que queremos imprimir.
*@return devuelve OK si la casilla se imprime correctamente y ERROR si algo falla durante el proceso.
*/
STATUS space_print(Space* space);

#endif
