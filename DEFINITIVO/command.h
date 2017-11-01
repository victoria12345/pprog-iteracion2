/**
* @brief Implementa el interpretador de comandos
*
* @file command.h
* @author Victoria Pelayo e Ignacio Rabuñal.
* Se han definido las funciones necesarias debido al cambio de la estructura de
* los comandos
* @version 2.0
* @date 01-11-2017
* @copyright GNU Public License
*/
#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

/** */
typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  QUIT,
  NEXT,
  BACK,
  PICK,
  DROP,
  LEFT,
  RIGHT,
  ROLL} T_Command;

  /** */
  typedef struct _Command Command;

  /*
  * @brief interpreta el comando
  * @return cmd el comando leído
  */
  Command* get_user_input();

  /*
  * @brief crea un comando
  * @return cmd el comando creado
  */
  Command* command_create();

  /*
  * @brief Destruye un comando
  * @param command comando que se quiere destruir
  */
  void command_destroy(Command* command);

  /*
  * @brief Devuelve la accion del comando
  * @param command comando cuya accion se quiere saber
  * @ return T_Command accion del comando
  */
  T_Command command_get_action(Command* command);

  /*
  * @brief Devuelve el nombre del objeto del comando
  * @param comando que contiene el objeto
  * @return se devovlera " " si la accion no es pick, y si no el nombre del objeto
  */
  char* command_get_object(Command* command);

  /*
  * @brief Se cambia el objeto del comando
  * @param command comando cuyo objeto se quiere cambiar
  * @param nombre del objeto que tiene que tener el comando
  *@return OK si se ha realizado correctamente y ERROR si no ha sido asi
  */
  STATUS command_set_object(Command* command, char* object);

  /*
  * @brief Se cambia la accion del comando
  * @param command comando cuya accion se quiere cambiar
  * @param action accion que se quiere que tenga el comando
  *@return OK si se ha realizado correctamente y ERROR si no ha sido asi
  */
  STATUS command_set_action(Command* command, T_Command action);

  /*
  * @brief Devuelve el nombre del objeto de la accion
  * @param comando que contiene el nombre de la accion
  * @return se devovlera el nombre de la accion
  */
  char* command_get_name(Command* command);

  /*
  * @brief Se cambia el nombre de la accion del comando
  * @param command comando cuyo nombre de la accion se quiere cambiar
  * @param nombre de la accion que tiene que tener el comando
  * @return OK si se ha realizado correctamente y ERROR si no ha sido asi
  */
  STATUS command_set_name(Command* command, char* name);

  /*
  * @brief Devuelve el status del comando
  * @param comando que contiene el status
  * @return se devovlera OK si la accion se realiza correctamente, ERROR si no ha sido asi y
  * " " si la accion es UNKNOWN
  */
  char* command_get_status(Command* command);

  /*
  * @brief Se cambia el resultado de la accion del comando
  * @param command comando cuyo status se quiere cambiar
  * @param nombre del status quue se quiere establecer(OK, ERROR," ")
  *@return OK si se ha realizado correctamente y ERROR si no ha sido asi
  */
  STATUS command_set_status(Command* command, char* status);

  #endif
