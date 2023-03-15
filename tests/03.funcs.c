#include <stdio.h>

int sum(int x, int y) {
    return x + y;
}

int main() {
    printf("Calling function\n");
    printf("%d\n", sum(15, 15));
}