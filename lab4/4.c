#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Значение переменной SAMPLE_ENV: %s\n", getenv("SAMPLE_ENV"));
    putenv("SAMPLE_ENV=new_sample_text");
    printf("Новое значение переменной SAMPLE_ENV: %s\n", getenv("SAMPLE_ENV"));
    return 0;
}
