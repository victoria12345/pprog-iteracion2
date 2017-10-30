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


/** */
typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  QUIT,
  NEXT,
  BACK,
  PICK,
  DROP,
  JUMP,
  ROLL} T_Command;

  /*
  * @brief interpreta el comando
  * @return cmd el comando leído
  */
  T_Command get_user_input();

  #endif
