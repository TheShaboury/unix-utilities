#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    
    const char *source = argv[1];
    const char *destination = argv[2];
    
    int src_fd = open(source, O_RDONLY);
    if (src_fd == -1) {
        fprintf(stderr, "cp: cannot open '%s': %s\n", source, strerror(errno));
        return 1;
    }
    
    // Get source file permissions
    struct stat src_stat;
    if (fstat(src_fd, &src_stat) == -1) {
        fprintf(stderr, "cp: cannot stat '%s': %s\n", source, strerror(errno));
        close(src_fd);
        return 1;
    }
    
    int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode);
    if (dest_fd == -1) {
        fprintf(stderr, "cp: cannot create '%s': %s\n", destination, strerror(errno));
        close(src_fd);
        return 1;
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "cp: write error to '%s': %s\n", destination, strerror(errno));
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }
    
    if (bytes_read == -1) {
        fprintf(stderr, "cp: read error from '%s': %s\n", source, strerror(errno));
        close(src_fd);
        close(dest_fd);
        return 1;
    }
    
    if (close(src_fd) == -1) {
        fprintf(stderr, "cp: error closing '%s': %s\n", source, strerror(errno));
        close(dest_fd);
        return 1;
    }
    
    if (close(dest_fd) == -1) {
        fprintf(stderr, "cp: error closing '%s': %s\n", destination, strerror(errno));
        return 1;
    }
    
    return 0;
}
