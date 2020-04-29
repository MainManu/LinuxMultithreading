/* 
*   MovingBelt
*
*   Definition of FSM function in C
*     c file
*/

#include "MovingBelt.h"

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
        switch(state)
        {
            case idle:
                vstamp = vstamp + 1; // variable assignment
                if((inV->bl) && !(inV->limL))
                    state = Start_Move_Left;
                else if((inV->br) && !(inV->limR))
                    state = Start_Move_Right;
                break;
            case Start_Move_Left:
                vstamp = vstamp + 1; // variable assignment
                if(1)
                    state = Move_Left;
                break;
            case Move_Left:
                vstamp = vstamp + 1; // variable assignment
                if((inV->limL) || (inV->tmO))
                    state = idle;
                break;
            case Start_Move_Right:
                vstamp = vstamp + 1; // variable assignment
                if(1)
                    state = Move_Right;
                break;
            case Move_Right:
                vstamp = vstamp + 1; // variable assignment
                if((inV->limR) || (inV->tmO))
                    state = idle;
                break;
            case init:
                vstamp = vstamp + 1; // variable assignment
                if(1)
                    state = idle;
                break;
            default: ;  // never reached
        }      // end of switch 
    }         // end if (initialized) 
    else ;    // nothing to do here

    /*   Output function    */
    switch (state) { 
        case idle:
            (outV->mL) = 0;
            (outV->mR) = 0;
            (outV->strT) = 0;
            (outV->stamp) = vstamp;
            break;
        case Start_Move_Left:
            (outV->mL) = 1;
            (outV->mR) = 0;
            (outV->strT) = 1;
            (outV->stamp) = vstamp;
            break;
        case Move_Left:
            (outV->mL) = 1;
            (outV->mR) = 0;
            (outV->strT) = 0;
            (outV->stamp) = vstamp;
            break;
        case Start_Move_Right:
            (outV->mL) = 0;
            (outV->mR) = 1;
            (outV->strT) = 1;
            (outV->stamp) = vstamp;
            break;
        case Move_Right:
            (outV->mL) = 0;
            (outV->mR) = 1;
            (outV->strT) = 0;
            (outV->stamp) = vstamp;
            break;
        case init:
            (outV->mL) = 0;
            (outV->mR) = 0;
            (outV->strT) = 0;
            (outV->stamp) = 0;
            break;
        default: ;  // never reached
    }      // end of output switch 

    return(initialized);
}  // end of fsm function 

