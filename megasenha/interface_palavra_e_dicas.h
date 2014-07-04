#ifndef WORDANDHINTS_HPP
#define WORDANDHINTS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct wordAndHintsStruct {
    char *word;
    char *hints[3];
    char dificulty;
} wordAndHints;

#endif // WORDANDHINTS_HPP
