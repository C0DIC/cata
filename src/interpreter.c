#include <stdio.h>
#include "catastring/catastring.h"

#define MAX_TEST_BUFSIZE 1024

void write_expr(CataStr args) {
    if (args.length <= 0) {
        fprintf(stderr, "ERROR: excepted `(` after write\n");
    } else if(!castr_endswith(")", args)) {
        fprintf(stderr, "ERROR: `(` never closed\n");
    } else {
        args = castr_rtrim(')', castr_ltrim('(', args));

        if (args.length != 0) {
            if (castr_to_lld(args) || castr_same(args, CS("0")))
                fprintf(stdout, "%lld\n", castr_to_lld(args));
            else fprintf(stderr, "ERROR: excepted only numbers as an argment for `write`\n");
        } else fprintf(stdout, "\n");
    }
};

void if_expr(CataStr expr) {
    return;
}

#if 0
int main() {
    // little token defins
    // ===================================================
    CataStr EXIT_EXPR  = CS("exit()");
    CataStr WRITE_EXPR = CS("write");
    CataStr IF_EXPR    = CS("if");
    // ===================================================

    CataStr input = CS((char*)malloc(MAX_TEST_BUFSIZE));

    while (true) {
        printf(">>> ");
        input = castr_trim(' ', castr_rtrim('\n', CS(fgets(input.data, MAX_TEST_BUFSIZE, stdin))));

        if (castr_startswith(CS_FMT(WRITE_EXPR), input)) {
            if (castr_has('(', input)) {
                if (castr_same(castr_untilc('(', input), WRITE_EXPR))
                    write_expr(castr_cutc('(', input));
                else fprintf(stdout, "ERROR: unkown command `%s`\n", CS_FMT(castr_untilc('(', input)));
            } else {
                if (castr_same(input, WRITE_EXPR))
                    write_expr(castr_cutc('(', input));
                else fprintf(stdout, "ERROR: unkown command `%s`\n", CS_FMT(input));
            }
        } else if (castr_startswith(CS_FMT(IF_EXPR), input)) {
            printf("[IF]%s\n", CS_FMT(input));
        } else if (castr_startswith(CS_FMT(EXIT_EXPR), input)) {
            break;    
        } else {
            fprintf(stdout, "ERROR: unkown command `%s`\n", CS_FMT(input));
        }
    }
}
#endif