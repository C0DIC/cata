//
//
//    loop.h
//    Created by C0DIC, 18/03/2023
//
//    Standart library method to make looping
//    
//    loop 1..15 as i
//        write i
//    end

#ifndef CATA_LOOP_H
#define CATA_LOOP_H

#include "../token.h"

void cata_loop(Token *tokenized, long long int _start, long long int _end,
                size_t _block_start, size_t _block_end);

#endif

#ifdef CATA_LOOP

void cata_loop(Token *tokenized, long long int _start, long long int _end, 
               size_t _block_start, size_t _block_end) {

    if (_start >= _end) {
        for (; _start > _end ; --_start) {
            parser(tokenized, _block_start, _block_end);
        }
    } else if (_start <= _end) {
        for (; _start < _end ; ++_start) {
            parser(tokenized, _block_start, _block_end);
        }
    }
}

#endif