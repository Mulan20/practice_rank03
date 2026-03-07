//n-queens.c -> ./a.out <n of queens>
//Allowed functions : atoi, fprintf, write,
//  calloc, malloc, free, realloc, stdout, stderr

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

void print_result(int *board, int n)
{
      int i = 0;
     char str[12];
     int len;

    
     while (i < n)
    {
       len = sprintf(str, "%d", board[i]);
         write(1, str, len);
        if (i < n - 1)
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}

int is_checked(int *board, int col, int row)
{
    int i = 0;
    while (i < col)
    {
        if (board[i] == row || (abs(board[i] - row) == abs(i - col)))
            return 0;
        i++;
    }
    return 1;
}

void fill_board(int *board, int n, int col)
{
    int row;
    if (col == n)
    {
        print_result(board, n);
        return ;
    }

    row = 0;
    while (row < n)
    {
        if (is_checked(board, col, row))
        {
            board[col] = row;
            fill_board(board, n, col + 1);
        }
        row++;
    }
}

int main(int ac, char **av)
{
    int n; 
    int *board; 

    if (ac != 2 || av[1][0] == '\0')
    {
        fprintf(stderr, "Usage : %s <n of queens> \n", av[0]);
        return 1;
    }

    n = atoi(av[1]);
    if (n <= 0)
        return 0;

    //don't forget to malloc the board
    board = (int *)calloc(n, sizeof(int));
    if (!board)
    {
        fprintf(stderr, "allocation");
        return 1;
    }
    fill_board(board, n, 0);
    free(board);
    return 0;
}