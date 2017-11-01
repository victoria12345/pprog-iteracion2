/**
* @brief Implementación de la función de carga de espacios.
*
* @file game_reader.c
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 1.0
* @date 24-09-2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"

STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  line line1,line2,line3;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(line1, toks);
      toks = strtok(NULL, "|");
      strcpy(line2, toks);
      toks = strtok(NULL, "|");
      strcpy(line3, toks);
      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s\n", id, name, north, east, south, west, line1,line2,line3);
      #endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_gdesc(space, line1,0);
        space_set_gdesc(space, line2,1);
        space_set_gdesc(space, line3,2);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}


STATUS game_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id, id_space = NO_ID;
  Space* space;
  Object* object;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_space = atol(toks);

      #ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, id_space);
      #endif
      object = object_create(id, name);
      if(object == NULL) fprintf(stderr, "Error creando el objeto");
      if(object != NULL) {

        space = game_get_space(game, id_space);
        if(space == NULL )fprintf(stderr, "Error creando el espacio");

        if(game_add_object(game, object) == ERROR) fprintf(stderr,"Error al añadir objeto al juego");
        if(space_add_object(space, id) == ERROR) fprintf(stderr,"Error al añadir objeto al espacio");

      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}
