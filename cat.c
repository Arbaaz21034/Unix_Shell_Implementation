
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void handle_file(char* file, int flag_n, int flag_b)
{
    FILE* fptr;
    fptr = fopen(file, "r");
    if (!fptr)
    {
        printf("cat: %s: No such file or directory", file);
        return;
    }
    char next;
    char c = fgetc(fptr);
    int count = 1;
    if (flag_n)
    {
        printf("%d  ", count);
        count++;
    }
    if (flag_b)
    {
        if (c == '\n')
        {

        }
        else
        {
            
            printf("%d  ", count);
            count++;
        }
    }
    

    while(c != EOF)
    {
        next = fgetc(fptr); 
        printf("%c", c);
        if (c == '\n')
        {

            
            if (flag_n)
            {
                
                printf("%d  ", count);
                count++;

            }
            else if (flag_b)
            {
                
                if (next == '\n' || next == EOF)
                {

          
                }
                else
                {

                    printf("%d  ", count);
                    count++;
                }   
            }
          
            

        }
        
        
      
        c = next;

    }
    
    fclose(fptr);
}

int main(int argc,char*argv[])
{
    int flag_n = 0;
    char* flag = argv[1];
    char* file;
    int flag_b = 0;
    int index;
    if (argc > 2)
    {
        
        if (!strcmp(flag, "-n"))
        {
            flag_n = 1;
            index = 2;
        }
        else if (!strcmp(flag, "-b"))
        {
            flag_b = 1;
            index = 2;
        }
        else
        {
            index = 1;
        }
        
    }
    else
    {
        index = 1;
    }
    for (int j = index; j < argc; j++)
    {
        handle_file(argv[j], flag_n, flag_b);
    }
    printf("\n");
    
    return 0;
}