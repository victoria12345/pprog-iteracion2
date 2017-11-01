/**
* @brief Implementa el interpretador de comandos
*
* @file command.h
* @author Victoria Pelayo e Ignacio Rabuñal.
* @version 1.0
* @date 19-12-2014
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

  typedef struct _Command Command;

  /*
  * @brief interpreta el comando
  * @return cmd el comando leído
  */
  Command* get_user_input();

  Command* command_create();
  void command_destroy(Command* command);
  T_Command command_get_action(Command* command);
  char* command_get_object(Command* command);
  STATUS command_set_object(Command* command, char* object);
  STATUS command_set_action(Command* command, T_Command action);
  char* command_get_name(Command* command);
  STATUS command_set_name(Command* command, char* name);
  char* command_get_status(Command* command);
  STATUS command_set_status(Command* command, char* status);

  #endif
