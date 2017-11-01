/**
* @brief Implementa las funciones para el manejo de las casillas.
*
* @file space.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 1.0
* @date 29/09/2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"


struct _Space {
  Id id; /*!< identificador */
  char name[WORD_SIZE + 1]; /*!< nombre */
  Id north; /*!< Id de la casilla que está al norte */
  Id south; /*!< Id de la casilla que está al sur */
  Id east; /*!< Id de la casilla que está al este */
  Id west; /*!< Id de la casilla que está al oeste */
  Set* objects; /*!< id del objeto que se encuentra en la casilla */
  line gdesc[3]; /*! Descripcion grafica de la casilla */
};


Space* space_create(Id id) {
  Space *newSpace = NULL;

  if (id == NO_ID)
  return NULL;

  newSpace = (Space *) malloc(sizeof(Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->objects = set_create();

  strcpy(newSpace->gdesc[0], "       ");
  strcpy(newSpace->gdesc[1], "       ");
  strcpy(newSpace->gdesc[2], "       ");
  return newSpace;
}


STATUS space_destroy(Space* space) {

  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);

  free(space);
  space = NULL;

  return OK;
}


STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}


STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}


STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}


STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}


STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}


STATUS space_add_object(Space* space, Id id_object) {
  if (!space) {
    return ERROR;
  }
  return set_add_element(space->objects, id_object);
}

STATUS space_del_object(Space* space, Id id_object) {
  if (!space  ) {
    return ERROR;
  }
  return set_del_element(space->objects, id_object);
}

const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

BOOL object_in_space(Space* space, Id id_object){
  if(!space) return FALSE;

  if (get_position_element(space->objects, id_object) == -1) return FALSE;

  return TRUE;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}


Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}


Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}


Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}


Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}


Id* space_get_object(Space* space) {
  if (!space) {
    return FALSE;
  }
  return set_get_elements(space->objects);
}

line* space_get_gdesc(Space* space){
  if(!space) return NULL;

  return space->gdesc;
}

STATUS space_set_gdesc(Space* space,line lines, int pos){

  if(!space || !lines) return ERROR;

  strcpy(space->gdesc[pos], lines);
  
  return OK;
}


STATUS space_print(Space* space) {
  Id idaux = NO_ID;
  Id* ids;
  int i;

  if (!space) {
    return ERROR;
  }

  ids = space_get_object(space);

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  if (!ids) {
    set_print(space->objects);
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  fprintf(stdout,"Gdesc:\n");

  for(i = 0; i<= 2; i++) fprintf(stdout,"%s", space->gdesc[i]);

  free(ids);

  return OK;
}
