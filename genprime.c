#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/*
 * Compile with: gcc -g -Wall -fopenmp -std=c99 -o genprime genprime.c
 * Run with ./genprime N t
 * N is a positive number bigger than 2 and less than 100,000
 * t is the number of threads, a positive integer that does not exceed 100
 * Output is N.txt
 * each line of N.txt is in the format a, b, c
 *  a: rank of the number (1 is the first prime on the list)
 *  b: the actual prime
 *  c: the interval from the previous prime (curr - prev)
 */

int main(int argc, char *argv[]){
    
    char* output[100] = "";
    FILE * fp;

    if (argc != 3)
    {
        printf("Usage: ./genprime N t\n");
        exit(1);
    }
    //argv[1] is N
    //argv[2] is t

    sprintf(output, "%d.txt", argv[1]);
    fp = fopen(output, "w");
    if (!fp)
    {
        printf("Cannot create the file %s\n", output);
        exit(1);
    }

    fclose(fp);
    exit(0);

}