#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int copy_file(const char *source, const char *destination) {
    int src_fd = open(source, O_RDONLY);
    if (src_fd == -1) {
        return -1;
    }
    
    struct stat src_stat;
    if (fstat(src_fd, &src_stat) == -1) {
        close(src_fd);
        return -1;
    }
    
    int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode);
    if (dest_fd == -1) {
        close(src_fd);
        return -1;
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            close(src_fd);
            close(dest_fd);
            return -1;
        }
    }
    
    if (bytes_read == -1) {
        close(src_fd);
        close(dest_fd);
        return -1;
    }
    
    close(src_fd);
    close(dest_fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    
    const char *source = argv[1];
    const char *destination = argv[2];
    
    // Try to rename first (3a4an law fe nafs el makan)
    if (rename(source, destination) == 0) {
        return 0;
    }
    
    if (errno == EXDEV) {
        // Copy file to new location
        if (copy_file(source, destination) == -1) {
            fprintf(stderr, "mv: cannot copy '%s' to '%s': %s\n", source, destination, strerror(errno));
            return 1;
        }
        
        // Remove original file
        if (unlink(source) == -1) {
            fprintf(stderr, "mv: cannot remove '%s': %s\n", source, strerror(errno));
            return 1;
        }
        
        return 0;
    } else {
        fprintf(stderr, "mv: cannot move '%s' to '%s': %s\n", source, destination, strerror(errno));
        return 1;
    }
}
