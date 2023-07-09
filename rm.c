#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

void remove_custom(char* file)
{
    int failed = remove(file);
    if (failed)
    {
        perror("rm");
    
    }
}

int directory_error(char* file)
{
    struct stat s;
    stat(file, &s);
    int isDirectory = S_ISDIR(s.st_mode);
    if (isDirectory)
    {
        printf("rm: %s: is a directory\n", file);
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    char* files[100];
    int index_files = 0;
    int i = 1;
    argc -= 1;
    while(argc--)
    {
        if (strcmp(argv[i],"-i") && strcmp(argv[i], "-v"))
        {
            files[index_files++] = argv[i];
            
        }
        i++;
    }
    files[index_files++] = NULL;
    
   
    i = 0;
    while(files[i] != NULL)
    {
        int e = directory_error(files[i]);
        if (e)
        {
            i++;
            continue;
        }
        if (!strcmp(argv[1], "-i"))
        {
            printf("remove %s? ", files[i]);
            char c;
            scanf("%c", &c);
            char buffer;
            scanf("%c", &buffer);
            if ((c == 'y') || (c == 'Y'))
            {
                remove_custom(files[i]);
            }
            
        }
        else if (!strcmp(argv[1], "-v"))
        {
            remove_custom(files[i]);
            printf("%s\n", files[i]);
            
        } 
        else
        {
            remove_custom(files[i]);
        }
        i++;
       
        
    }
    
    return 0;
}