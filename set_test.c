#include <stdio.h>
#include <stdlib.h>
#include "set.h"

int main(){
	Set *s1;
	int i;
	Id* ids;

	if ((s1 = set_create()) == NULL) {

		printf("Error creando set");

		return -1;
	}

	set_print(s1);

	for(i = 0; i < N_OBJECTS; i++ )
		set_add_element(s1,i+1);

	set_print(s1);

	if (set_add_element(s1,i+1) == OK)
		printf("Añade elementos de mas.");

	printf("Elemento 1:  posicion:%d \n", get_position_element(s1,1));
	printf("Elemento 25:  posicion:%d \n", get_position_element(s1,25));
	printf("Elemento 51:  posicion:%d \n", get_position_element(s1,51));


	ids = set_get_elements(s1);

	printf("Lista ids: \n");

	for(i = 0; i < N_OBJECTS; i++)
		printf("%ld \n", ids[i]);

	printf("\n");

	if (set_del_element(s1,51) == OK)printf("Elimina elementos que no estan");

	for (i = 0; i< N_OBJECTS; i++)
		set_del_element(s1, i+1);

	set_print(s1);

	if (set_del_element(s1,4) == OK) printf("Elimina elementos de mas");

	set_destroy(s1);

	free(ids);

	ids = NULL;

	return 0;
}
