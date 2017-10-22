#include <stdio.h>
#include <stdlib.h>
#include "die.h"

void main(){

  Die *die;

  die = die_create(1);
  die_roll(die, getpid());
  die_print(die);
  die_destroy(die);

}
