#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void buffer_operations() {
    char* buffer1 = (char*)malloc(100);
    if (buffer1 == NULL) {
        printf("Memory allocation error.\n");
        return;
    }
    strcpy(buffer1, "hello world!");
    printf("%s\n", buffer1);
    free(buffer1);
    printf("%s\n", buffer1); // Неопределенное поведение.
    char* buffer2 = (char*)malloc(14);
    if (buffer2 == NULL) {
        printf("Memory allocation error.\n");
        return;
    }
    strcpy(buffer2, "hello world!");
    printf("%s\n", buffer2);
    char* middle = buffer2 + 7;
    // Освобождаем память по смещенному указателю.
    free(middle); // Неопределенное поведение.
    // В зависимости от реализации программа может как завершиться с ошибкой,
    // так и продолжить работу.
//  printf("%s\n", buffer2);
    free(buffer2);
}

int main(){
    buffer_operations();
    return 0;
}
