#include <stdio.h>
#include <stdlib.h>
#include "MovingBelt.h"
#include <pthread.h>
#include <time.h>
#include <unistd.h>
//#include "MovingBelt_exec.c"

#define NUM_THREADS 3

InVector_MovingBelt inputVector;
OutVector_MovingBelt outputVector;
bool fsmReset,
     fsm_done,
     output_updated,
     input_updated,
     startTimer,
     exec,
     reset,
     timeElapsed;

void waitForOutputUpdate(){
    while(!output_updated){
        sleep(1);
    }
    output_updated = false;
}

void io(){
    uint64_t inputBuf,
             outputBuf;
    //system("gnome-terminal");
    //printf("test");
    while(1){
        //exec = readInput_MovingBelt( &reset, &inputVector);
       printf("Enter hexadecimal value for bl: ");
       scanf("%lx", &inputBuf);
       inputVector.bl = (bool)inputBuf;
       printf("Enter hexadecimal value for br: ");
       scanf("%lx", &inputBuf);
       inputVector.br = (bool)inputBuf;
       printf("Enter hexadecimal value for limL: ");
       scanf("%lx", &inputBuf);
       inputVector.limL = (bool)inputBuf;
       printf("Enter hexadecimal value for limR: ");
       scanf("%lx", &inputBuf);
       inputVector.limR = (bool)inputBuf;
       printf("Enter hexadecimal value for tmO: ");
       scanf("%lx", &inputBuf);
       inputVector.tmO = (bool)inputBuf;
       input_updated = true;

       if(output_updated){
            printf("\nActual output signal values of FSM");
            outputBuf = (__int64_t) (outputVector.mL);
            printf("\n  mL = %d ", outputBuf);
            outputBuf = (__int64_t) (outputVector.mR);
            printf("\n  mR = %d ", outputBuf);
            outputBuf = (__int64_t) (outputVector.strT);
            printf("\n  strT = %d ", outputBuf);
            outputBuf = (__int64_t) (outputVector.stamp);
            printf("\n  stamp = %d ", outputBuf);
            waitForOutputUpdate();
       }

    }
    //printf("Hello from input\n");
}

void fsmExecutor(){
    fsm_MovingBelt(true, &inputVector, &outputVector);
    while(1){
        fsm_MovingBelt(false, &inputVector, &outputVector);
    }
}


void timer(){
//system("gnome-terminal");
    printf("Hello from timer\n");
}

int main(){
    pthread_t threads[NUM_THREADS];
    size_t stacksize;
    int rc[NUM_THREADS];

    input_updated = false;
    output_updated = false;

    rc[0] = pthread_create(&threads[0], NULL, exec_fsm_MovingBelt, (void * )0);
    rc[1] = pthread_create(&threads[1], NULL, io, (void * )1);
    rc[2] = pthread_create(&threads[3], NULL, timer, (void * )3);

    if(rc[0]||rc[1]||rc[2]||rc[3]){
        printf("Error creating threads");
        return -1;
    }



    return 0;
}
