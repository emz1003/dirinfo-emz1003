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
    char *dir = calloc(1028, sizeof(char));
    char *files = calloc(1028, sizeof(char));

    stat(d, &s);

    printf("Statistics for directory: %c\nTotal directory size: %lld Bytes\n", *d, s.st_size);
    while (file) {
        char *temp = calloc(256, sizeof(char));
        stat(file->d_name, &s);
        if (errno) {
            printf("%d: %s\n", errno, strerror(errno));
        }

        char *mode = format_mode(s.st_mode);
            sprintf(temp, "\t%-16s %-16s %-16s", mode, file->d_name, ctime(&s.st_mtime));
        if(s.st_mode / 01000 == 040)
            strcat(dir, temp);
        else
            strcat(files, temp);
        file = readdir(mydir);
        free(temp);
        free(mode);
    }
    printf("directories:\n%sfiles:\n%s\n", dir, files);
    free(dir);
    free(files);
    closedir(mydir);
    return 0;
}