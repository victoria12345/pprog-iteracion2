/**
* @brief Test para comprobar correcto funcionamiento de die
*
* @file die_test.c
* @author Victoria Pelayo e Ignacio Rabuñal.
* @version 2.0
* @date 15-10-2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "die.h"

int main(){
  int i;

  Die *die;

  die = die_create(1);
  if(die == NULL){
    fprintf(stderr, "Error al crear el dado");
    return 1;
  }

  for (i = 0; i<10; i++){

    printf("%d", i);

    die_roll(die, getpid());

    die_print(die);

    printf("\n");
  }

  die_destroy(die);

  return 0;
}
