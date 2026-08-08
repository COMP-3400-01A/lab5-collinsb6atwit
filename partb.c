#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document

    if (argc != 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }//end if

    char* input_filename = argv[1];
    char* output_filename = argv[2];

    int fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0770);

    if (fd == -1) {
        perror("open");
        return 1;
    }//end if

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return 1;
    }//end if

    close(fd);

    printf("Category,Count\n");
    fflush(stdout);

    char* parta_args[] = { "./parta", input_filename, NULL };

    int eret = execv("./parta", parta_args);

    if (eret == -1) {
        perror("execv");
        return 1;
    }//end if

    return 0;
}
