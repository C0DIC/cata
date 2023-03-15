#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "lexer.h"
#include "catastring/catastring.h"

#include "std/write.h"

#define FUNCTION_NAMES_CAPACITY 2048

static char *argv_next(int *argc, char ***argv) {
    assert(*argc > 0);
    char *arg = **argv;
    *argv += 1;
    *argc -= 1;

    return arg;
}

// Get file extension (should be `.cata`)
static const char *get_cata_ext(const char *file_path) {
    const char *ext = strrchr(file_path, '.');

    if (!ext) return ""; else return ext + 1;
}

// Get only file name, without full_path
static const char *lazy_filename(const char *file_path) {
    const char *slash = strrchr(file_path, '/');

    if (!slash) return file_path; else return slash + 1;
}

// Parser ======================================
static void cata_parse_fn(Token *tokenized, size_t tokens_count, size_t *pos) {
    size_t i = *pos;
    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_NAME) {
        fprintf(stderr, "ERROR: excepted name after function declaration\n");
        exit(1);
    } else {
             
    }

    i += 1;
    if (tokenized[i].token_type != TOKEN_TYPE_COLON) {
        fprintf(stderr, "ERROR: excepted `:` after function name\n");
        exit(1);
    }

    while (tokenized[i].token_type != TOKEN_TYPE_END && i < tokens_count) {        
        i += 1;
    }

    if (i == tokens_count) {
        fprintf(stderr, "ERROR: function block never closed\n");
        exit(1);
    }
}

static void cata_parse_write(Token *tokenized, size_t tokens_count, size_t *pos) {
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

static void parser(Token *tokenized, size_t tokens_count) {
    for(size_t i = 0; i < tokens_count; ++i) {
        if (tokenized[i].token_type == TOKEN_TYPE_FUNC) {
            cata_parse_fn(tokenized, tokens_count, &i);
        }

        if (tokenized[i].token_type == TOKEN_TYPE_WRITE) {
            cata_parse_write(tokenized, tokens_count, &i);
        }
    }
}

// =============================================

int main(int argc, char **argv) {
    argv_next(&argc, &argv);

    if (argc == 0) {
        fprintf(stderr, "Usage: ./cata <filename>\n");
        exit(1);
    } 

    const char *filename  = NULL;
    const char *file_path = NULL;

    while (argc > 0) {
        const char *arg = argv_next(&argc, &argv);

        if (!strcmp("cata", get_cata_ext(arg))) {
            file_path = arg;
            filename  = lazy_filename(arg);
        } else {
            fprintf(stderr, "ERROR: not a `.cata` file\n");
            exit(1);
        }
    }

    FILE *cata_file  = fopen(file_path, "r");

    if (!cata_file) {
        fprintf(stderr, "ERROR: no such file or directory %s\n",filename);
        exit(1);
    }

    size_t tokens_count = 0;
    char *program = readFile(cata_file);

    Token tokenized[BUFSIZ];
    lexer(program, tokenized, &tokens_count);
    // Print tokens from file
    for (size_t i = 0; i < tokens_count; ++i) {
        printf("Token: %.*s -> %d\n",
            (int)tokenized[i].token_value.length,
            CS_FMT(tokenized[i].token_value),
            tokenized[i].token_type
        );
    }
    parser(tokenized, tokens_count);

    return 0;
}