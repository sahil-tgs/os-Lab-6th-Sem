#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>

bool flag[2] = {false, false};
int turn = 0;

void fun1() {
    flag[0] = true;
    turn = 1;

    while (flag[1] && turn == 1) {
        // Busy waiting
    }

    // Critical section
    FILE* file = fopen("shared_file.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int count;
    fscanf(file, "%d", &count);

    int a = count; // 1
    a = a + 1;     // 2
    count = a;     // 3
    printf("fun1: %d\n", count);

    rewind(file);
    fprintf(file, "%d", count);
    fflush(file);

    fclose(file);

    // Remainder section
    flag[0] = false;
}

void fun2() {
    flag[1] = true;
    turn = 0;

    while (flag[0] && turn == 0) {
        // Busy waiting
    }

    // Critical section
    FILE* file = fopen("shared_file.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int count;
    fscanf(file, "%d", &count);

    int b = count; // 4
    b = b - 1;     // 5
    count = b;     // 6
    printf("fun2: %d\n", count);

    rewind(file);
    fprintf(file, "%d", count);
    fflush(file);

    fclose(file);

    // Remainder section
    flag[1] = false;
}

int main() {
    FILE* file = fopen("shared_file.txt", "w");
    fprintf(file, "5");
    fclose(file);

    // Execution order 1: 1, 2, 3, 4, 5, 6
    fun1();
    fun2();

    // Execution order 2: 1, 4, 2, 5, 3, 6
    FILE* file2 = fopen("shared_file.txt", "w");
    fprintf(file2, "5");
    fclose(file2);

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        fun1();
    } else if (pid > 0) {
        // Parent process
        fun2();
    } else {
        perror("Error forking process");
        exit(1);
    }

    return 0;
}