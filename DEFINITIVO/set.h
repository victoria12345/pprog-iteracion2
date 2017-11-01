/**
* @brief Definición de funciones de set
*
* @file set.h
* @author Victoria Pelayo
* @version 1.0
* @date 6-10-2017
* @copyright GNU Public License
*/

#ifndef SET_H
#define SET_H

#include "types.h"
#define N_OBJECTS 3

typedef struct _Set Set;

/**
*@brief crea un set.
*@return puntero al set creado.
*/
Set* set_create();

/**
*@brief destruye un set.
*@param set que se quiere destruir.
*/
void set_destroy(Set* set);

/**
*@brief añade un elemento, en la ultima posicion, al set.
*@param set en el que se añade un elemento.
*@param id_element id del elemento que se quiere añadir.
*@return OK si se realiza correctamente y ERROR si no ha sido así.
*/
STATUS set_add_element(Set *set, Id id_element);

/**
*@brief elimina un elemento del set.
*@param set en el que se elimina un elemento.
*@param id_element id del elemento que se quiere eliminar.
*@return OK si se realiza correctamente y ERROR si no ha sido así.
*/
STATUS set_del_element(Set* set, Id id_element);

/**
*@brief Develve posicion de un elemento en el set
*@param set en el que se busca un elemento.
*@param id_element id del elemento que se busca.
*@return entero de la posicion en el array
*/
int get_position_element(Set* set, Id id_element);

/**
*@brief devuelve los ids del set
*@param set donde estan los elementos
*@return array de ids, array de los elementos del set
*/
Id* set_get_elements(Set* set);

/**
*@brief busca un elemento en el set
*@param set en el que se busca un elemento.
*@param id_element id del elemento que se busca.
*@return TRUE si esta en el set y FALSE si no lo esta
*/
BOOL element_in_set(Set* set, Id id_element);

/**
*@brief devuelve numero de elementos
*@param set cuyo numero de elementos se quiere saber
*@return numero de elementos del set
*/
int n_set_elements(Set* set);

/**
*@brief imprime set por pantalla
*@param set que se quiere imprimir
*@return OK si se realiza correctamente y ERROR si no ha sido así.
*/
STATUS set_print(Set* set);

#endif
