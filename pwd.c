#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_PATH 4096

int main() {
    char cwd[MAX_PATH];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return 0;
    } else {
        fprintf(stderr, "pwd: %s\n", strerror(errno));
        return 1;
    }
}
