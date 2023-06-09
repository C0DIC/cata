//
//
//    parser.h
//    Created by C0DIC, 18/03/2023
//


#ifndef CATA_PARSER_H
#define CATA_PARSER_H

#include <stdlib.h>
#include <stdio.h>

#include "catavar.h"

#include "std/write.h"
#include "std/loop.h"
#include "std/conditions.h"

#include "token.h"

void parser(Token *tokenized, size_t start_pos, size_t tokens_count);

void cata_parse_expr(Token *tokenized, size_t start_pos, size_t tokens_count);

void cata_parse_fn(Token *tokenized, size_t tokens_count, size_t *pos);

void cata_parse_write(Token *tokenized, size_t tokens_count, size_t *pos);

void cata_parse_variables(Token *tokenized, size_t tokens_count, size_t *pos);

void cata_parse_loop(Token *tokenized, size_t tokens_count, size_t *pos);

void cata_parse_condition(Token *tokenized, size_t tokens_count, size_t *pos);

#endif

#ifdef CATA_PARSER

CataVar CATA_VARIABLES[BUFSIZ] = {0};

void parser(Token *tokenized, size_t start_pos, size_t tokens_count) {
    CATA_VARIABLES[0] = (CataVar) {.name = CS("CATA_BUF_SIZE"), .type = INT_CATA, .value.as_int = BUFSIZ};

    for(; start_pos < tokens_count; ++start_pos) {

        /*if (tokenized[start_pos].token_type == TOKEN_TYPE_FUNC) {
            cata_parse_fn(tokenized, tokens_count, &start_pos);
        }*/

        if (tokenized[start_pos].token_type == TOKEN_TYPE_WRITE) {
            cata_parse_write(tokenized, tokens_count, &start_pos);
        }

        if (tokenized[start_pos].token_type == TOKEN_TYPE_LOOP) {
            cata_parse_loop(tokenized, tokens_count, &start_pos);
        }

        if (tokenized[start_pos].token_type == TOKEN_TYPE_VAR) {
            cata_parse_variables(tokenized, tokens_count, &start_pos);
        }

        if (tokenized[start_pos].token_type == TOKEN_TYPE_IF) {
            cata_parse_condition(tokenized, tokens_count, &start_pos);
        }
    }
}

void cata_parse_write(Token *tokenized, size_t tokens_count, size_t *pos) {
    size_t i = *pos;
    i += 1;

    if (tokenized[i].token_type != TOKEN_TYPE_INT &&
        tokenized[i].token_type != TOKEN_TYPE_STRING &&
        tokenized[i].token_type != TOKEN_TYPE_FLOAT &&
        tokenized[i].token_type != TOKEN_TYPE_NAME
    ) {
        fprintf(stderr, "ERROR: `%.*s` is not writable\n",
            (int)tokenized[i].token_value.length,
            CS_FMT(tokenized[i].token_value)
        );
        exit(1);
    } else {
        cata_write(tokenized[i], CATA_VARIABLES);
    }
}

void cata_parse_loop(Token *tokenized, size_t tokens_count, size_t *pos) {
    size_t i = *pos;

    long long int _loop_starter = 0, _loop_end = 0;
    size_t _loop_block_start = 0, _loop_block_end = 0;


    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_INT) {
        fprintf(stderr, "ERROR: excepted int as the start of the loop iteration\n");
        exit(1);
    } else {
        _loop_starter = castr_to_lld(tokenized[i].token_value);
    }
    
    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_ITERATOR) {
        fprintf(stderr, "ERROR: excepted iterator `..` after int\n");
        exit(1);
    }

    i+=1;
    if (tokenized[i].token_type != TOKEN_TYPE_INT) {
        fprintf(stderr, "ERROR: excepted int as the end of the loop iteration\n");
        exit(1);
    } else {
        _loop_end = castr_to_lld(tokenized[i].token_value);
    }

    i+=1;
    if (tokenized[i].token_type != TOKEN_TYPE_AS && tokenized[i+1].token_type != TOKEN_TYPE_NAME) {
        _loop_block_start = i;

        while (i <= tokens_count) {
            if (tokenized[i].token_type == TOKEN_TYPE_END && 
                tokenized[i].marked_end == false) {
                    tokenized[i].marked_end = true;
                    _loop_block_end = i;
                    *pos = i + 1;
                    break;
            }
            i++;
        }

        if (i >= tokens_count) {
            fprintf(stderr, "ERROR: loop block never closed\n");
            exit(1);
        }
    } else {
        if (tokenized[i+1].token_type != TOKEN_TYPE_NAME) {
            fprintf(stderr, "ERROR: excepted name after `as`\n");
            exit(1);
        }

        _loop_block_start = i;
        
        while (i <= tokens_count) {
            if (tokenized[i].token_type == TOKEN_TYPE_END && 
                tokenized[i].marked_end == false) {
                    tokenized[i].marked_end = true;
                    _loop_block_end = i;
                    *pos = i + 1;
                    break;
            }
            i++;
        }

        if (i >= tokens_count) {
            fprintf(stderr, "ERROR: loop block never closed\n");
            exit(1);
        }
    }

    cata_loop(tokenized, _loop_starter, _loop_end, _loop_block_start, _loop_block_end);
}

void cata_parse_variables(Token *tokenized, size_t tokens_count, size_t *pos) {
    size_t i = *pos;

    i +=1;
    if(tokenized[i].token_type != TOKEN_TYPE_NAME) {
        fprintf(stderr, "ERROR: excepted variable name after `var`\n");
        exit(1);
    }

    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_COLON) {
        fprintf(stderr, "ERROR: excepted `:` after variable name\n");
        exit(1);
    }

    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_INT_TYPE &&
        tokenized[i].token_type != TOKEN_TYPE_FLOAT_TYPE &&
        tokenized[i].token_type != TOKEN_TYPE_STRING_TYPE
        ) {
        fprintf(stderr, "ERROR: excepted variable type after name, but got `%.*s`\n",
                    (int)tokenized[i].token_value.length,
                    CS_FMT(tokenized[i].token_value)
        );
        exit(1);
    } else {
        if (tokenized[i+1].token_type == TOKEN_TYPE_EQUAL) {
            if (tokenized[i+2].token_type != TOKEN_TYPE_INT &&
                tokenized[i+2].token_type != TOKEN_TYPE_STRING &&
                tokenized[i+2].token_type != TOKEN_TYPE_FLOAT
            ) {
                fprintf(stderr, "ERROR: excepted value after `=`, but got `%.*s`\n",
                    (int)tokenized[i+2].token_value.length,
                    CS_FMT(tokenized[i+2].token_value)
                );
                exit(1);
            } else {
                if (tokenized[i].token_type == TOKEN_TYPE_INT_TYPE
                    && tokenized[i+2].token_type != TOKEN_TYPE_INT
                ) {
                    fprintf(stderr, "ERROR: type error. Excepted int, but got `%.*s`\n",
                        (int)tokenized[i+2].token_value.length,
                        CS_FMT(tokenized[i+2].token_value)
                    );
                    exit(1);
                }

                if (tokenized[i].token_type == TOKEN_TYPE_FLOAT_TYPE
                    && tokenized[i+2].token_type != TOKEN_TYPE_FLOAT
                ) {
                    fprintf(stderr, "ERROR: type error. Excepted float, but got `%.*s`\n",
                        (int)tokenized[i+2].token_value.length,
                        CS_FMT(tokenized[i+2].token_value)
                    );
                    exit(1);
                }

                if (tokenized[i].token_type == TOKEN_TYPE_STRING_TYPE
                    && tokenized[i+2].token_type != TOKEN_TYPE_STRING
                ) {
                    fprintf(stderr, "ERROR: type error. Excepted string, but got `%.*s`\n",
                        (int)tokenized[i+2].token_value.length,
                        CS_FMT(tokenized[i+2].token_value)
                    );
                    exit(1);
                }

                CataVar variable = createCataVariable(tokenized[i-2].token_value, tokenized[i+2].token_value, tokenized[i].token_type);
                catavar_array_push(CATA_VARIABLES, variable);
            }
        } else {
            CataVar variable = createCataVariable(tokenized[i-2].token_value, CS(" "), tokenized[i].token_type);
            catavar_array_push(CATA_VARIABLES, variable);
        }
    }
}

void cata_parse_condition(Token *tokenized, size_t tokens_count, size_t *pos) {
    size_t i = *pos;
    CataVar condition;

    i += 1;
    if (tokenized[i].token_type == TOKEN_TYPE_INT) {
        condition.type = INT_CATA;
        condition.value.as_int = castr_to_lld(tokenized[i].token_value);
    } else if (tokenized[i].token_type == TOKEN_TYPE_NAME) {
        size_t pos = 0;

        while (pos < BUFSIZ) {
            if (castr_same(CATA_VARIABLES[pos].name, tokenized[i].token_value)) {
                if (CATA_VARIABLES[pos].type == INT_CATA) {
                    condition.value.as_int = CATA_VARIABLES[pos].value.as_int;
                } else {
                    fprintf(stderr, "ERROR: `%.*s` type is not arithemtic\n",
                        (int)CATA_VARIABLES[pos].name.length,
                        CS_FMT(CATA_VARIABLES[pos].name)
                    );
                    exit(1);
                }

                break;
            }
            pos += 1;
        }

        if (pos == BUFSIZ) {
            fprintf(stderr, "ERROR: no variable named `%.*s`\n",
                        (int)tokenized[i].token_value.length, 
                         CS_FMT(tokenized[i].token_value));
            exit(1);
        }
        
        condition.name = tokenized[i].token_value;
        condition.type = INT_CATA;
    } else {
        fprintf(stderr, "ERROR: the expression must have an arithmetic type, but found `%.*s`\n",
                    (int)tokenized[i].token_value.length,
                    CS_FMT(tokenized[i].token_value)
        );
        exit(1);
    }

    while (i <= tokens_count) {
        if (tokenized[i].token_type == TOKEN_TYPE_END && 
            tokenized[i].marked_end == false) {            
                tokenized[i].marked_end = true;
                size_t end_pos = i;
                if_condition(condition, end_pos, pos);
                break;
        }
        i++;
    }

    if (i >= tokens_count) {
        fprintf(stderr, "ERROR: loop block never closed\n");
        exit(1);
    }
}

#endif