//
//
//    token.h
//    Created by C0DIC, 10/03/2023
//

#ifndef CATA_TOKEN_H
#define CATA_TOKEN_H

#include "catastring/catastring.h"

typedef enum {
    TOKEN_TYPE_EOF,
    TOKEN_TYPE_INT,
    TOKEN_TYPE_FLOAT,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_NAME,
    TOKEN_TYPE_FUNC,
    TOKEN_TYPE_PLUS,
    TOKEN_TYPE_MINUS,
    TOKEN_TYPE_VAR,
    TOKEN_TYPE_COLON,
    TOKEN_TYPE_DOT,
    TOKEN_TYPE_WRITE,
    TOKEN_TYPE_QUOTE,
    TOKEN_TYPE_LOOP,
    TOKEN_TYPE_IF,
    TOKEN_TYPE_ELSE,
    TOKEN_TYPE_AS,
    TOKEN_TYPE_END,
    TOKEN_TYPE_EQUAL,
    TOKEN_TYPE_INT_TYPE,
    TOKEN_TYPE_FLOAT_TYPE,
    TOKEN_TYPE_STRING_TYPE,
    TOKEN_TYPE_LEFT_BRACKET,
    TOKEN_TYPE_RIGHT_BRACKET,
    TOKEN_TYPE_ITERATOR,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_RETURN,
} TokenType;

typedef struct {
    CataStr token_value;
    unsigned int token_type;

    bool marked_end;
} Token;


bool checkToken(CataStr word);
Token createToken(CataStr word, unsigned int token_type);

#endif