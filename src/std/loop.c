#include "../token.h"
#include "../parser.h"
#include "loop.h"
#include <stdio.h>

void cata_loop(Token *tokenized, long long int _start, long long int _end, 
               size_t _block_start, size_t _block_end) {
    
    if (_start >= _end) {
        for (; _start > _end ; --_start) {
            cata_parse_loop_block(tokenized, _block_start, _block_end);
        }
    } else if (_start <= _end) {
        for (; _start < _end ; ++_start) {
            cata_parse_loop_block(tokenized, _block_start, _block_end);
        }
    }
}