/**
 * @brief Funcionalidad para el manejo de dados.
 *
 * @file die.h
 * @author Ignacio Rabunnal
 * @version 1.0
 * @date 11/10/2017
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H
#include "types.h"

typedef struct _Die Die;

/**
*@brief crea un dado con un id dado.
*@param id entero mayor o igual que 0.
*@return puntero al dado creado.
*/
Die* die_create(Id id);

/**
*@brief destruye un dado.
*@param dice puntero al dado que queremos destruír.
*/
void die_destroy(Die *die);

/**
*@brief tira el dado, generando un numero aleatorio entre 1 y 6.
*@param dice puntero al dado que queremos tirar.
*@param semilla semilla para crear los numeros aleatorios.
*@return OK si el dado se lanza correctamente y ERROR si algo falla durante el proceso.
*/
STATUS die_roll(Die *die, int semilla);

/**
*@brief imprime la información del dado por pantalla.
*@param dice puntero al dado que queremos imprimir.
*@return OK si el dado se imprime correctamente y ERROR si algo falla durante el proceso.
*/
STATUS die_print(Die *die);

#endif
