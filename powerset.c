//powerset ./a.out 5 1 2 3 4 5

//allowed functions - atoi, printf, fprintf, malloc, 
// calloc, realloc, free, stdout,
//write

void print_result(int *subset, int size)
{
    //you don't need char str[12] for this one 
    // int i = 0;
    // char str[12];
    // int len;

    // //don't forget to check the size
    // if (size == 0)
    // {
    //     printf("\n");
    //     return ; 
    // }
    // while (i < size)
    // {
    //     len = sprintf(str, "%d", subset[i]);
    //     write(1, str, len);
    //     if (i < size - 1)
    //         write(1, " ", 1);
    //     i++;
    // }
    // write(1, "\n", 1);


    //the following simple version is ok!
    if (size == 0)
    {
        printf("\n");
        return;
    }
    
    int i = 0;
    while (i < size)
    {
        if (i == size - 1)
            printf("%d", subset[i]);
        else
            printf("%d ", subset[i]);
        i++;
    }
    printf("\n");
}



int check_args(int ac, char **av)
{
    int i = 1; //to not checek a.out
    while (i < ac)
    {
        j = 0; 
        while (av[i][j] == '-' || av[i][j] == '+')
            j++;

        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

void backtrack(int *set, int *subset, int setsize, int subset_size, int current_sum, int pos, int target, int *found)
{
    if (set_size == pos)
    {
        if (current_sum == target)
        {
            print_result(subset, subset_size);
            *found = 1;
        }
        return ; 
    }

    backtrack(set, subset, setsize, subset_size, current_sum, pos + 1, target, found);

    subset[subset_size] = set[pos];
    backtrack(set, subset, setsize, subset_size + 1, current_sum + set[pos], pos + 1, target, found);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {   printf("\n");
        return 1;
    }

    if (!check_args(ac, av))
    {
        return 1; 
    }

    int set_size = ac -2;
    int target = atoi(av[1]);
    if (set_size <= 0) //to check set_size not target
    {   write(1, "\n", 1);
        return 0;
    }

    int *set;
    int *subset;
    if (set_size <= 0)
        return 1; 

    set = (int *)malloc(set_size * sizeof(int));
    subset = (int *)malloc(set_size * sizeof(int));
    if (!set || !subset)
    {
        free(set);
        free(subset);
        return 1; 
    }
    int found = 0;

    //don't forget to push data to set
    int i = 0;
    int j = 0;
    while (j < ac)
    {
        set[i] = av[j];
        i++;
        j++;
    }
      backtrack(set, subset, set_size, 0, 0, 0, target, &found);
      if (!found)
      {
        write(1, "\n", 1);
        return 1;
      }
      free(set);
      free(subset);
      return 0;
}