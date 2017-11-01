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
#include <stdlib.h>
#include <string.h>
#include "command.h"

/** */
#define CMD_LENGHT 30
#define N_CMD 10

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Quit", "Next", "Back", "Pick", "Drop","Left", "Right","Roll"};

struct _Command{
  T_Command cmd;
  char action[WORD_SIZE];
  char object[WORD_SIZE];
  char status[7];
};

Command* get_user_input(){
  Command* command = NULL;
  char action[WORD_SIZE] = " ";
  char object[WORD_SIZE] = " ";

  command = command_create();

/**  gets(input);*/

  if (scanf("%s", action) > 0){

  /**  action = strtok(input, " ");*/

    if (!strcmp(action, "q") || !strcmp(action, "quit")){
      command->cmd = QUIT;

    }else if (!strcmp(action, "n") || !strcmp(action, "next")){
      command->cmd = NEXT;

    }else if (!strcmp(action, "b") || !strcmp(action, "back")){
      command->cmd = BACK;

    }else if (!strcmp(action, "p") || !strcmp(action, "pick")){

      command->cmd = PICK;

    /**  object = strtok(input, " ");*/
      if(scanf("%s", object) > 0)
        strcpy(command->object, object);

    }else if (!strcmp(action, "d") || !strcmp(action, "drop")){
      command->cmd = DROP;

    }else if (!strcmp(action, "l") || !strcmp(action, "left")){
      command->cmd = LEFT;

    }else if (!strcmp(action, "r") || !strcmp(action, "right")){
      command->cmd = RIGHT;

    }else if (!strcmp(action, "roll") || !strcmp(action, "ROLL")){
      command->cmd = ROLL;

    }else{
      command->cmd = UNKNOWN;
    }

  }

  return command;
}

Command* command_create(){
  Command* newCommand;

  newCommand = (Command*)malloc(sizeof(newCommand[0]));

  newCommand->cmd = NO_CMD;

  strcpy(newCommand->action, " ");
  strcpy(newCommand->status, " ");
  strcpy(newCommand->object, " ");

  return newCommand;
}

void command_destroy(Command* command){
  if (!command) return;

  free(command);
}

T_Command command_get_action(Command* command){
  if(!command) return NO_CMD;

  return command->cmd;
}

char* command_get_object(Command* command){
  if(!command) return NULL;

  return command->object;
}

STATUS command_set_object(Command* command, char* object){
  if(!command || !object) return ERROR;

  strcpy(command->object, object);
  return OK;
}

STATUS command_set_action(Command* command, T_Command action){
  if(!command || action == NO_CMD) return ERROR;

  command->cmd = action;
  return OK;
}

char* command_get_name(Command* command){

  return command->action;
}

STATUS command_set_name(Command* command, char* name){
  if(!command || !name) return ERROR;

  strcpy(command->action,name);
  return OK;
}

char* command_get_status(Command* command){
  if (!command) return "ERROR";

  return command->status;
}

STATUS command_set_status(Command* command, char* status){
  if(!command || !status) return ERROR;

  if(strcmp(status, "OK") != 0 && strcmp(status, "ERROR") != 0) return ERROR;

  strcpy(command->status, status);
  return OK;
}
