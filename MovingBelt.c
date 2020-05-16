/*
*   MovingBelt
*
*   Definition of FSM function in C
*     c file
*/

#include "MovingBelt.h"

//start of custom code
extern bool output_updated,
            input_updated;

void waitForInputUpdate(){
    while(!input_updated){
        sleep(1);
    }
    input_updated = false;
}

//end of custom code

/*   (c) input/output signals */
bool fsm_MovingBelt(
  bool reset,              // reset of fsm
  PtrInVector_MovingBelt inV,         // input signals
  PtrOutVector_MovingBelt outV        // output signals
)
{
    /* state variable (static, inside step function   */
    static enum
    {
      idle, //
      Start_Move_Left, //
      Move_Left, //
      Start_Move_Right, //
      Move_Right, //
      init //
    } state;
    static bool initialized = false;   // enforce resetting!

    /* VARIABLES */
    static uint32_t vstamp; // x

    /* SET INITIAL STATE if requested */
    if (reset) {
        state = init;
        initialized = true;
        /* output of start-node */
        (outV->mL) = 0;
        (outV->mR) = 0;
        (outV->strT) = 0;
        (outV->stamp) = 0;
    }
    else if (initialized) {
        /* state transition function */
        //each non transient transition can only occur after the input has been changed, so the execution will wait for that
        switch(state)
        {
            case idle:
                vstamp = vstamp + 1; // variable assignment
                (outV->mL) = 0;
                (outV->mR) = 0;
                (outV->strT) = 0;
                (outV->stamp) = vstamp;
                waitForInputUpdate();
                if((inV->bl) && !(inV->limL))
                    state = Start_Move_Left;
                else if((inV->br) && !(inV->limR))
                    state = Start_Move_Right;
                break;
            case Start_Move_Left:
                vstamp = vstamp + 1; // variable assignment
                (outV->mL) = 1;
                (outV->mR) = 0;
                (outV->strT) = 1;
                (outV->stamp) = vstamp;
                if(1)
                    state = Move_Left;
                break;
            case Move_Left:
                vstamp = vstamp + 1; // variable assignment
                (outV->mL) = 1;
                (outV->mR) = 0;
                (outV->strT) = 0;
                (outV->stamp) = vstamp;
                waitForInputUpdate();
                if((inV->limL) || (inV->tmO))
                    state = idle;
                break;
            case Start_Move_Right:
                vstamp = vstamp + 1; // variable assignment
                (outV->mL) = 0;
                (outV->mR) = 1;
                (outV->strT) = 1;
                (outV->stamp) = vstamp;
                if(1)
                    state = Move_Right;
                break;
            case Move_Right:
                vstamp = vstamp + 1; // variable assignment
                (outV->mL) = 0;
                (outV->mR) = 1;
                (outV->strT) = 0;
                (outV->stamp) = vstamp;
                waitForInputUpdate();
                if((inV->limR) || (inV->tmO))
                    state = idle;
                break;
            case init:
                vstamp = vstamp + 1; // variable assignment
                (outV->mL) = 0;
                (outV->mR) = 0;
                (outV->strT) = 0;
                (outV->stamp) = 0;
                if(1)
                    state = idle;
                break;
            default: ;  // never reached
        }      // end of switch
    }         // end if (initialized)
    else ;    // nothing to do here

    /*   Output function    */
    /*switch (state) {
        case idle:


            break;
        case Start_Move_Left:

            break;
        case Move_Left:

            break;
        case Start_Move_Right:

            break;
        case Move_Right:

            break;
        case init:

            break;
        default: ;  // never reached
    }      // end of output switch
*/
//since vstamp increments every time the fsm executes and is part of the output, the output needs to be updated each time the fsm executes
    output_updated = true;
    return(initialized);
}  // end of fsm function

