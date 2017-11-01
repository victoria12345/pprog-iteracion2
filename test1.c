#include <stdlib.h>
#include <stdio.h>
#include "space.h"

int main(){
  Space* s;
  line lines[2];
  line * lineas;
  s = space_create(1);
  strcpy(lines[0], "    j j");
  strcpy(lines[1], "    j j");
  space_set_gdesc(s,lines[0],0);
  space_set_gdesc(s,lines[0],1);

  lineas = space_get_gdesc(s);

  printf("%s", lineas[0]);
  space_destroy(s);
  return 0;
}
