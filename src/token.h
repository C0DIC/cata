//
//
//    token.h
//    Created by C0DIC, 10/03/2023
//

#include "catastring/catastring.h"

typedef enum {
    TOKEN_TYPE_EOF,
    TOKEN_TYPE_INT,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_NAME,
    TOKEN_TYPE_FUNC,
    TOKEN_TYPE_PLUS,
    TOKEN_TYPE_MINUS,
    TOKEN_TYPE_COLON,
    TOKEN_TYPE_WRITE,
    TOKEN_TYPE_QUOTE,
    TOKEN_TYPE_LOOP,
    TOKEN_TYPE_AS,
    TOKEN_TYPE_END,
    TOKEN_TYPE_LEFT_BRACKET,
    TOKEN_TYPE_RIGHT_BRACKET,
    TOKEN_TYPE_ITERATOR,
    TOKEN_TYPE_COMMENT,
} TokenType;

typedef struct {
    CataStr token_value;
    unsigned int token_type;
} Token;


Token createToken(CataStr word, unsigned int token_type);