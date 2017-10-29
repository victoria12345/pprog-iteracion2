#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "die.h"

int main(){
  int i;
  
  Die *die;

  die = die_create(1);

  for (i = 0; i<10; i++){

    printf("%d", i);

    die_roll(die, getpid());

    die_print(die);

    printf("\n");
  }

  die_destroy(die);
  
  return 0;
}
