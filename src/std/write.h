//
//
//    write.h
//    Created by C0DIC, 13/03/2023
//
//    Standart library method to write into stdout
//    
//    write 123

#ifndef CATA_WRITE_H
#define CATA_WRITE_H

#include "../token.h"

void cata_write(Token arg, CataVar *variables);

#endif

#ifdef CATA_WRITE

void cata_write(Token arg, CataVar *variables) {
    
    if (arg.token_type == TOKEN_TYPE_STRING) {
        fprintf(stdout, "%.*s\n", (int)arg.token_value.length, 
                         CS_FMT(arg.token_value)
        );
    } else if (arg.token_type == TOKEN_TYPE_INT) {
        fprintf(stdout, "%lld\n", castr_to_lld(arg.token_value));
    } else if (arg.token_type == TOKEN_TYPE_FLOAT) {
        fprintf(stdout, "%lf\n", atof(arg.token_value.data));
    } else if (arg.token_type == TOKEN_TYPE_NAME) {
        size_t pos = 0;

        while (pos < BUFSIZ) {
            if (castr_same(variables[pos].name, arg.token_value)) {
                switch (variables[pos].type) {
                    case STRING_CATA:
                        fprintf(stdout, "%.*s\n", 
                            (int)variables[pos].value.as_string.length,
                            CS_FMT(variables[pos].value.as_string));
                        break;
                    case FLOAT_CATA:
                        fprintf(stdout, "%lf\n", 
                            variables[pos].value.as_float);
                        break;
                    case INT_CATA:
                        fprintf(stdout, "%ld\n", 
                            variables[pos].value.as_int);
                        break;
                    default:
                        break;
                    }

                break;
            }
            pos += 1;
        }

        if (pos == BUFSIZ) {
            fprintf(stderr, "ERROR: no variable named `%.*s`\n",
                        (int)arg.token_value.length, 
                         CS_FMT(arg.token_value));
            exit(1);
        }
    }
};

#endif