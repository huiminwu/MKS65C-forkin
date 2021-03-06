#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    printf("Initial Message from Parent\n");
    int fork_val;
    if(fork_val = fork()) { //if parent
        fork_val = fork(); //fork again
    }

    if (fork_val == 0) { //if child
        printf("Child pid: %i\n", getpid());
        int * num = malloc(sizeof(int));
        int fd = open("/dev/random", O_RDONLY);
        read(fd, num, sizeof(int));
        int temp =  abs(*num % 16) + 5;
        sleep(temp);
        printf("Child Program with child process num: %i has ended\n", getpid());
        close(fd);
        exit(temp);
    }

    if (fork_val != 0) { //if parent
        int status;
        int pid = wait(&status);
        if(WIFEXITED(status)) {
            int sec = WEXITSTATUS(status);
            printf("Parent Program has ended after child pid num %i who snoozed for %i secs\n", pid, sec);
        }
        return 0;
    }
    return 0;
}
