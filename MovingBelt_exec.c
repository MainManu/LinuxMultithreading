/*
*   MovingBelt
*
*   example code for executing the FSM in C
*     exec c file
*/


/* For Simulation here a flag is used
   Outcomment next line with define of SIMULATION_MovingBelt if real operation */
#define SIMULATION_MovingBelt

#ifdef SIMULATION_MovingBelt
#include <ctype.h>
#include <stdio.h>
#endif

#include "MovingBelt.h"

extern InVector_MovingBelt inputVector;
extern OutVector_MovingBelt outputVector;

/*
  input function
   @param bool *reset     out   reset wanted
   @param InVector_MovingBelt *inV   out   input values
   @returns true, if not shutdown of fsm
*/
bool readInput_MovingBelt(bool *reset, InVector_MovingBelt *inV)
{
   bool end;
   uint64_t inputBuf;

   /* get information whether the FSM should be
      shut down (Variable end)
      resetted  (Parameter *reset)                           */
   // ### INSERT MANUALLY IF NOT SIMULATION FROM CONSOLE ###
#ifdef SIMULATION_MovingBelt
   char str[2];
   printf("\nFSM Stop (S,s), Reset (R,r) or Normal Step (N) (default N): ");
   scanf("%s", str);
   end = (toupper(str[0])=='S');
   if (end) return false;
   *reset = (toupper(str[0])=='R');
   // ### END PART FOR SIMULATION READING FSM Stop or Reset ###
#else
   if (end) return false;
#endif
   if (*reset) return true;
   /* read input-signals from device */
   // ### INSERT MANUALLY OTHER CODE IF NOT SIMULATION ###
   // inV->bl = XXX;
   // inV->br = XXX;
   // inV->limL = XXX;
   // inV->limR = XXX;
   // inV->tmO = XXX;
#ifdef SIMULATION_MovingBelt
   printf("Enter hexadecimal value for bl: ");
   scanf("%lx", &inputBuf);
   inV->bl = (bool)inputBuf;
   printf("Enter hexadecimal value for br: ");
   scanf("%lx", &inputBuf);
   inV->br = (bool)inputBuf;
   printf("Enter hexadecimal value for limL: ");
   scanf("%lx", &inputBuf);
   inV->limL = (bool)inputBuf;
   printf("Enter hexadecimal value for limR: ");
   scanf("%lx", &inputBuf);
   inV->limR = (bool)inputBuf;
   printf("Enter hexadecimal value for tmO: ");
   scanf("%lx", &inputBuf);
   inV->tmO = (bool)inputBuf;
#endif
   return true;
}; /* end input function */

/*
  output function
   @param OutVector *outV_MovingBelt   in   output values
*/
void writeOutput_MovingBelt(OutVector_MovingBelt *outV)
{
    __int64_t outputBuf;
    /* write output-signals to device */
    // ### INSERT MANUALLY ###
    // XXX = outV.mL;
    // XXX = outV.mR;
    // XXX = outV.strT;
    // XXX = outV.stamp;

#ifdef SIMULATION_MovingBelt
    printf("\nActual output signal values of FSM");
    outputBuf = (__int64_t) (outV->mL);
    printf("\n  mL = %d ", outputBuf);
    outputBuf = (__int64_t) (outV->mR);
    printf("\n  mR = %d ", outputBuf);
    outputBuf = (__int64_t) (outV->strT);
    printf("\n  strT = %d ", outputBuf);
    outputBuf = (__int64_t) (outV->stamp);
    printf("\n  stamp = %d ", outputBuf);
#endif
}    /* end of output function*/

/*
  exec function
*/
void exec_fsm_MovingBelt()
{
    /* Generation of input/ output vector */
    /*InVector_MovingBelt inV = {0};
    OutVector_MovingBelt outV = {0};*/
    //replaced with global variable to enable cross thread communication

    bool exec = false;
    bool reset = true;
    /* Initialisation  */
    exec = fsm_MovingBelt( true, &inputVector, &outputVector);
    writeOutput_MovingBelt(&outputVector);
    /* Example of execution LOOP */
    while(exec)
    {
        exec = readInput_MovingBelt( &reset, &inputVector);
        if (!exec) break;
        exec = fsm_MovingBelt( reset, &inputVector, &outputVector);
        writeOutput_MovingBelt(&outputVector);
        // ### INSERT OTHER STUFF HERE
        // ### NO WHILE LOOP OR UNCONTROLLED GETS, SCANF ETC.!!!
    } // end while loop of fsm
#ifdef SIMULATION_MovingBelt
    printf("\nEND OF SIMULATION OF FSM!!!");
#endif
}  /* end of exec function */
