#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>
#include <sys/stat.h>

void date_r_file(char* file)
{
    struct stat st;
    char time_file[100];
    int status = stat(file, &st);

    if (!status)
    {
        strftime(time_file, 100,  "%a %b %d %H:%M:%S %Y\n", localtime(&st.st_mtime));
    
        printf("%s", time_file);
     
    }
    else
    {
        perror("date");
    }
}



int checkformat(char* f)
{
    
    if(f[0] == '"' && f[1] == '+')
    {
        return 1;
    }

    return 0;
}
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "-r"))
        {
            date_r_file(argv[2]);
        }
        else if (!strcmp(argv[1], "-u"))
        {
            time_t seconds;
            time(&seconds);
            char current_date_and_time[100];
            strftime(current_date_and_time, 100, "%a %b %d %T UTC %Y", gmtime(&seconds));
            printf("%s\n", current_date_and_time);
        }
        else if (checkformat(argv[1]))
        {

            char format[100];
            int i = 2;
            int index_format = 0;
            while(argv[1][i]!='"')
            {
                format[index_format++] = argv[1][i++];
            }

            time_t seconds;
            time(&seconds);
            char time_in_format[100];
            strftime(time_in_format, 100, format, localtime(&seconds));
            printf("%s\n", time_in_format);

        }
    }
    else
    {
        time_t seconds;
        time(&seconds);
        char current_date_and_time[100];
        strftime(current_date_and_time, 100, "%a %b %d %T IST %Y", localtime(&seconds));
        printf("%s\n", current_date_and_time);

    }
    
}