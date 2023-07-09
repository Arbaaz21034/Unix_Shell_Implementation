#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>



int main(int argc, char* argv[])
{
   

    char* flag = argv[1];
    int flag_list = 0;
    int flag_hidden = 0;
    char* directories[100];
    int index_directories = 0;
    if (flag)
    {
        if (!strcmp(flag, "-a"))
        {
          
            flag_hidden = 1;
        }
        else if (!strcmp(flag, "-l"))
        {
           
            flag_list = 1;
        }
    }
    char wd[2000];
    if (flag_hidden || flag_list)
    {
        if (argc == 3)
        {
            strcpy(wd,argv[2]);
        }
        else if (argc == 2)
        {
            getcwd(wd, sizeof(wd));
        }
    }
    else
    {
        if (argc == 2)
        {
          
            strcpy(wd,argv[1]);
            
        }
        else if (argc == 1)
        {
            getcwd(wd, sizeof(wd));
        }
        
    }
    

    
    DIR* start = opendir(wd);
   
    if (start)
    {
        struct dirent* directory = readdir(start);
        while(directory)
        {

            if (directory->d_name[0] == '.')
            {
                if (!flag_hidden)
                {
                    directory = readdir(start);
                    
                    continue;
                }
                
            }
            
            
            printf("%s  ", directory->d_name);
            directory = readdir(start);
            if (flag_list)
            {
                printf("\n");
            }
        }
        if (!flag_list)
        {
            printf("\n");
        }
        

    }
    else
    {
        perror("ls");

    }

    return 0;
}