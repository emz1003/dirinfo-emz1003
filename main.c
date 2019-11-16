#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR * mydir = opendir(".");
    if(errno) {
        printf("%d: %s\n", errno, strerror(errno));
    }

    struct dirent *file = readdir(mydir);
    struct stat s;
    while (file) {
        stat(file->d_name, &s);
        if (errno) {
            printf("%d: %s\n", errno, strerror(errno));
        }
        printf("%s\t %o\n", file->d_name, s.st_mode);
        file = readdir(mydir);
    }
    
    return 0;
}