/*
*   MovingBelt
*
*   Header for FSM implementation in C
*     h file
*/

#ifndef __cplusplus
#ifndef false
#define false 0
#define true 1
#endif
typedef int bool;
#endif

#ifndef byte
typedef unsigned char byte;
#endif

#ifndef __gtiTypes
#define __gtiTypes
typedef unsigned long long uint64_t;
typedef unsigned long int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
//typedef long long int64_t;
//typedef long int int32_t;
//typedef short int int16_t;
//typedef char int8_t;
#endif

/* SIGNAL TYPE */
/*   (a) input signal type */
typedef struct {
  bool bl; // Pushbutton move left
  bool br; // Pushbutton move right
  bool limL; // Limiter left side
  bool limR; // Limiter right side
  bool tmO; // timeOver
  } InVector_MovingBelt ;
typedef InVector_MovingBelt  *PtrInVector_MovingBelt ;
/*   (b) output signal type */
typedef struct {
  bool mL; // Motor moves left
  bool mR; // Motor moves right
  bool strT; // start Timer
  uint32_t stamp; // x
  } OutVector_MovingBelt;
typedef OutVector_MovingBelt *PtrOutVector_MovingBelt;

bool fsm_MovingBelt(
  bool reset,              // reset of fsm
  PtrInVector_MovingBelt inV,         // input signals
  PtrOutVector_MovingBelt outV        // output signals
);
void exec_fsm_MovingBelt();


