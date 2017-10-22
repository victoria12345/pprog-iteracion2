/** 
 * @brief Implementa las funciones para el manejo de los dados.
 * 
 * @file die.c
 * @author Ignacio Rabuñal
 * @version 1.0 
 * @date 11/10/2017
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "die.h"

/**
*@brief dado
*
*Esta estructura define un dado que consta de un id y un entero que indica el valor del dado en la última tirada.
*/
struct _Die {
	Id id; /*!< identificador */
	int latest_roll; /*!< última tirada */
};

Die* die_create(Id id){
	Die *newDie;

	if(id == NO_ID)
		return NULL;

	newDie = (Die*)malloc(sizeof(Die));

	if(newDie == NULL)
		return NULL;

	newDie->id = id;
	newDie->latest_roll = -1;

	return newDie;	
}

void die_destroy(Die *die){
	if(!die)
		return;

	free(die);
	die = NULL;	
}

STATUS die_roll(Die *die, int semilla){
	if(die == NULL || die->id == NO_ID)
		return ERROR;

	srand(semilla);

	die->latest_roll = ((rand() % 6) + 1);
	return OK;
}

STATUS die_print(Die *die){
	if(die == NULL || die->id == NO_ID)
		return ERROR;

	fprintf(stdout, "Die id: %ld. \nDie latest roll: %d.\n ",die->id, die->latest_roll);
	return OK;	
}


