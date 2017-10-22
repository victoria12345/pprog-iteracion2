/**
 * @brief Definición de funciones de set
 *
 * @file command.h
 * @author Victoria Pelayo
 * @version 1.0
 * @date 6-10-2017
 * @copyright GNU Public License
 */

 #ifndef SET_H
 #define SET_H

 #include "types.h"
 #define N_OBJECTS 3

 typedef struct _Set{
	Id elements[N_OBJECTS];
	int num_elements;
}Set;

 Set* set_create();
 void set_destroy(Set* set);
 STATUS set_add_element(Set *set, Id id_element);
 STATUS set_del_element(Set* set, Id id_element);
 BOOL element_in_set (Set* set, Id id_element);
 int get_position_element(Set* set, Id id_element);
 Id* set_get_elements(Set* set);
 STATUS set_print(Set* set);

 #endif
