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

#define N_CMD 9




char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Quit", "Next", "Back", "Pick", "Drop","Left", "Right"};



Command get_user_input(){
  int i, j;
  Command cmd;
  char input_cmd[CMD_LENGHT] = "";
  char input_obj[CMD_LENGHT] = "";
  char total_input[CMD_LENGHT]="";

  if(scanf("%s", total_input) > 0){
    for(i = 0; i < 4 ; i++){
      input_cmd[i] = total_input[i];
    }

    if(total_input[5] != '\0'){
      for(i = 5, j = 0; i != '\0'; i++, j++){
        input_obj[j] = total_input[i];
      }
    }
  }



  if (!strcmp(input_cmd, "q") || !strcmp(input_cmd, "quit")){
    cmd.command = QUIT;
  }
  else if (!strcmp(input_cmd, "n") || !strcmp(input_cmd, "next")){
    cmd.command = NEXT;
  }else if (!strcmp(input_cmd, "b") || !strcmp(input_cmd, "back")){
    cmd.command = BACK;
  }else if (!strcmp(input_cmd, "p") || !strcmp(input_cmd, "pick")){
    cmd.command = PICK;

    if(!strcmp(input_obj, "*")){
      strcpy(cmd.obj, "*");
    }else if(!strcmp(input_obj, "^_^")){
      strcpy(cmd.obj, "^_^");
    }else if(!strcmp(input_obj, "._.")){
      strcpy(cmd.obj, "._.");
    }else if(!strcmp(input_obj, "%%")){
      strcpy(cmd.obj, "%%");
    }
  }else if (!strcmp(input_cmd, "d") || !strcmp(input_cmd, "drop")){
    cmd.command = DROP;
  }else if (!strcmp(input_cmd, "l") || !strcmp(input_cmd, "left")){
    cmd.command = LEFT;

  }else if (!strcmp(input_cmd, "r") || !strcmp(input_cmd, "rigt")){
      cmd.command = RIGT;
  }else{
    cmd.command = UNKNOWN;
  }

  return cmd;
}
