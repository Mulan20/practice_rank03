//rip.c -> ./a.out ()()()

//allowed function -> write

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int is_balanced(char *str)
{
    int i = 0;
    int balance = 0;
    while (str[i]) //u may do with i < len as well 
    {
        if (str[i] == '(')
            balance++;
        else if (str[i] == ')')
        {
            balance--;
            if (balance < 0)
            {
                return 0;
            }
        }
        i++;
    }
    return (balance == 0);
}
void ft_rip(char *str, int *min_rmv, int pos, int current_rmv, int step)
{
    char saved; 
    int i;
    if (current_rmv > *min_rmv)
        return ;
    if (is_balanced(str))
    {
        if (step == 1 && *min_rmv > current_rmv)
                *min_rmv = current_rmv;
        else if (step == 2 && *min_rmv == current_rmv)
            {
                write(1, str, ft_strlen(str));
                write(1, "\n", 1);
                return;
            }
    }

    int len = ft_strlen(str);

    int i = pos;
    while (i < len) //u may do with str[i] as well
    {
        if (str[i] == '(' || str[i] == ')')
    {
        saved = str[i];
        str[i] = ' '; //not double quotation this is a char
        ft_rip(str, min_rmv, i + 1, current_rmv + 1, step);
        str[i] = saved;
    }
    i++;
    }
}

int main(int ac, char **av)
{
    if (ac != 2 || av[1][0] == '\0')
        return 1; 
    
        //you don't need the following
    // int len = ft_strlen(av[1]);
    // if (len <= 0 || !av[1] || av[1][0] == '\0')
    //     return 1;

    int i = 0;
    while (av[1][i])
    {
        if (av[1][i] != '(' && av[1][i] != ')')
            return 1;
        i++;
    }

    int min_rmv = ft_strlen(av[1]);

    ft_rip(av[1], &min_rmv, 0, 0, 1 );
    ft_rip(av[1], &min_rmv, 0, 0, 2);

    return 0;

}