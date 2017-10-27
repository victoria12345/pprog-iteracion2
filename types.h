/**
 * @brief Define tipos comunes.
 *
 * @file types.h
 * @author Victoria Pelayo e Ignacio Rabuñal.
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

/** */
#ifndef TYPES_H
#define TYPES_H

/** */
#define WORD_SIZE 100
#define NO_ID -1

/**
*@brief Id
*Id es un numero de tipo long
*/
typedef long Id;

/**
* @brief tipo bool
* Enumeración de un tipo de dato que puede ser FALSE o TRUE
*/
typedef enum {
  FALSE, TRUE
} BOOL;

/**
* @brief tipo STATUS
*enumeracion para definir el tipo status que puede ser ERROR o OK
*/
typedef enum {
    ERROR, OK
} STATUS;

/***
*@BRIEF tipo DIRECTION
* enumeracion para definir el tipo DIRECTION que puede ser N,S,W o E
*/
typedef enum {
    N, S, E, W
} DIRECTION;

#endif
