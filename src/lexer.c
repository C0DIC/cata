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
        strcat(program, line);
    }

    fclose(source_file);
    return program;
}

void lexer(char *program, Token *tokenArray, size_t *tokens_count) {
    CataStr cata_program = castr_ltrim(' ', CS(program));
    CataStr token = CS("");

    while (cata_program.length > 0) {
        if (isalpha(cata_program.data[0])) {
            token = castr_walpha(cata_program);
            cata_program = castr_ltrim(' ', castr_cut_by(token.length, cata_program));

            if (castr_same(token, CS("fn"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_FUNC);
                *tokens_count += 1;
            } else if (castr_same(token, CS("write"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_WRITE);
                *tokens_count += 1;
            } else if (castr_same(token, CS("end"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_END);
                *tokens_count += 1;
            } else if (castr_same(token, CS("loop"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_LOOP);
                *tokens_count += 1;
            } else if (castr_same(token, CS("as"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_AS);
                *tokens_count += 1;
            } else if (castr_same(token, CS("return"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_RETURN);
                *tokens_count += 1;
            } else if (castr_same(token, CS("var"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_VAR);
                *tokens_count += 1;
            } else if (castr_same(token, CS("int"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_INT_TYPE);
                *tokens_count += 1;
            }  else if (castr_same(token, CS("float"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_FLOAT_TYPE);
                *tokens_count += 1;
            } else if (castr_same(token, CS("str"))) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_STRING_TYPE);
                *tokens_count += 1;
            } else {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_NAME);
                *tokens_count += 1;
            }
        } else if (isdigit(cata_program.data[0])) {
            token = castr_wdigit(cata_program);
            cata_program = castr_ltrim(' ', castr_cut_by(token.length, cata_program));

            if (castr_has('.', token)) {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_FLOAT);
                *tokens_count += 1;
            } else {
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_INT);
                *tokens_count += 1;
            }

        } else {
            if (cata_program.data[0] == ':') {
                token = CS(":");
                cata_program = castr_ltrim(' ', castr_cut_by(token.length, cata_program));

                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_COLON);
                *tokens_count += 1;
            } else if (cata_program.data[0] == '"') {
                cata_program = castr_cut_by(1, cata_program);
                token = castr_untilc('"', cata_program);
                cata_program = castr_ltrim(' ', castr_cut_by(token.length + 1, cata_program));

                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_STRING);
                *tokens_count += 1;
            } else if (cata_program.data[0] == '.') {
                if (cata_program.data[1] == '.') {
                    token = CS("..");
                    cata_program = castr_trim(' ', castr_cut_by(token.length, cata_program));
                    tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_ITERATOR);
                    *tokens_count += 1;
                } else {
                    token = CS(".");
                    cata_program = castr_trim(' ', castr_cut_by(token.length, cata_program));
                    tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_DOT);
                    *tokens_count += 1;
                }
            } else if (cata_program.data[0] == '+') {
                token = CS("+");
                cata_program = castr_trim(' ', castr_cut_by(token.length, cata_program));
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_PLUS);
                *tokens_count += 1;
            } else if (cata_program.data[0] == '=') {
                token = CS("=");
                cata_program = castr_trim(' ', castr_cut_by(token.length, cata_program));
                tokenArray[*tokens_count] = createToken(token, TOKEN_TYPE_EQUAL);
                *tokens_count += 1;
            } else if (cata_program.data[0] == '#') {
                cata_program = castr_trim(' ', castr_cutc('\n', cata_program));
            } else if (cata_program.data[0] == 10 || cata_program.data[0] == ' ') {
                cata_program = castr_cut_by(1, cata_program);
            } else {
                fprintf(stderr, "ERROR: uknown operand `%c` occured\n", cata_program.data[0]); 
                exit(1);
            }
        }
        
        cata_program = castr_ltrim(' ', castr_ltrim('\n', cata_program));
        // /printf("||%.*s||\n", (int)cata_program.length, CS_FMT(cata_program));
    }
}