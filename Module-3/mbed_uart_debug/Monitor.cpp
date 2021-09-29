/**----------------------------------------------------------------------------
             \file Monitor.cpp
--                                                                           --
--              ECEN 5003 Mastering Embedded System Architecture             --
--                  Project 1 Module 3                                       --
--                Microcontroller Firmware                                   --
--                      Monitor.cpp                                            --
--                                                                           --
-------------------------------------------------------------------------------
--
--  Designed for:  University of Colorado at Boulder
--               
--                
--  Designed by:  Tim Scherr
--  Revised by:  Student's name 
-- 
-- Version: 2.0
-- Date of current revision:  2016-09-29   
-- Target Microcontroller: Freescale MKL25ZVMT4 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              Freescale FRDM-KL25Z Freedom Board
--               
-- 
   Functional Description: See below 
--
--      Copyright (c) 2015 Tim Scherr All rights reserved.
--
*/              

#include <stdio.h>
#include "shared.h"

extern float frequnecy;
extern float flow;
extern float temp;
const char* regs[16] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};

/*******************************************************************************
* Set Display Mode Function
* Function determines the correct display mode.  The 3 display modes operate as 
*   follows:
*
*  NORMAL MODE       Outputs only mode and state information changes   
*                     and calculated outputs
*
*  QUIET MODE        No Outputs
*
*  DEBUG MODE        Outputs mode and state information, error counts,
*                    register displays, sensor states, and calculated output
*
*
* There is deliberate delay in switching between modes to allow the RS-232 cable 
* to be plugged into the header without causing problems. 
*******************************************************************************/

void set_display_mode(void)   
{
  UART_direct_msg_put("\r\nCommands -  Desciption");
  UART_direct_msg_put("\r\nNOR - Normal");
  UART_direct_msg_put("\r\nQUI - Quiet");
  UART_direct_msg_put("\r\nDEB - Debug" );
  UART_direct_msg_put("\r\nV - Version#\r\n");
  UART_direct_msg_put("\r\n> ");
  
}


//*****************************************************************************/
/// \fn void chk_UART_msg(void) 
///
//*****************************************************************************/
void chk_UART_msg(void)    
{
   UCHAR j;
   while( UART_input() )      // becomes true only when a byte has been received
   {                                    // skip if no characters pending
      j = UART_get();                 // get next character

      if( j == '\r' )          // on a enter (return) key press
      {                // complete message (all messages end in carriage return)
         UART_msg_put("->");
         UART_msg_process();
      }
      else 
      {
         if ((j != 0x02) )         // if not ^B
         {                             // if not command, then   
            UART_put(j);              // echo the character   
         }
         else
         {
           ;
         }
         if( j == '\b' ) 
         {                             // backspace editor
            if( msg_buf_idx != 0) 
            {                       // if not 1st character then destructive 
               UART_msg_put(" \b");// backspace
               msg_buf_idx--;
            }
         }
				 if(j == 0x03)
				 {
					 display_timer = 0;
					 set_display_mode();
				 }
         else if( msg_buf_idx >= MSG_BUF_SIZE )  
         {                                // check message length too large
            UART_msg_put("\r\nToo Long!");
            msg_buf_idx = 0;
         }
         else if ((display_mode == QUIET) && (msg_buf[0] != 0x02) && 
                  (msg_buf[0] != 'D') && (msg_buf[0] != 'N') && 
                  (msg_buf[0] != 'V') &&
                  (msg_buf_idx != 0))
         {                          // if first character is bad in Quiet mode
            msg_buf_idx = 0;        // then start over
         }
         else {                        // not complete message, store character
 
            msg_buf[msg_buf_idx] = j;
            msg_buf_idx++;
            if (msg_buf_idx > 2)
            {
               UART_msg_process();
            }
         }
      }
   }
}

//*****************************************************************************/
///  \fn void UART_msg_process(void) 
///UART Input Message Processing
//*****************************************************************************/
void UART_msg_process(void)
{
   UCHAR chr,err=0;
//   unsigned char  data;


   if( (chr = msg_buf[0]) <= 0x60 ) 
   {      // Upper Case
      switch( chr ) 
      {
         case 'D':
            if((msg_buf[1] == 'E') && (msg_buf[2] == 'B') && (msg_buf_idx == 3)) 
            {
               display_mode = DEBUG;
               UART_msg_put("\r\nMode=DEBUG\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;

         case 'N':
            if((msg_buf[1] == 'O') && (msg_buf[2] == 'R') && (msg_buf_idx == 3)) 
            {
               display_mode = NORMAL;
               UART_msg_put("\r\nMode=NORMAL\n");
               //display_timer = 0;
            }
            else
               err = 1;
            break;

         case 'Q':
            if((msg_buf[1] == 'U') && (msg_buf[2] == 'I') && (msg_buf_idx == 3)) 
            {
               display_mode = QUIET;
               UART_msg_put("\r\nMode=QUIET\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;

         case 'V':
            display_mode = VERSION;
            UART_msg_put("\r\n");
            UART_msg_put( CODE_VERSION ); 
            UART_msg_put("\r\nSelect  ");
            display_timer = 0;
            break;
                
         default:
            err = 1;
      }
   }

   else 
   {                                 // Lower Case
      switch( chr ) 
      {
        default:
         err = 1;
      }
   }

   if( err == 1 )
   {
      UART_msg_put("\n\rError!");
   }   
   else if( err == 2 )
   {
      UART_msg_put("\n\rNot in DEBUG Mode!");
   }   
   else
   {
    msg_buf_idx = 0;          // put index to start of buffer for next message
      ;
   }
   msg_buf_idx = 0;          // put index to start of buffer for next message


}


//*****************************************************************************
///   \fn   is_hex
/// Function takes 
///  @param a single ASCII character and returns 
///  @return 1 if hex digit, 0 otherwise.
///    
//*****************************************************************************
UCHAR is_hex(UCHAR c)
{
   if( (((c |= 0x20) >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f'))  )
      return 1;
   return 0;
}

/*******************************************************************************
*   \fn  DEBUG and DIAGNOSTIC Mode UART Operation
*******************************************************************************/

__asm int getr0()
{
	bx lr
}

__asm int getr1()
{
	movs r0, r1
	bx lr
}

__asm int getr2()
{
	movs r0, r2
	bx lr
}
__asm int getr3()
{
	movs r0, r3
	bx lr
}
__asm int getr4()
{
	movs r0, r4
	bx lr
}
__asm int getr5()
{
	movs r0, r5
	bx lr
}
__asm int getr6()
{
	movs r0, r6
	bx lr
}

__asm int getr7()
{
	movs r0, r7
	bx lr
}

__asm int getr8()
{
	mov r0, r8
	bx lr
}

__asm int getr9()
{
	mov r0, r9
	bx lr
}
__asm int getr10()
{
	mov r0, r10
	bx lr
}

__asm int getr11()
{
	mov r0, r11
	bx lr
}
__asm int getr12()
{
	mov r0, r12
	bx lr
}
__asm int getr13()
{
	mov r0, r13
	bx lr
}
__asm int getr14()
{
	mov r0, r14
	bx lr
}
__asm int getr15()
{
	mov r0, r15
	bx lr
}
__asm int* read_stack()
{
	mov r0, r13
	bx lr
}

typedef struct
{
	const char *str;
	int (*func)(void);
}reg_set;

void monitor(void)
{
/**********************************/
/*     Initialize array           */
/**********************************/
	reg_set regs[16] = {
		{"r0 = 0x", getr0},
		{"r1 = 0x", getr1},
		{"r2 = 0x", getr2},
		{"r3 = 0x", getr3},
		{"r4 = 0x", getr4},
		{"r5 = 0x", getr5},
		{"r6 = 0x", getr6},
		{"r7 = 0x", getr7},
		{"r8 = 0x", getr8},
		{"r9 = 0x", getr9},
		{"r10 = 0x", getr10},
		{"r11 = 0x", getr11},
		{"r12 = 0x", getr12},
		{"r13 = 0x", getr13},
		{"r14 = 0x", getr14},
		{"r15 = 0x", getr15},
	};
	char str[20];

/**********************************/
/*     Spew outputs               */
/**********************************/
	
   switch(display_mode)
   {
      case(QUIET):
         {
             UART_msg_put("\r\n ");
             display_flag = 0;
         }  
         break;
      case(VERSION):
         {
             display_flag = 0;
         }  
         break;         
      case(NORMAL):
         {
            if (display_flag == 1)
            {
               UART_direct_msg_put("\r\nNORMAL ");
               UART_direct_msg_put(" Flow: ");
               // ECEN 5803 add code as indicated               
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Temp: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Freq: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               display_flag = 0;
            }
         }  
         break;
      case(DEBUG):
         {
            if (display_flag == 1)
            {
               UART_direct_msg_put("\r\nDEBUG");
               UART_direct_msg_put(" Flow: ");
               // ECEN 5803 add code as indicated               
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Temp: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Freq: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               
               
 /****************      ECEN 5803 add code as indicated   ***************/             
               //  Create a display of  error counts, sensor states, and
               //  ARM Registers R0-R15
							 UART_direct_msg_put("\r\nARM Registers\r\n");
               for(uint8_t i = 0; i < 16; i++)
							 {
								 uint32_t regptr = regs[i].func();
								 UART_direct_msg_put(regs[i].str);
								 UART_direct_hex_put((regptr>>24));
								 UART_direct_hex_put((regptr>>16));
								 UART_direct_hex_put((regptr>>8));
								 UART_direct_hex_put((regptr&0xFF));
								 UART_direct_msg_put("\r\n");
							 }
               //  Create a command to read a section of Memory and display it
							 
							 UART_direct_msg_put("\r\nRead memory section\r\n");
							 uint32_t start = 0, end = 0x10;
               uint32_t *mem_ptr = 0x00000000;
							 for(uint32_t i = start ; i < end; i++)
							 {
								 UART_direct_msg_put("\r\n0x");
								 UART_direct_hex_put(i);
								 UART_direct_msg_put(":      0x");
								 uint32_t regptr = (*(mem_ptr + i));
								 UART_direct_hex_put((regptr>>24));
								 UART_direct_hex_put((regptr>>16));
								 UART_direct_hex_put((regptr>>8));
								 UART_direct_hex_put((regptr&0xFF));
							 }
							 UART_direct_msg_put("\r\n");
               
               //  Create a command to read 16 words from the current stack 
               // and display it in reverse chronological order.
							 UART_direct_msg_put("\r\nPrint Stack\r\n");
							 uint32_t *reg_ptr = (uint32_t*)getr13();
							 for(uint8_t i = 0; i < 15; i++)
							 {
								 UART_direct_msg_put("\r\n0x");
								 UART_direct_hex_put(i);
								 UART_direct_msg_put(":      0x");
								 
								 uint32_t value = *reg_ptr;
								 UART_direct_hex_put((value>>24));
								 UART_direct_hex_put((value>>16));
								 UART_direct_hex_put((value>>8));
								 UART_direct_hex_put((value&0xFF));
								 reg_ptr--;
							 }
							 UART_direct_msg_put("\r\n");
              
               // clear flag to ISR      
               display_flag = 0;
             }   
         }  
         break;

      default:
      {
         UART_msg_put("Mode Error");
      }  
   }
}  
