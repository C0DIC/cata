#include <stdio.h>

int main() {
    for (int i = 0; i < 10; i++)
        printf("%d\n", i);

    for (int x = 10; x > 0; x--)
        printf("%d\n", x);

    return 0;
}

#if 0
    //    Print tokens from file
        for (size_t i = 0; i < tokens_count; ++i) {
            printf("Token: %.*s -> %d\n",
                (int)tokenized[i].token_value.length,
                CS_FMT(tokenized[i].token_value),
                tokenized[i].token_type
            );
        }
#endif