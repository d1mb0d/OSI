#include <stdio.h>

int *func() {
    int x = 10;
    return &x;
}

int main() {
    printf("%p\n", func());
    return 0;
}
