#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void mkdir_custom(char* file)
{
    struct stat s;
    int exist = stat(file, &s);
    if (exist == -1) // doesn't exist
    {
        int status = mkdir(file, 0777);
        if (status == -1)
        {
            perror("mkdir");
        }
    }
    else
    {
        printf("mkdir: %s: File exists\n", file);
    }
}

void mkdir_customp(char* file)
{
    struct stat s;
    int exist = stat(file, &s);
    if (exist == -1) // doesn't exist
    {
        int status = mkdir(file, 0777);
    }
  
}

int main(int argc, char* argv[])
{

    char* files[100];
    int index_files = 0;
    int i = 1;
    argc -= 1;
    while(argc--)
    {
        if (strcmp(argv[i],"-p") && strcmp(argv[i], "-v") && strcmp(argv[i], "&t"))
        {
            files[index_files++] = argv[i];
            
        }
        i++;
    }
    files[index_files++] = NULL;

    i = 0;
    while(files[i] != NULL)
    {
        
        if (!strcmp(argv[1], "-p"))
        {
            char* h[100];
            char *token = strtok(files[i], "/");
            int e = 0;
            while (token != NULL)
            {

                h[e++] = token;

                token = strtok(NULL, "/");
             
            }
            
            h[e++] = NULL;
            int total = e;
            e = 0;
            while(h[e] != NULL)
            {
                mkdir_customp(h[e]);
                chdir(h[e]);
                e++;
                
            }
            for (int k = 0; k < e; k++)
            {
                chdir("..");
            }
            
        }
        else if (!strcmp(argv[1], "-v"))
        {
            mkdir_custom(files[i]);
            printf("%s\n", files[i]);
            
        } 
        else
        {
            mkdir_custom(files[i]);
        }
        i++;
       
        
    }

    
    
    
    return 0;
}