/** 
 * @brief Implementa las funciones para el manejo de jugadores
 * 
 * @file player.c
 * @author Victoria Pelayo e Ignacio Rabuñal
 * @version 1.0 
 * @date 29/09/2017
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"


struct _Player{
	Id id; /*!< identificador */
	char name[WORD_SIZE +1]; /*!< nombre */
	Id id_space; /*!< Id de la casilla en la que se encuentra */
	Id id_object; /*!< id del objeto que porta */
};


Player* player_create(Id id, char* name){

	Player *newplayer = NULL;

	if (id == NO_ID || name == NULL || strlen(name) >= WORD_SIZE ) 	return NULL;

	newplayer = (Player*)malloc(sizeof(Player));

	strcpy(newplayer->name, name);
	newplayer-> id = id;
	newplayer-> id_space = NO_ID;
	newplayer-> id_object = NO_ID;
	
	return newplayer;
}


void player_destroy(Player* player){
	if (!player) return;	

	free (player);
	player = NULL;
}


Id player_get_id(Player* player){
	if (player-> id == NO_ID || player == NULL) return NO_ID;
	
	return player-> id;
}


Id player_get_object(Player* player){
	if (player-> id_object == NO_ID || player == NULL) return NO_ID;
	
	return player->id_object;
}


Id player_get_location(Player* player){
	if (player->id_space == NO_ID || player == NULL) return NO_ID;
	
	return player-> id_space;
}


char* player_get_name(Player* player){
	if (!player) return NULL;
	
	return player->name;
}


STATUS player_set_name(Player* player, char* name){
	if (!player || !name || strlen(name) > WORD_SIZE ) return ERROR;

	if (!strcpy(player->name, name)) {
        return ERROR;
    }

    return OK;
}


STATUS player_set_id(Player* player, Id id){
	if (!player || id == NO_ID) return ERROR;

	player-> id = id;
	return OK;
}


STATUS player_set_object(Player* player, Id id_object){
	if (!player ) return ERROR;

	player-> id_object = id_object;
	return OK;
}


STATUS player_set_location(Player* player, Id id_space){
	if (!player ) return ERROR;

	player-> id_space = id_space;
	return OK;
}


STATUS player_print(Player *player){

	if (player == NULL) return ERROR;

	
	else{
	if (player->id_space == NO_ID) fprintf(stdout, "El jugador no tiene espacio");
		else fprintf(stdout, "El id del espacio donde esta el jugador es: %ld", player->id_space);
	
	
	if(player->id_object == NO_ID) fprintf(stdout, "El jugador no tiene objeto");
	else fprintf(stdout, "El id del objeto  del jugador es: %ld", player->id_object);

	fprintf(stdout, "El nombre del jugador es: %s.\n", player->name);
	fprintf(stdout, "El id del jugador es: %ld.\n", player->id);
	}
	return OK;
	
}

