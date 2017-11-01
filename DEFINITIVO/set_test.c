/**
* @brief Test para ver si funciona el modulo set
*
* @file set_test.c
* @author Victoria Pelayo
* @version 1.0
* @date 28/09/2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include "set.h"

int main(){
	Set *s1;
	int i;
	Id* ids;

	if ((s1 = set_create()) == NULL) {
		fprintf(stderr,"Error creando set");

		return -1;
	}

	set_print(s1);

	for(i = 0; i < N_OBJECTS; i++ )
	set_add_element(s1,i+1);

	set_print(s1);

	if (set_add_element(s1,i+1) == OK)
	fprintf(stderr, "Añade elementos de mas.\n");

	printf("Elemento 1:  posicion:%d \n", get_position_element(s1,1));
	printf("Elemento 25:  posicion:%d \n", get_position_element(s1,25));
	printf("Elemento 51:  posicion:%d \n", get_position_element(s1,51));

	ids = set_get_elements(s1);

	fprintf(stderr, "Lista ids: \n");

	for(i = 0; i < N_OBJECTS; i++)
	fprintf(stderr, "%ld \n", ids[i]);

	fprintf(stderr, "\n");

	if (set_del_element(s1,51) == OK)
	fprintf(stderr, "Elimina elementos que no estan");

	for (i = 0; i< N_OBJECTS; i++)
	set_del_element(s1, i+1);

	set_print(s1);

	if (set_del_element(s1,4) == OK)
	fprintf(stderr, "Elimina elementos de mas");

	set_destroy(s1);

	free(ids);

	return 0;
}
