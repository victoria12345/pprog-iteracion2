/**
* @brief Implementa el interpretador de comandos.
*
* @file command.c
* @author Victoria Pelayo e Ignacio Rabuñal.
* @version 1.1
* @date 03-10-2017
* @copyright GNU Public License
*/

#include <stdio.h>
#include <string.h>
#include "command.h"

/** */
#define CMD_LENGHT 30
#define N_CMD 9

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Quit", "Next", "Back", "Pick", "Drop","Jump","Roll"};



T_Command get_user_input(){
  T_Command cmd = NO_CMD;
  char input[CMD_LENGHT] = "";

  if (scanf("%s", input) > 0){
    if (!strcmp(input, "q") || !strcmp(input, "quit")){
      cmd = QUIT;
    }
    else if (!strcmp(input, "n") || !strcmp(input, "next")){
      cmd = NEXT;
    }else if (!strcmp(input, "b") || !strcmp(input, "back")){
      cmd = BACK;
    }else if (!strcmp(input, "p") || !strcmp(input, "pick")){
      cmd = PICK;
    }else if (!strcmp(input, "d") || !strcmp(input, "drop")){
      cmd = DROP;
    }else if (!strcmp(input, "j") || !strcmp(input, "jump")){
      cmd = JUMP;
    }else if (!strcmp(input, "r") || !strcmp(input, "roll")){
      cmd = ROLL;
	}else{cmd = UNKNOWN;
    }
  }
  return cmd;
}
