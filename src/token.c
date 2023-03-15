#include "token.h"

Token createToken(CataStr word, unsigned int token_type) {
    return (Token) {
        .token_value = word,
        .token_type  = token_type
    };
}