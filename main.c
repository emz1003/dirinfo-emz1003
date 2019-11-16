#include "dirinfo.h"

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
    char *dir = calloc(256, sizeof(char));
    char *files = calloc(256, sizeof(char));
    char *temp;

    stat(d, &s);

    printf("Statistics for directory: %c\nTotal directory size: %lld Bytes\n", *d, s.st_size);
    while (file) {
        temp = calloc(64, sizeof(char));
        stat(file->d_name, &s);
        if (errno) {
            printf("%s: %s\n", errno, strerror(errno));
        }
        sprintf(temp, "\t%-16s %-16s\n", format_mode(s.st_mode), file->d_name);
        if(s.st_mode / 01000 == 040)
            strcat(dir, temp);
        else
            strcat(files, temp);
        file = readdir(mydir);
        free(temp);
    }
    printf("directories:\n%sfiles:\n%s\n", dir, files);
    free(dir);
    free(files);
    closedir(mydir);
    return 0;
}