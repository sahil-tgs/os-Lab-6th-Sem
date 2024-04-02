#include <stdio.h>

int count = 5; // global variable

void fun1() {
    int a;
    a = count; // 1
    a = a + 1; // 2
    count = a; // 3
    printf("%d\n", count);
}

void fun2() {
    int b;
    b = count; // 4
    b = b - 1; // 5
    count = b; // 6
    printf("%d\n", count);
}

int main() {
    // Execution order 1: 1, 2, 3, 4, 5, 6
    fun1();
    fun2();
    printf("\n");
    count = 5; // Reset count to initial value

    // Execution order 2: 1, 4, 2, 5, 3, 6
    int a = count; // 1
    int b = count; // 4
    a = a + 1;     // 2
    b = b - 1;     // 5
    count = a;     // 3
    printf("%d\n", count);
    count = b;     // 6
    printf("%d\n", count);

    return 0;
}