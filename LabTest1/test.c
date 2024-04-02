/* 
Q. Create a parent child realtion between 2 process such tha tchild process creates a file named relation.txt and the parent process write some content into it by taking input from the user.

submitted by: Sahil Mandi, (BT21ECE098)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    printf("Parent process (PID: %d) started\n", getpid());

    // Create a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) started\n", getpid());

        // Create the file "relation.txt"
        FILE *file = fopen("relation.txt", "w");
        if (file == NULL) {
            fprintf(stderr, "Error creating file\n");
            exit(1);
        }
        fclose(file);

        printf("Child process (PID: %d) created the file 'relation.txt'\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Parent process (PID: %d) waiting for child process (PID: %d) to finish\n", getpid(), pid);

        // Wait for the child process to terminate
        wait(&status);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("Parent process (PID: %d) detected child process (PID: %d) finished successfully\n", getpid(), pid);

            // Open the file "relation.txt" for writing
            FILE *file = fopen("relation.txt", "w");
            if (file == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(1);
            }

            // Get input from the user and write it to the file
            char input[100];
            printf("Parent process (PID: %d) prompting user for input\n", getpid());
            printf("Enter content to write to the file: ");
            fgets(input, sizeof(input), stdin);
            fputs(input, file);

            fclose(file);
            printf("Parent process (PID: %d) wrote content to the file 'relation.txt'\n", getpid());
        } else {
            printf("Parent process (PID: %d) detected child process (PID: %d) terminated abnormally\n", getpid(), pid);
        }
    }

    return 0;
}