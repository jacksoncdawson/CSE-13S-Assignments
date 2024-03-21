#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define B 16
void p(const unsigned char *b, ssize_t r, off_t o) {
    printf("%08lx: ", (unsigned long) o);
    for (int i = 0; i < B; i++) {
        (i < r) ? printf("%02x", b[i]) : printf("  ");
        printf((i % 2 == 1) ? " " : "");
    }
    printf(" ");
    for (int i = 0; i < r; i++)
        printf("%c", isprint(b[i]) ? b[i] : '.');
    printf("\n");
}
int main(int argc, char **argv) {
    int fd = argc == 2 ? open(argv[1], O_RDONLY) : STDIN_FILENO;
    if (fd == -1 || argc > 2)
        return 1;
    unsigned char b[B];
    off_t o = 0;
    for (ssize_t r, t; (memset(b, 0, B), t = 0, 1); o += t) {
        while (t < B && (r = read(fd, b + t, (size_t) (B - t))) > 0)
            t += r;
        if (t == 0)
            break;
        p(b, t, o);
        if (t < B)
            break;
    }
    close(fd);
    return 0;
}
