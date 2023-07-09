#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <pthread.h>

#define MAXCOMLENGTH 1000
#define MAXWORDS 100
char perm[100];
char single_quote = 39;

char current_d[2000];

char open_d[2000];

void start_Shell()
{

    printf("\e[1;1H\e[2J");
    printf("\n\n\t\t\t\tSHELL BY ARBAAZ\n\n\n");

    return;
}

void takeInput(char *input)
{
 
  
    scanf("%[^\n]%*c", input);
    strcpy(perm, input);

}

int processingCommand(char *s, char **processed)
{
    

    char *token = strtok(s, " ");
    int i = 0;
    while (token != NULL)
    {

        processed[i++] = token;

        token = strtok(NULL, " ");
    }
    processed[i++] = NULL;
    return i-1;
}

void execute_pwd(char **processed)
{
    if (processed[1] != NULL)
    {
        if (!strcmp(processed[1], "-L") || !strcmp(processed[1], "-P"))
        {

        }
        else
        {
            printf("pwd: too many arguments\n");
            return;
        }
        
    }
    char wd[2000];

    if (getcwd(wd, sizeof(wd)))
    {
        printf("%s\n", wd);
    }
    else
    {
        perror("pwd: ");
    }
    
}

void execute_cd(char **processed)
{
    int index_file;
    if (!strcmp(processed[1], "-L") || !strcmp(processed[1],"-P"))
    {
        index_file = 2;
    }
    else
    {
        index_file = 1;
    }
    int failed = chdir(processed[index_file]);
    if (failed)
    {
        printf("cd: no such file or directory: %s\n", processed[1]);
    }

}

int find_quotes(char **processed, char* print_string)
{
    int processed1_index = 0;
    while (print_string[processed1_index] != '\0')
    {
        if (print_string[processed1_index] == '"')
        {
            return 2;
        }
        else if (print_string[processed1_index] == single_quote)
        {
            return 1;
        }
        processed1_index++;
    }
    return 0;
}
void print_echo_help()
{
    printf("\nECHO MANUAL\n\n");
    printf("NAME\n\techo – write arguments to the standard output\n\n");
    printf("SYNOPSIS\n\techo [-n] [string ...]\n");
    printf("DESCRIPTION\n\tThe echo utility writes any specified operands, separated by single blank (‘ ’) characters and followed by a newline (‘\\n’) character, to the standard output.\n\n");
    printf("\tThe following option is available:\n\n");
    printf("\t-n\t Do not print the trailing newline character.\n\n");
    printf("\t--help\n\t\tDisplay this help and exit\n\n");
    printf("EXIT STATUS\n\tThe echo utility exits 0 on success, and >0 if an error occurs.\n\n");

}
void execute_echo(char **processed)
{
    char* flag = processed[1];
    char print_string[1000];
    int index_processed;
    int flag_newline = 0;
    if (flag)
    {
        if (strcmp(flag, "-n") == 0)
        {
            flag_newline = 1;
            strcpy(print_string, processed[2]);
            index_processed = 3;
        }
        else if (strcmp(flag, "--help") == 0)
        {
            print_echo_help();
            return;
        }
        else
        {
            strcpy(print_string, processed[1]);
            index_processed = 2;
        }
    }
    else
    {
        printf("\n");
        return;
    }
    
    while(processed[index_processed] != NULL)
    {
        strcat(print_string, " ");
        strcat(print_string, processed[index_processed]);
        index_processed++;
    }
    
    int q = find_quotes(processed, print_string);
    if (q == 2)
    {
        char print[1000];
        int print_index = 0;
        int processed1_index = 0;
        int paired = 1;
        int flag = 0;
        while (1)
        {
            char c;

            if (!flag)
            {
                if (print_string[processed1_index] == '\0')
                {

                    c = '\n';
                    flag = 1;
                }
                else
                {
                    c = print_string[processed1_index++];
                }
            }
            else
            {
                scanf("%c", &c);
            }
            if (c != '"')
            {
                print[print_index++] = c;
            }

            if (paired && (c == '\n'))
            {
                if (flag_newline)
                {
                    print_index--;
                    print[print_index++] = '\0';
                }
                else
                {
                    print[print_index++] = '\0';
                }
                break;
            }
            if (c == '\n')
            {
                printf("dquote> ");
            }
            if (c == '"')
            {
                if (paired)
                {
                    paired = 0;
                }
                else
                {
                    paired = 1;
                }
            }
        }
        printf("%s", print);
    }
    else if (q == 1)
    {
        char print[1000];
        int print_index = 0;
        int processed1_index = 0;
        int paired = 1;
        int flag = 0;
        while (1)
        {
            char c;

            if (!flag)
            {
                if (print_string[processed1_index] == '\0')
                {

                    c = '\n';
                    flag = 1;
                }
                else
                {
                    c = print_string[processed1_index++];
                }
            }
            else
            {
                scanf("%c", &c);
            }
            if (c != single_quote)
            {
                print[print_index++] = c;
            }

            if (paired && (c == '\n'))
            {
                if (flag_newline)
                {
                    print_index--;
                    print[print_index++] = '\0';
                }
                else
                {
                    print[print_index++] = '\0';
                }
                
                break;
            }
            if (c == '\n')
            {
                printf("dquote> ");
            }
            if (c == single_quote)
            {
                if (paired)
                {
                    paired = 0;
                }
                else
                {
                    paired = 1;
                }
            }
        }
        printf("%s", print);
    }
    else
    {
        if (flag_newline)
        {
            printf("%s", print_string);
        }
        else
        {
            printf("%s\n", print_string);
        }
        
    }
}



void execute_external(char** processed)
{
    char path[2000];
    strcpy(path, open_d);
    strcat(path, processed[0]);
  
    int parent = fork();
    
    if (!parent)
    {
   
        int h = execv(path, processed);

        exit(0);
    }
    else
    {
        wait(NULL);
    }
}
void* thread_f(void* args)
{
    

    char input1[100];

    int i = 0;
    while(perm[i] != '\0')
    {
        i++;
    }
    int input1_index = 0;
    int path_index = 0;
    char path[2000];
    strcpy(path, open_d);
    while(path[path_index] != '\0')
    {
        input1[input1_index++] = path[path_index++];
    }

    input1[input1_index++] = '/';
    for(int j = 0; j < (i-3);j++)
    {   
        
        input1[input1_index++] = perm[j];
    }


    system(input1);



   
    void* ret;
    return ret;
}
void execute_external_thread(char** processed)
{
 
    pthread_t p;
  
    
    pthread_create(&p, NULL, &thread_f, NULL);
    pthread_join(p, NULL);

    
}

int check_for_allowed_commands(char** processed)
{
    if (!strcmp(processed[0], "cd"))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "echo"))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "pwd"))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "exit"))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "clear"))
    {
        return 1;
    }
    else if ((!strcmp(processed[0], "ls")))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "cat"))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "date"))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "rm"))
    {
        return 1;
    }
    else if (!strcmp(processed[0], "mkdir"))
    {
        return 1;
    }
    return 0;
}

int main()

{

    getcwd(open_d, sizeof(open_d));

    strcat(open_d, "/");
    start_Shell();

    char s[MAXCOMLENGTH];
    
    char *processed[MAXCOMLENGTH];
 
    getcwd(current_d, sizeof(current_d));
    while (1)
    {
        
        
        
        
        printf("[*] %s --> ", current_d);

        takeInput(s);
        int total = processingCommand(s, processed);
        
        int allow = check_for_allowed_commands(processed);
        if (!allow)
        {
            printf("shell: command not found: %s\n", processed[0]);
            continue;
        }
       
        if (!strcmp(processed[0], "cd"))
        {
            execute_cd(processed);
            getcwd(current_d, sizeof(current_d));
        }
        else if (!strcmp(processed[0], "echo"))
        {
            execute_echo(processed);
        }
        else if (!strcmp(processed[0], "pwd"))
        {
            execute_pwd(processed);
        }
        else if (!strcmp(processed[0], "exit"))
        {
            printf("[Process Completed]\n");
            exit(0);
        }
        else if (!strcmp(processed[0], "clear"))
        {
            printf("\e[1;1H\e[2J");
        }
        else
        {
            int last = total - 1;
            if (!strcmp(processed[last], "&t"))
            {
                execute_external_thread(processed);
            }
            else
            {
                
                execute_external(processed);
            }
            
        }
    }

    return 0;
}
