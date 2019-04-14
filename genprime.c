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

typedef enum {false, true} bool;

/******** Globals ********/
int N; /* a positive number */
int thread_count; 
bool* isPrime;
int* primeVals;
int primeValSize;
int lastNum;

/* Function declarations */
void parallel();

int main(int argc, char *argv[]){

    char output[100] = "";
    FILE * fp;

    if (argc != 3)
    {
        printf("Usage: ./genprime N t\n");
        exit(1);
    }
    //argv[1] is N
    //argv[2] is t
    N = strtol(argv[1], NULL, 10);
    thread_count = strtol(argv[2], NULL, 10);

    isPrime = (bool *) malloc(N * sizeof(bool));
    if (!isPrime)
    {
        printf("Can't allocate prime boolean array.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++)
        isPrime[i] = true;
    
    parallel();

    int thread_rank = omp_get_thread_num();
    if (thread_rank == 0)
    {
        sprintf(output, "%d.txt", N);
        fp = fopen(output, "w");
        if (!fp)
        {
            printf("Cannot create the file %s\n", output);
            exit(1);
        }
        for (int i = 2; i < primeValSize; i++)
            fprintf(fp, "%d %d\n", i, primeVals[i]);
        fclose(fp);
        exit(0);
    }

}

void parallel() 
{
    int current;
    lastNum = (N + 1) / 2 + 1;
    for (current = 2; current < lastNum; current++)
    {
        printf("%d\n", current);
        if (isPrime[current])
        {
            # pragma omp parallel num_threads(thread_count)
            {
                int i;
                # pragma omp parallel for
                for (i = current; i < N; i += current)
                    isPrime[i] = false;
            }

            primeVals[primeValSize] = current;
            primeValSize++;
        }
    }
}