#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    char * d = ".";
    DIR * mydir = opendir(d);
    
    if(errno) {
        printf("%d: %s\n", errno, strerror(errno));
    }
    
    struct dirent *file = readdir(mydir);
    
    if(errno) {
        printf("%d: %s\n", errno, strerror(errno));
    }

    struct stat s;
    char *dir = calloc(128, sizeof(char));
    char *files = calloc(128, sizeof(char));

    stat(d, &s);

    printf("Statistics for directory: %c\nTotal directory size: %lld Bytes\n", *d, s.st_size);
    while (file) {
        stat(file->d_name, &s);
        if (errno) {
            printf("%d: %s\n", errno, strerror(errno));
        }
        char * temp = calloc(128, sizeof(char));
        sprintf(temp, "\t%-16o %-16s\n", s.st_mode, file->d_name);
        if(s.st_mode / 01000 == 040)
            strcat(dir, temp);
        else
            strcat(files, temp);
        file = readdir(mydir);
    }
    printf("directories:\n%sfiles:\n%s\n", dir, files);
    free(dir);
    free(files);
    return 0;
}