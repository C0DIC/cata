#include "lexer.h"


#define MAX_TEST_BUFSIZE 1024

char *readFile(FILE *source_file) {
    // Getting the file size
    fseek(source_file, 0, SEEK_END);
    size_t file_size = ftell(source_file);
    fseek(source_file, 0, SEEK_SET);
    
    char *line    = (char*)malloc(MAX_TEST_BUFSIZE);
    char *program = (char*)malloc(file_size);

    while (fgets(line, MAX_TEST_BUFSIZE, source_file)) {
        if (!castr_startswith("#", castr_ltrim(' ', CS(line))) && castr_rtrim('\n', CS(line)).length != 0) {
            strcat(program, line);
        }
    }

    fclose(source_file);
    return program;
}

void lexer(char *program, Token *tokenArray, size_t *tokens_count) {
    CataStr cata_program = CS(program);

    CataStr line = castr_ltrim(' ', cata_program);
    CataStr token = castr_walpha(line);

    //printf("%.*s\n", (int)line.length, CS_FMT(line));
    //printf("%.*s - %lu - {TOKEN}\n", (int)token.length, CS_FMT(token), token.length);

    while(line.length != 0) {
        if (castr_startswith(" ", line)) {
            line = castr_ltrim(' ', line);
            token = castr_walpha(line);
        } else if (castr_startswith("\n", line)) {
            line = castr_ltrim(' ', castr_ltrim('\n', line));
            token = castr_walpha(line);
        } else if (castr_startswith("\t", line)) {
            line = castr_ltrim('\t', line);
            token = castr_walpha(line);
        }

        if (castr_same(token, CS("fn"))) {
            line = castr_cut_by(token.length, line);
            tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_FUNC);
            *tokens_count += 1;
        } else if (castr_same(token, CS("write"))) {
            line = castr_cut_by(token.length, line);
            tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_WRITE);
            *tokens_count += 1;
        } else if (castr_same(token, CS("end"))) {
            line = castr_cut_by(token.length, line);
            tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_END);
            *tokens_count += 1;
        } else {
            if (isalpha(line.data[0])) {
                line = castr_cut_by(token.length, line);
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_NAME);
                *tokens_count += 1;
            } else if (isdigit(line.data[0])) {
                token = castr_wdigit(line);
                line = castr_cut_by(token.length, line);
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_INT);
                *tokens_count += 1;
            } else {
                if (castr_startswith(":", line)) {
                    line = castr_cut_by(1, line);
                    tokenArray[*tokens_count] = createToken(CS(":"), TOKEN_TYPE_COLON);
                    token = castr_untilc(':', line);
                    *tokens_count += 1;
                } else if (castr_startswith("\"", line)) {
                    line = castr_cut_by(1, line);
                    token = castr_untilc('\"', line);

                    tokenArray[*tokens_count] = createToken(
                                    token, 
                                    TOKEN_TYPE_STRING
                    );

                    line = castr_cut_by(token.length + 1, line);
                    *tokens_count += 1;
                } else {
                    if (token.data[0] == 0) {
                        line = castr_cut_by(token.length, line);
                    } else {
                        if (isalpha(line.data[0])) {
                            fprintf(stderr, "ERROR: unknown operand `%.*s` occured\n", 
                                                    (int)token.length,
                                                    CS_FMT(token)
                            );
                            exit(1);
                        } else {
                            fprintf(stderr, "ERROR: unknown operand `%c` occured\n", line.data[0]);
                            exit(1);
                        }
                    }
                }
            }
        }
    }
}