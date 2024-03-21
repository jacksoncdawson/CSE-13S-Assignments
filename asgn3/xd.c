#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 16

void printRow(const unsigned char *buffer, ssize_t bytesRead, off_t offset) {

    // print offset
    printf("%08lx: ", (unsigned long) offset);

    // print hex representation
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i < bytesRead) {
            printf("%02x", buffer[i]);
        } else {
            printf("  ");
        }

        if (i % 2 == 1) {
            printf(" ");
        }
    }

    // print ASCII representation
    printf(" ");
    for (int i = 0; i < bytesRead; i++) {
        printf("%c", isprint(buffer[i]) ? buffer[i] : '.');
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    int fd;
    ssize_t bytesRead, totalBytesRead;
    unsigned char buffer[BUFFER_SIZE];
    off_t offset = 0;

    // return error if more than 2 args given
    if (argc > 2) {
        return 1;
    }

    // open fd if two arguments given; return error if file DNE, etc...
    // else, read from STDIN
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            return 1;
        }
    } else {
        fd = STDIN_FILENO;
    }

    while (1) {
        memset(buffer, 0, BUFFER_SIZE); // clear buffer
        totalBytesRead = 0;

        while (totalBytesRead < BUFFER_SIZE) {
            bytesRead = read(fd, buffer + totalBytesRead, (size_t) (BUFFER_SIZE - totalBytesRead));
            if (bytesRead <= 0) {
                break;
            }
            totalBytesRead += bytesRead;
        }

        if (totalBytesRead == 0) {
            break;
        }

        printRow(buffer, totalBytesRead, offset);
        offset += totalBytesRead;

        if (totalBytesRead < BUFFER_SIZE) {
            break;
        }
    }

    // close fd if fd was given
    if (argc == 2) {
        close(fd);
    }

    return 0;
}
