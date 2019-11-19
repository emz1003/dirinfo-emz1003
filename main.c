#include "dirinfo.h"

int main(int argc, char* argv[]) {
    char *d = calloc(256, sizeof(char));
    if (argc < 2) {
        printf("please enter in a valid directory: ");
        fgets(d, 256, stdin);
        d[strlen(d) - 1] = 0;

        if (errno)
        {
            printf("%d: %s\n", errno, strerror(errno));
        }
    } else
        d = argv[1];

    DIR * mydir = opendir(d);
    
    if(errno) {
        printf("%d: %s\n", errno, strerror(errno));
    }
    
    struct dirent *file = readdir(mydir);
    
    if(errno) {
        printf("%d: %s\n", errno, strerror(errno));
    }

    struct stat s;
    char *dir = calloc(2048, sizeof(char));
    char *files = calloc(2048, sizeof(char));

    int size = 0;

    printf("Statistics for directory: %s\n", d);
    while (file) {
        char *temp = calloc(256, sizeof(char));
        stat(file->d_name, &s);
        char *mode = format_mode(s.st_mode);
            sprintf(temp, "\t%-16s %-16s %-16s", mode, file->d_name, ctime(&s.st_mtime));
        if(S_ISDIR(s.st_mode)){
            dir = strcat(dir, temp);
        }
        else{
            files = strcat(files, temp);
        }
        size += s.st_size;
        file = readdir(mydir);
        free(temp);
        free(mode);
    }
    printf("Total directory size: %.2f KB\n", size / (float)0b10000000000);
    printf("directories:\n%sfiles:\n%s\n", dir, files);
    free(dir);
    free(files);
    closedir(mydir);
    return 0;
}