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
#define CMD_LENGHT 30

typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  QUIT,
  NEXT,
  BACK,
  PICK,
  DROP,
  LEFT,
  RIGT} T_Command;

struct _Command {
  T_Command command;
  char obj[CMD_LENGHT + 1];

};


typedef struct _Command Command;
/** */


  /*
  * @brief interpreta el comando
  * @return cmd el comando leído
  */
Command get_user_input();

  #endif
