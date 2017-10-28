/**
* @brief Funcionalidad para el manejo de objetos
*
* @file object.h
* @author Victoria Pelayo e Ignacio Rabunnal
* @version 1.0
* @date 24-09-2017
* @copyright GNU Public License
*/

#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"

/**
*@brief objeto
*Esta estructura define un objeto que consta de un nombre y un entero que lo identifican
*/
typedef struct _Object Object;


/**
*@brief crea un objeto con el entero id y un nombre.
*@param id entero mayor o igual que 0.
*@param name cadena de caracteres correctamente formada.
*@return newObject puntero al objeto creado.
*/
Object* object_create (Id id, char* name);

/**
*@brief destruye un objeto.
*@param object puntero al objeto que queremos destruír.
*/
void object_destroy(Object *object);

/**
*@brief devuelve el id de un objeto que pasamos como argumento.
*@param object objeto cuyo id queremos saber.
*@return object->id id del objeto.
*/
Id object_get_id(Object* object);

/**
*@brief devuelve el nombre de un objeto que pasamos como argumento.
*@param object objeto cuyo nombre queremos saber.
*@return object->name nombre del objeto.
*/
char* object_get_name(Object* object);

/**
*@brief establece o cambia el nombre de un objeto.
*@param object objeto cuyo nombre queremos establecer o cambiar.
*@param name nuevo nombre del objeto.
*@return devuelve OK si el nombre se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS object_set_name(Object* object, char* name);

/**
*@brief establece o cambia el id de un objeto.
*@param object objeto cuyo id queremos establecer o cambiar.
*@param id entero que será el nuevo id del objeto.
*@return devuelve OK si el id se establece correctamente y ERROR si algo falla durante el proceso.
*/
STATUS object_set_id(Object* object, Id id);

/**
*@brief imprime en la pantalla el nombre , el id del objeto y el nombre del objeto.
*@param object objeto que queremos imprimir.
*@return devuelve OK si el objeto se imprime correctamente y ERROR si algo falla durante el proceso.
*/
STATUS object_print(Object *object);

#endif
