//
//
//    write.c
//    Created by C0DIC, 13/03/2023
//
//    Standart library method to write into stdout
//    
//    write 123

#include "../token.h"
#include "write.h"
#include <stdio.h>

void cata_write(Token arg) {
    if (arg.token_type == TOKEN_TYPE_STRING) {
        fprintf(stdout, "%.*s\n", (int)arg.token_value.length, 
                         CS_FMT(arg.token_value)
        );
    } else if (arg.token_type == TOKEN_TYPE_INT) {
        fprintf(stdout, "%lld\n", castr_to_lld(arg.token_value));
    }
};