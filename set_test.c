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

	for(i = 0; i < N_OBJECTS; i++ ) set_add_element(s1,i+1);

	set_print(s1);

	set_add_element(s1,1);

	set_print(s1);

	printf("Elemento 1: en el conjunto %d, posicion:%d \n", element_in_set(s1,1), get_position_element(s1,1));

	ids = set_get_elements(s1);
	for(i = 0; i < N_OBJECTS; i++) printf("%ld", ids[i]);
	printf("\n");

	for (i = 0; i< N_OBJECTS; i++) set_del_element(s1, i+1);

	set_print(s1);

	if (set_del_element(s1,4) == OK) return -1;

	set_print(s1);

	set_destroy(s1);
	free(ids);
	ids = NULL;

	return 0;
}
