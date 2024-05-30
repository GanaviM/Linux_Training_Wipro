#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
  pid_t child_pid = fork();

  if (child_pid < 0) {
    perror("fork failed");
    return 1;
  }

  // Parent process
  if (child_pid > 0) {
    printf("Parent process: PID = %d\n", getpid());
    wait(NULL); // Wait for child to finish
  } 

  // Child process
  else {
    printf("Child process: PID = %d\n", getpid());
    char *argv[] = {"ls", "-l", NULL}; // Arguments for ls command
    execv("/bin/ls", argv);  // Replace child process with ls
    perror("execv failed");  // Only if execv fails
    exit(1);
  }

  return 0;
}
