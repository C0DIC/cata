#define CATA_VAR
#define CATA_EXPR

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CATA_PARSER
#include "parser.h"

#include "lexer.h"

#include "catastring/catastring.h"

#define CATA_WRITE
#include "std/write.h"

#define CATA_LOOP
#include "std/loop.h"

#define CATA_CONDITIONS
#include "std/conditions.h"


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

    /*
    for (size_t i = 0; i < tokens_count; ++i) {
        printf("Token: %.*s -> %d\n",
            (int)tokenized[i].token_value.length,
            CS_FMT(tokenized[i].token_value),
            tokenized[i].token_type
        );
    }
    */
    parser(tokenized, 0, tokens_count);

    return 0;
}