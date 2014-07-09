/**Creates a struct used to stores a word, its hints and its dificulty.
/*
 * @autor Douglas
 * @autor Isabella
 * @autor Thiago
 * @autor Tiago
 * @since 04/07/2014
 * @version 2.0
 * 
 * 
*/

#ifndef WORDANDHINTS_HPP
#define WORDANDHINTS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wordAndHintsStruct { /** <Struct used to stores a word, its hints and its dificulty.*/
    /*@reldef@*/ char *word;
    /*@reldef@*/ char *hints[3];
    /*@reldef@*/ char dificulty;
} wordAndHints;

#endif /**<WORDANDHINTS_HPP.*/
