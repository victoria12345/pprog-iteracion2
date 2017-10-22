/** 
 * @brief Implementa las funciones para el manejo de objetos.
 * 
 * @file object.c
 * @author Victoria Pelayo e Ignacio Rabuñal
 * @version 1.0 
 * @date 28/09/2017
 * @copyright GNU Public License
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"


struct _Object {
	Id id; /*!< identificador */
	char name[WORD_SIZE + 1]; /*!< nombre */
}; 


Object* object_create(Id id, char* name) {

	Object *newObject = NULL;

	if (id == NO_ID)
		return NULL;

	if (name == NULL || strlen(name) > WORD_SIZE)
		return NULL;

	newObject = (Object *) malloc(sizeof (Object));

	if (newObject == NULL) {
	        return NULL;
	}
    	
	strcpy(newObject->name,name);
	newObject->id = id;

	return newObject;
}


void object_destroy(Object * object) {
	if (!object){
		return;
	}

	free(object);
	object = NULL;

   
}


Id object_get_id(Object* object){
	if(!object) return -1;
	return object -> id;
}


char* object_get_name(Object* object){
	if (!object) return NULL;
	return object -> name;
}


STATUS object_set_name(Object* object, char* name){
	if (!object || !name) return ERROR;
	
	if (!strcpy(object->name, name)) {
        return ERROR;
	}

	return OK;
}


STATUS object_set_id(Object* object, Id id){
	if (!object || id == NO_ID) return ERROR;
	object -> id = id;
	return OK;
}


STATUS object_print(Object *object){
	if (!object || object -> id == NO_ID) return ERROR;

	fprintf(stdout, "Object name : %s. \n Object id: %ld. \n", object->name, object->id);
	return OK;
}
