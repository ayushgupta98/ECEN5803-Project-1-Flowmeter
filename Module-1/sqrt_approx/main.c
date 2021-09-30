/************************************************************************//**
* \file main.c
* \brief LAB EXERCISE 5.2 - SQUARE ROOT APPROXIMATION
*
* Write an assembly code subroutine to approximate the square root of an 
* argument using the bisection method. All math is done with integers, so the 
* resulting square root will also be an integer
******************************************************************************
* GOOD LUCK!
 ****************************************************************************/

 #include "stdint.h"
 
 
 /** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
 #include "string.h"
 /** @endcond */
 
 /**
 * @brief 5863 Write a brief description of the function here
 *
 * Detailed description of the function after one line gap
 *
 * @note You can also add a note this way
 *
 * @param[in] 
 *  You can also start writing on a new line. 
 *  And continue on the next line. This is how you describe an input parameter
 *
 * @return
 *  This is how you describe the return value
 * 
 */
__asm int my_sqrt(int x){
		//Write your code here
		push{r1-r7}	//push R1-R7 registers on the stack
		movs r2, #0 // done=0
		movs r3, #0 // a=0
		movs r4, r0 // b = x
		movs r5, #0 //c_old = 0
		ldr r6, = 0xffffffff //c = -1
		b COND_1 //BRANCH to LABLE COND_1

COND_1
	cmp r7, #0 //COMPARE done with 0
	bne COND_2 //if done != 0 then BRANCH to COND_2
	beq END_FUN //if done == 0 then BRANCH to END_FUN
	
COND_2
	CMP r5, r6 //compare c_old and c
	bne LOOP_BODY //c_old != c then BRANCH to LOOP_BODY
	beq END_FUN //c_old == c then BRANCH to END_FUN
	
IF_BODY
	movs r2, #1 //done = 1
	b COND_1 //BRANCH to COND_1

ELSE_IF_BODY 
	movs r3, r6 //a = c
	b COND_1 //BRANCH to COND_1 
	
ELSE_BODY
	movs r4, r6 //b = c
	b COND_1 //BRANCH to COND_1

LOOP_BODY
	movs r5, r6 //c_old = c
	adds r7, r3, r4 //tmp = a+b
	lsrs r6, r7, #1 // c = tmp>>1
	movs r7, #1; // tmp = 1
	muls r7, r6, r7 //tmp = c*1 
	muls r7, r6, r7 //tmp = c*c
	cmp r7, r0 //tmp == x
	beq IF_BODY // if tmp == c then BRANCH to IF_BODY
	blt ELSE_IF_BODY // if tmp < c then BRANCH to ELSE_IF_BODY
	bgt ELSE_BODY // if tmp > c then BRANCH to ELSE_BODY
	
END_FUN
	movs r0, r6 //move value of c in r6
	pop{r1-r7} //pop r1-r7 from the stack
	bx lr //branch to the Link Register
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
 /**
 * @brief Main function
 *
 * Detailed description of the main
 */
int main(void){
	volatile int r, j=0;
	int i;
	             
  r = my_sqrt(0);     // should be 0
  r = my_sqrt(25);    // should be 5
  r = my_sqrt(133);   // should be 11
  r = my_sqrt(2);     // should be 1
  r = my_sqrt(4);     // should be 2
  r = my_sqrt(22);    // should be 4
  r = my_sqrt(121);   // should be 11
  for (i=0; i<10000; i++){
    r = my_sqrt(i);
    j+=r;
  }

	while(1)
		;
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************/
