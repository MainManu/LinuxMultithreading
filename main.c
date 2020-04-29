#include <stdio.h>
#include <stdlib.h>
#include "MovingBelt.h"
#include <pthread.h>
#include <time.h>
//#include "MovingBelt_exec.c"

#define NUM_THREADS 4

InVector_MovingBelt inputVector;
OutVector_MovingBelt outputVector;
bool fsmReset,
     startTimer,
     timeElapsed;



void inputReader(){
    printf("Hello from input\n");
}

void outputWriter(){
    printf("Hello from output\n");
}

void timer(){
    printf("Hello from timer\n");
}

int main(){
    pthread_t threads[NUM_THREADS];
    size_t stacksize;
    int i,
        rc[NUM_THREADS];

    rc[0] = pthread_create(&threads[0], NULL, exec_fsm_MovingBelt, (void * )0);
    rc[1] = pthread_create(&threads[1], NULL, inputReader, (void * )1);
    rc[2] = pthread_create(&threads[2], NULL, outputWriter, (void * )2);
    rc[3] = pthread_create(&threads[3], NULL, timer, (void * )3);

    if(rc[0]||rc[1]||rc[2]||rc[3]){
        printf("Error creating threads");
        return -1;
    }



    return 0;
}
