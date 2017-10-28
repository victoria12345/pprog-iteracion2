/**
* @brief Implementación del las funciones de set
*
* @file command.h
* @author Victoria Pelayo
* @version 1.0
* @date 6-10-2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include "set.h"

struct _Set{
  Id elements[N_OBJECTS]; /*!< Array de los ids del set*/
  int num_elements; /*!< numero de elementos */
};


Set* set_create(){
  Set *newSet;
  newSet = (Set*) malloc(sizeof(Set));
  if( !newSet ) return NULL;

  newSet->num_elements = 0;

  return newSet;
}

void set_destroy (Set* set){
  if (!set) return;

  free(set);
  set = NULL;

}

STATUS set_add_element (Set* set, Id id_element){
  int i;
  if (!set || id_element == NO_ID) return ERROR;

  if(set->num_elements == N_OBJECTS) return ERROR;

  /** ya esta en el set*/
  if ((i = get_position_element(set, id_element)) != -1) return ERROR;

  set->elements[set->num_elements] = id_element;
  set->num_elements ++;

  return OK;

}

STATUS set_del_element (Set* set, Id id_element){
  int i;
  if (!set || id_element == NO_ID) return ERROR;

 /***no esta al set*/
  if ((i = get_position_element(set, id_element)) == -1) return ERROR;

  set->elements[i] = set->elements [set->num_elements -1];
  set->elements [set->num_elements - 1] = NO_ID;
  set->num_elements = set->num_elements -1;

  return OK;
}


int get_position_element(Set* set, Id id_element){
  int i;

  if(!set || id_element == NO_ID) return -1;

  for (i = 0; i <= set->num_elements; i++){
    if (set->elements[i] == id_element) return i;
  }
  return -1;
}

Id* set_get_elements(Set* set){
  int i;
  Id* ids;

  if(!set) return NULL;

  ids = (Id*)malloc(sizeof(ids[0]) * (set->num_elements + 1));

  if(!ids) return NULL;

  for (i = 0; i <= (set->num_elements); i++){
    ids[i] = set->elements[i];
  }

  return ids;
}

int n_set_elements(Set* set){
  if(!set) return -1;

  return set->num_elements;
}

STATUS set_print(Set* set){
  int i;
  if (!set) return ERROR;

  fprintf (stdout,"Numero de elementos: %d.\n", set->num_elements);

  for ( i = 0; i < set->num_elements; i++) {
    fprintf(stdout, "Elemento %d: %ld\n", i+1, set->elements[i]);
  }
  return OK;

}
