/**
* @brief Prototipo de  las funciones para la pantalla.
*
* @file screen.h
* @author Victoria Pelayo e Ignacio Rabuñal
* @version 1.0
* @date 11-01-2017
* @copyright GNU Public License
*/

#ifndef __SCREEN__
#define __SCREEN__

/** */
#define SCREEN_MAX_STR 80

/**
*@brief area
*Esta estructura define areas que colocaremos en la pantalla y que usará el motor gráfico para cargar la información del juego.
*/
typedef struct _Area Area;

/**
*@brief crea una pantalla.
*/
void  screen_init();

/**
*@brief destruye una pantalla.
*/
void  screen_destroy();

/**
*@brief vuelca el contenido de la pantalla en la terminal.
*/
void  screen_paint();

/**
*@brief da una pantalla
@param str cadena de caracteres
*/
void  screen_gets(char *str);


/**
*@brief crea un area de pantalla.
*@param x posición del eje x de la pantalla donde se empezará a crear el area.
*@param y posición del eje y de la pantalla donde se empezará a crear el area.
*@param width ancho de la pantalla.
*@param height alto de la pantalla.
*@return puntero al area creada.
*/
Area* screen_area_init(int x, int y, int width, int height);

/**
*@brief destruye un area de pantalla.
*@param area area que queremos destruir
*/
void  screen_area_destroy(Area* area);

/**
*@brief "limpia" un area de pantalla dado llenandolo de caracteres en blanco.
*@param area area que queremos limpiar.
*/
void  screen_area_clear(Area* area);

/**
*@brief lleva el cursor de un area a su posición inicial.
*@param area area cuyo cursor queremos llevar a la posición inicial.
*/
void  screen_area_reset_cursor(Area* area);

/**
*@brief rellena un area con una cadena de caracteres dada.
*@param area area que queremos rellenar.
*@param str cadena de caracteres con la que se rellenará el area.
*/
void  screen_area_puts(Area* area, char *str);

#endif
