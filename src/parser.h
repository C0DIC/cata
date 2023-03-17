//
//
//    parser.h
//    Created by C0DIC, 18/03/2023
//


#include <stdlib.h>

#include "std/write.h"
#include "std/loop.h"

void parser(Token *tokenized, size_t tokens_count);

void cata_parse_fn(Token *tokenized, size_t tokens_count, size_t *pos);

void cata_parse_write(Token *tokenized, size_t tokens_count, size_t *pos);

void cata_parse_loop(Token *tokenized, size_t tokens_count, size_t *pos);
void cata_parse_loop_block(Token *tokenized, size_t block_start, size_t block_end);