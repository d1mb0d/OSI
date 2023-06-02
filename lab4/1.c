#include <stdio.h>
#include <unistd.h>

int d = 100;
int e;
const float f = 100;

void variables() {
    int a;
    static int b;
    const int c = 'A';
    printf("Address of local a: %p\n", (void*)&a);
    printf("Address of static b: %p\n", (void*)&b);
    printf("Address of const c: %p\n", (void*)&c);
    printf("Address of global initialized d: %p\n", (void*)&d);
    printf("Address of global not initialized e: %p\n", (void*)&e);
    printf("Address of global const initialized f: %p\n", (void*)&f);
}

int main() {
    printf("PID: %d\n", getpid());
    variables();
    sleep(30);
    return 0;
}
