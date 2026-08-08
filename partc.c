#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document

    if (argc != 2) {
        printf("USAGE: partc FILE\n");
        return 1;
    }//end if

    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }//end if

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }//end if

    if (pid > 0) {
        close(pipe_fd[0]);

        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            return 1;
        }//end if

        close(pipe_fd[1]);

        char* parta_args[] = { "./parta", argv[1], NULL };

        execv("./parta", parta_args);

        perror("execv");

        return 1;
    }//end if

    else {
        close(pipe_fd[1]);

        if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            return 1;
        }//end if

        close(pipe_fd[0]);

        char* sort_args[] = { "sort", "-t,", "-k2", "-n", NULL };

        execvp("sort", sort_args);

        perror("execvp");
        return 1;
    }//end else

    return 0;
}
