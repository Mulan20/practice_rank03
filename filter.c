//filter 
//Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
//realloc, free, printf, fprintf, stdout, stderr, perror

//echo "hello " | ./a.out 'h'

#define _GNU_SOURCE
#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 42
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void ft_filter(char *str, const char *target) //don't forget to make this const
{
    int len = strlen(target);
    int i = 0;
    int j, k;
    while (str[i])
    {
        j = 0;
        while (target[j] && str[i + j] == target[j])
            j++;
        if (j == len)
        {
            k = 0;
            while (k < len)
            {
                write(1, "*", 1);
                k++;
            }
            i += len; //this should be len not j
        }
        else 
        {
            write(1, &str[i], 1);
            i++;
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2 || av[1][0] == '\0')
    {
        perror("user input \n"); //no need for this one
        return 1;
    }

   char b[BUFFER_SIZE];
   char *temp;
   char *result = NULL;
   int total_read = 0; //set this to 0 improtant!
   ssize_t bytes;

   while ((bytes = read(0, b, BUFFER_SIZE)) > 0)
   {
        temp = realloc(result, total_read + bytes + 1);
        if (!temp)
        {
            free(result);
            perror("allocation");
            return 1;
        }
        result = temp;
        memmove(result + total_read, b, bytes);
        total_read += bytes;
        result[total_read] = '\0';
   }

   if (bytes < 0)
   {
    free(result);
    perror("read");
    return 1;
   }
   if (!result)
        return 0;

    ft_filter(result, av[1]);
    free(result);
    return 0;
}