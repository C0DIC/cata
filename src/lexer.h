//
//
//    lexer.h
//    Created by C0DIC, 10/03/2023
//

#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "catastring/catastring.h"

void lexer(char *program, Token *tokenArray, size_t *tokens_count);

char *readFile(FILE *source_file);