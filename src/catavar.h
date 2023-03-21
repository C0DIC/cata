//
//
//    catavar.h
//    Created by C0DIC, 19/03/2023
//
//
//    Header where cata variable structure implemented

#ifndef CATA_VAR_H
#define CATA_VAT_H

#include <stdio.h>
#include <stdint.h>
#include "catastring/catastring.h"
#include "token.h"

typedef enum {
    INT_CATA = 1,
    FLOAT_CATA,
    STRING_CATA,
    EMPTY_CATA
} CataTypes;


typedef union {
    int64_t as_int;
    double as_float;
    CataStr as_string;
} CataValue;

typedef struct CataVariable {
    CataStr    name;
    CataValue  value;
    __u_short  type;
} CataVar;

CataVar createCataVariable(CataStr name, CataStr value, __u_short type);
void catavar_array_push(CataVar *variables, CataVar variable);

#endif /* CATA_VAR */

#ifdef CATA_VAR

CataVar createCataVariable(CataStr name, CataStr value, __u_short type) {
    switch (type) {
        case TOKEN_TYPE_INT_TYPE:
            return (CataVar) {.type = INT_CATA, .value.as_int = castr_to_lld(value), .name = name};
            break;
        case TOKEN_TYPE_FLOAT_TYPE:
            return (CataVar) {.type = FLOAT_CATA, .value.as_float = atof(value.data), .name = name};
            break;
        case TOKEN_TYPE_STRING_TYPE:
            return (CataVar) {.type = STRING_CATA, .value.as_string = value, .name = name};
            break;
        default:
            fprintf(stderr, "ERROR: unknown type\n");
            exit(1);
    }
}

void catavar_array_push(CataVar *variables, CataVar variable) {
    size_t pos = 0;

    while (variables[pos].name.length != 0) {
        if (castr_same(variables[pos].name, variable.name)) {
            fprintf(stderr, "ERROR: reassigning of variable `%.*s`. Already exists\n",
                (int)variables[pos].name.length,
                CS_FMT(variables[pos].name)
            );
            exit(1);
        }
        pos += 1;
    }
    variables[pos] = variable;

    pos = 0;
    while (variables[pos].name.length != 0) {
        
        pos += 1;
    }
}

#endif