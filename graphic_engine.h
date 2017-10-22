/** 
 * @brief Funciones para el manejo del motor gráfico.
 * 
 * @file graphic_engine.h
 * @author Victoria Pelayo e Ignacio Rabuñal
 * @version 1.0 
 * @date 18-01-2017
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

/**
*@brief motor gráfico
*Esta estructura define un motor gráfico que cuenta con 5 areas de pantalla con usos diferentes. 
*/
typedef struct _Graphic_engine Graphic_engine;

/**
*@brief crea un motor gráfico.
*@return puntero al motor gráfico creado.
*/
Graphic_engine* graphic_engine_create();

/**
*@brief destruye un motor gráfico.
*@param ge motor gráfico que queremos destruir.
*/
void graphic_engine_destroy(Graphic_engine *ge);

/**
*@brief rellena las areas con los caracteres necesarios para el juego.
*@param ge motor gráfico que vamos a usar.
*@param game juego específico que queremos cargar en la pantalla.
*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
