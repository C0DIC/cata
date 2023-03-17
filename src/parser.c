#include <stdio.h>
#include "token.h"
#include "parser.h"

void parser(Token *tokenized, size_t tokens_count) {
    for(size_t i = 0; i < tokens_count; ++i) {
        if (tokenized[i].token_type == TOKEN_TYPE_FUNC) {
            cata_parse_fn(tokenized, tokens_count, &i);
        }

        if (tokenized[i].token_type == TOKEN_TYPE_WRITE) {
            cata_parse_write(tokenized, tokens_count, &i);
        }

        if (tokenized[i].token_type == TOKEN_TYPE_LOOP) {
            cata_parse_loop(tokenized, tokens_count, &i);
        }
    }
}

 void cata_parse_fn(Token *tokenized, size_t tokens_count, size_t *pos) {
    size_t i = *pos;
    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_NAME) {
        fprintf(stderr, "ERROR: excepted name after function declaration\n");
        exit(1);
    } else {
        // TODO
    }

    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_COLON) {
        fprintf(stderr, "ERROR: excepted `:` after function name\n");
        exit(1);
    }

    while (i < tokens_count) {
        if (tokenized[i].token_type == TOKEN_TYPE_END && 
            tokenized[i].marked_end == false) {
                tokenized[i].marked_end = true;
                break;
        }
        i += 1;
    }

    if (i == tokens_count) {
        fprintf(stderr, "ERROR: function block never closed\n");
        exit(1);
    }
}

void cata_parse_write(Token *tokenized, size_t tokens_count, size_t *pos) {
    size_t i = *pos;
    i += 1;

    if (tokenized[i].token_type != TOKEN_TYPE_INT &&    
        tokenized[i].token_type != TOKEN_TYPE_STRING
    ) {
        fprintf(stderr, "ERROR: excepted int or string after `write`\n");
        exit(1);
    } else {
        cata_write(tokenized[i]);
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

        while (i < tokens_count) {
            if (tokenized[i].token_type == TOKEN_TYPE_END && 
                tokenized[i].marked_end == false) {
                    tokenized[i].marked_end = true;
                    _loop_block_end = i;
                    *pos = i;
                    break;
            }
            i++;
        }

        if (i == tokens_count) {
            fprintf(stderr, "ERROR: loop block never closed\n");
            exit(1);
        }
    } else {
        if (tokenized[i+1].token_type != TOKEN_TYPE_NAME) {
            fprintf(stderr, "ERROR: excepted name after `as`\n");
            exit(1);
        }

        _loop_block_start = i;
        
        while (i < tokens_count) {
            if (tokenized[i].token_type == TOKEN_TYPE_END && 
                tokenized[i].marked_end == false) {
                    tokenized[i].marked_end = true;
                    _loop_block_end = i;
                    *pos = i;
                    break;
            }
            i++;
        }

        if (i == tokens_count) {
            fprintf(stderr, "ERROR: loop block never closed\n");
            exit(1);
        }
    }

    cata_loop(tokenized, _loop_starter, _loop_end, _loop_block_start, _loop_block_end);
}

void cata_parse_loop_block(Token *tokenized, size_t block_start, size_t block_end) {
    for(; block_start < block_end; ++block_start) {
        if (tokenized[block_start].token_type == TOKEN_TYPE_FUNC) {
            cata_parse_fn(tokenized, block_end, &block_start);
        }

        if (tokenized[block_start].token_type == TOKEN_TYPE_WRITE) {
            cata_parse_write(tokenized, block_end, &block_start);
        }

        if (tokenized[block_start].token_type == TOKEN_TYPE_LOOP) {
            cata_parse_loop(tokenized, block_end, &block_start);
        }
    }
}
