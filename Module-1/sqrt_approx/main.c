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
	push {r1-r7}
	//Write your code here
	cmp r0, #1
	beq condition_1
	mov r1, r0 // Load R1 with the value of x
	ldr r2, =0xffffffff // c
	movs r3, #0 // done
	movs r4, #0 // c_old
	movs r6, #0 // a
	mov r7, r0 // b
done_check
	CMP r3, #1
	beq end_func
	b check_1
check_1
	CMP r2, r4
	beq end_func
	b code
code
	mov r4, r2 // c_old = c
	adds r5,r6,r7 // temp = a+b
	lsrs r2,r5,#1 // c = temp/2
	movs r5, #1
	muls r5, r2, r5
	muls r5, r2, r5
	cmps r5, r0
	beq end_func
	cmps r5, r0
	blt set_a
	mov r7, r2
	b done_check
set_a
	mov r6, r2
	b done_check

condition_1
		movs r2, #1
		b end_func
end_func
		mov r0, r2
		pop {r1-r7}
		bx lr
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
	r = my_sqrt(133); 	// should be 11
  for (i=0; i<10000; i++){
		r = my_sqrt(i);
    j+=r;
  }
	while(1)
		;
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************/
