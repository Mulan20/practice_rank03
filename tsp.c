//tsp -> you will get a text file with coordinates and then you will print out the shortest possible route

//Allowed functions: write, sqrtf, getline, fseek, fscanf, ferror, feof,
//fabsf, memcpy, fprintf, fclose, malloc, calloc, realloc, free, fopen,
//errno, stderr, stdin, stdout

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <float.h>
#include <math.h>

typedef struct
{
    float x, y;
}   City;

void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

float cal_distance(City a, City b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return (sqrtf((dx * dx) + (dy * dy)));
}

float cal_total(City *cities, int *path, int n)
{
    int i = 0;
    float total = 0.0f; //not 0.00 but 0.0f
    while (i < n - 1)
    {
        total += cal_distance(cities[path[i]], cities[path[i + 1]]);
        i++; //don't forget incrementation
    }
    total += cal_distance(cities[path[n - 1]], cities[path[0]]);

    return total;
}
void find_shortest_path(City *cities, int *path, int index, int *min_distance, int n)
{
    if (index == n)
    {
        float total_len = cal_total(cities, path, n);
        if (total_len < *min_distance)
        {
            *min_distance = total_len;
            //*found = 1; you don't need this 
        }
        return;
    }

    int i = pos;
    while (i < n)
    {
        //don't forget &
        swap(&path[pos], &path[i]);
        find_shortest_path(cities, path, index + 1, min_distance, n);
        swap(&path[pos], &path[i]);
        i++;
    }
}

int main(void) //you don't need to read from the user input but the fiel
{
    int n = 0; //don't forget to set 0
    City cities[12];

    while (n < 11 && (fscanf(stdin, "%f, %f", &cities[n].x, &cities[n].y) == 2)) //don't forget &
        n++;

    if (n < 2)
    {
        //write(1, "\n", 1);
        printf("0.00\n"); 
        return 1;
    }

    int path[12];
    for (int i = 0; i < n; i++)
        path[i] = i;
    float min_distance = FLT_MAX; //this should be float 
   // int found = 0; // you don't need this 
    find_shortest_path(cities, path, 1, &min_distance, n); //start form position 1. 
    // if (found != 1)
    //     return 1;
    printf("%.2f\n", min_distance); //it should be %.2f\n not %d
    return 0;
}