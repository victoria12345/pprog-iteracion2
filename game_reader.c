/**
 * @brief Implementa el modulo game_reader
 *
 * @file game_reader.c
 * @author Sofia sanchez y Luis Perez
 * @version 1.0
 * @date 24-09-2017: Creado y corregido el estilo de programacion y documentacion
 *
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_reader.h"


/**
 * @brief carga los espacios en el juego
 *
 *  Para cargar los espacios en eljuego, se abre el fichero que recibe como parametro de entrada.
 *  Lee las casillas del fichero, es decir, id, nombre de la casilla, norte, este, sur y oeste.
 *  A continuación lo que hace es actualizar el nombre, norte, sur, este y oeste y añade este espacio creado al juego.
 *  Por último, cierra el fichero cuando ha terminado todo esto.
 *
 * @param game puntero no nulo tipo Game
 * @param filename cadena de caracteres que nos indica como se llama el archivo del que tiene que cargar los espacios
 * @return devuelve OK si los espacios se han cargado correctamente. Devuelve ERROR si no se han cargado correctamente
 *
 */

STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;

  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;

  if (!filename)
    return ERROR;

  file = fopen(filename, "r");

  if (file == NULL)
    return ERROR;

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


#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s\n", id, name, north, east, south, west, picture);
#endif
      space = space_create(id);

      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file))
    status = ERROR;


  fclose(file);

  return status;
}


/**
 * @brief carga los objetos en el juego
 *  Esta funcion carga los objetos en el espacio que nosotros le ponemos. En este caso el espacio para los objetos
 *  será para todos el mismo, 0. Así lo hemos puesto en el fichero objects.dat.
 *
 * @param game puntero no nulo tipo Game
 * @param filename cadena de caracteres que nos indica como se llama el archivo del que tiene que cargar los espacios
 * @return devuelve OK si los objetos se han cargado correctamente. Devuelve ERROR si no se han cargado correctamente
 *
 */

STATUS game_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  char caracter;

  Id object_id = NO_ID;
  Id space_id = NO_ID;
  Object* object = NULL;
  Space *space = NULL;
  STATUS status = OK;

  if (!filename)
    return ERROR;

  file = fopen(filename, "r");
  if (file == NULL)

    return ERROR;

  while (fgets(line, WORD_SIZE, file)) {

    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      object_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      caracter = atol(toks);
      toks = strtok(NULL, "|");
      space_id = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%s|%ld\n", object_id, name,caracter, space_id);
#endif
      object = object_create(object_id, "objeto");

      if (object != NULL) {
        fprintf(stdout, "%ld id del esapcio\n", space_id);
        space = game_get_space(game, space_id);
        if (!space)
          fprintf(stdout, "error en el espacio\n" );
        object_set_name(object, name);
        if (game_add_object(game, object) == ERROR)
          fprintf(stdout, "error en game_add_object\n" );
        if (space_add_object(space, object_id) == ERROR)
          fprintf(stdout, "error en space_add_object\n" );
        /*if (game_set_object_location(game, space_id, object_id == ERROR))
          //fprintf(stdout, "error en game_set_object_location\n" );*/
        space = NULL;
      }
    }
  }

  if (ferror(file))
    status = ERROR;


  fclose(file);

  return status;
}
