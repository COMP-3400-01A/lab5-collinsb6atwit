#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    // TODO: Complete and document

    if (argc != 2) {
        printf("USAGE: parta FILE\n");
        return 1;
    }//end if

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }//end if

    int upper = 0;
    int lower = 0;
    int number = 0;
    int space = 0;
    int others = 0;

    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, BUFSIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            unsigned char c = buffer[i];

            if (isupper(c)){
                upper++;
            }//end if
            else if (islower(c)){

            }//end else if
            else if (isdigit(c)){
                number++;
            }//end else if
            else if (isspace(c)){
                space++;
            }//end else if
            else {
                others++;
            }//end else
        }//end for
    }//end while

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }//end if

    close(fd);

    printf("Uppercase letters: %d\n", upper);
    printf("Lowercase letters: %d\n", lower);
    printf("Digits: %d\n", number);
    printf("Whitespace characters: %d\n", space);
    printf("Other characters: %d\n", others);

    return 0;
}
