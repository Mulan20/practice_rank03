//permutations ./a.out ab -> ab ba

//allowed functions: puts, malloc, calloc, realloc, free, write

int is_alpha(char c)
{
    return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'));
}
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int ft_strchr(char *str, char c)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return 1;
    }
    return 0;
}

char *ft_sort(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i + 1] && str[i] > str[i + 1] )
        {
            char temp = str[i];
            str[i] = str[i + 1];
            str[i + 1] = temp;
            i = 0;
        }
        else
            i++;
    }
    return str;
}

void permute(int pos, char *sorted_string, char *result)
{
    int len = ft_strlen(sorted_string);
    if (len == pos)
    {
        write(1, result, len);
        write(1, "\n", 1);
        return ;
    }

    int i = 0;
    while (i < len) //this must be len not index 
    {
        if (!ft_strchr(result, sorted_string[i]))
        {

            result[pos] = sorted_string[i];
            permute(pos + 1, sorted_string, result);
            result[pos] = '\0';
        }
        i++;
    }

}

int main(int ac, char **av)
{
    if (ac != 2 )
        return 1;
    //you need to check len immediately
    int len = ft_strlen(av[1]);
    if (len == 0 || ( av[1][0] == ' ' &&!av[1][1])) //it should be || and && 
        return 1;
    //you need to check whether it includes only the char or not
    int i =0;
    while (av[1][i])
    {
        if (!is_alpha(av[1][i]))
            return 1;
        i++;
    }

   
    char *result; 
    result = (char *)calloc(len + 1, 1); //dont' forget that this is calloc 
    //don't forget to check this 
    if (!result)
        return 1;
    char *sorted_string = ft_sort(av[1]);

    permute(0, sorted_string, result);
    free(result);
    return 0;

}



