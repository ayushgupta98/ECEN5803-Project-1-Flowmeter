/*
 ****************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *                                                                            
 *  Version:    C, Version 2.1
 *                                                                            
 *  File:       dhry_1.c (part 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 ****************************************************************************
 */

#include "dhry.h"
#include "mbed.h"
#include <time.h>


#define HZ  CLK_TCK

/* Global Variables: */

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];


// Add board's mbed support 
Timer           timer;
Serial          pc(USBTX, USBRX);

extern char     *malloc ();
//Enumeration     Func_1 ();
  /* forward declaration necessary since Enumeration may not simply be int */

#ifndef REG
        Boolean Reg = false;
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
        Boolean Reg = true;
#endif

/* variables for time measurement: */

#ifdef TIMES
//struct tms      time_info;
extern  int     times ();
                /* see library function "times" */
#define Too_Small_Time (2*HZ)
                /* Measurements should last at least about 2 seconds */
#endif
#ifdef TIME
extern long     time();
                /* see library function "time"  */
#define Too_Small_Time 2
                /* Measurements should last at least 2 seconds */
#endif
#ifdef MSC_CLOCK
//extern clock_t  clock();

#define Too_Small_Time (2*HZ)
#endif

long            Begin_Time,
                End_Time,
                User_Time;
float           Microseconds,
                Dhrystones_Per_Second;

/* end of variables for time measurement */
static void Proc_1 (REG Rec_Pointer  Ptr_Val_Par);
static void Proc_2 (One_Fifty   *Int_Par_Ref);
static void Proc_3 (Rec_Pointer *Ptr_Ref_Par);
static void Proc_4 (); 
static void Proc_5 ();

extern Boolean Func_2 (Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref);
extern void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par);
extern void Proc_7 (One_Fifty Int_1_Par_Val, One_Fifty Int_2_Par_Val, 
One_Fifty *Int_Par_Ref);
extern void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref, 
int Int_1_Par_Val, int Int_2_Par_Val);
extern Enumeration Func_1 (Capital_Letter Ch_1_Par_Val, 
Capital_Letter Ch_2_Par_Val);
extern Boolean Func_2 (Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref);
extern Boolean Func_3 (Enumeration Enum_Par_Val);





int main ()
/*****/

  /* main program, corresponds to procedures        */
  /* Main and Proc_0 in the Ada version             */
{
        One_Fifty       Int_1_Loc;
  REG   One_Fifty       Int_2_Loc;
        One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
        Enumeration     Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
  REG   int             Run_Index;
  REG   int             Number_Of_Runs;

  /* Initializations */
  pc.baud(115200);

  Next_Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));
  Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));

  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy (Ptr_Glob->variant.var_1.Str_Comp, 
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */

 
  pc.printf ("\r\nDhrystone Benchmark, Version 2.1 (Language: C)\n");
  pc.printf ("\n");
  if (Reg)
  {
    pc.printf ("\r\nProgram compiled with 'register' attribute\n");
    pc.printf ("\n");
  }
  else
  {
    pc.printf ("\r\nProgram compiled without 'register' attribute\n");
    pc.printf ("\n");
  }
  pc.printf ("\r\nPlease give the number of runs through the benchmark: ");
  {
    int n = 0;
    scanf ("%d", &n);
    Number_Of_Runs = n;
  }
  pc.printf ("\n");

  pc.printf ("\r\nExecution starts, %d runs through Dhrystone\n", Number_Of_Runs);

  /***************/
  /* Start timer */
  /***************/
 
#ifdef TIMES
  //times (&time_info);
//  Begin_Time = (long) time_info.tms_utime;
    timer.start();
#endif
#ifdef TIME
  Begin_Time = time ( (long *) 0);
#endif
#ifdef MSC_CLOCK
  Begin_Time = clock();
#endif

  for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
  {

    Proc_5();
    Proc_4();
      /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
    Int_1_Loc = 2;
    Int_2_Loc = 3;
    strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
    Enum_Loc = Ident_2;
    Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
      /* Bool_Glob == 1 */
    while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
    {
      Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
        /* Int_3_Loc == 7 */
      Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
        /* Int_3_Loc == 7 */
      Int_1_Loc += 1;
    } /* while */
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
      /* Int_Glob == 5 */
    Proc_1 (Ptr_Glob);
    for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
                             /* loop body executed twice */
    {
      if (Enum_Loc == Func_1 (Ch_Index, 'C'))
          /* then, not executed */
        {
        Proc_6 (Ident_1, &Enum_Loc);
        strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
        Int_2_Loc = Run_Index;
        Int_Glob = Run_Index;
        }
    }
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Int_2_Loc = Int_2_Loc * Int_1_Loc;
    Int_1_Loc = Int_2_Loc / Int_3_Loc;
    Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
      /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
    Proc_2 (&Int_1_Loc);
      /* Int_1_Loc == 5 */

  } /* loop "for Run_Index" */

  /**************/
  /* Stop timer */
  /**************/
  
#ifdef TIMES
  //times (&time_info);
//  End_Time = (long) time_info.tms_utime;
    timer.stop();
    End_Time = timer.read();
    timer.reset();
#endif
#ifdef TIME
  End_Time = time ( (long *) 0);
#endif
#ifdef MSC_CLOCK
  End_Time = clock();
#endif

  pc.printf ("\r\nExecution ends\n");
  pc.printf ("\n");
  pc.printf ("\r\nFinal values of the variables used in the benchmark:\n");
  pc.printf ("\n");
  pc.printf ("\r\nInt_Glob:            %d\n", Int_Glob);
  pc.printf ("\r\n        should be:   %d\n", 5);
  pc.printf ("\r\nBool_Glob:           %d\n", Bool_Glob);
  pc.printf ("\r\n        should be:   %d\n", 1);
  pc.printf ("\r\nCh_1_Glob:           %c\n", Ch_1_Glob);
  pc.printf ("\r\n        should be:   %c\n", 'A');
  pc.printf ("\r\nCh_2_Glob:           %c\n", Ch_2_Glob);
  pc.printf ("\r\n        should be:   %c\n", 'B');
  pc.printf ("\r\nArr_1_Glob[8]:       %d\n", Arr_1_Glob[8]);
  pc.printf ("\r\n        should be:   %d\n", 7);
  pc.printf ("\r\nArr_2_Glob[8][7]:    %d\n", Arr_2_Glob[8][7]);
  pc.printf ("\r\n        should be:   Number_Of_Runs + 10\n");
  pc.printf ("\r\nPtr_Glob->\n");
  pc.printf ("\r\n  Ptr_Comp:          %d\n", (int) Ptr_Glob->Ptr_Comp);
  pc.printf ("\r\n        should be:   (implementation-dependent)\n");
  pc.printf ("\r\n  Discr:             %d\n", Ptr_Glob->Discr);
  pc.printf ("\r\n        should be:   %d\n", 0);
  pc.printf ("\r\n  Enum_Comp:         %d\n", Ptr_Glob->variant.var_1.Enum_Comp);
  pc.printf ("\r\n        should be:   %d\n", 2);
  pc.printf ("\r\n  Int_Comp:          %d\n", Ptr_Glob->variant.var_1.Int_Comp);
  pc.printf ("\r\n        should be:   %d\n", 17);
  pc.printf ("\r\n  Str_Comp:          %s\n", Ptr_Glob->variant.var_1.Str_Comp);
  pc.printf ("\r\n        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  pc.printf ("\r\nNext_Ptr_Glob->\n");
  pc.printf ("\r\n  Ptr_Comp:          %d\n", (int) Next_Ptr_Glob->Ptr_Comp);
  pc.printf ("\r\n        should be:   (implementation-dependent), same as above\n");
  pc.printf ("\r\n  Discr:             %d\n", Next_Ptr_Glob->Discr);
  pc.printf ("\r\n        should be:   %d\n", 0);
  pc.printf ("\r\n  Enum_Comp:         %d\n", Next_Ptr_Glob->variant.var_1.Enum_Comp);
  pc.printf ("\r\n        should be:   %d\n", 1);
  pc.printf ("\r\n  Int_Comp:          %d\n", Next_Ptr_Glob->variant.var_1.Int_Comp);
  pc.printf ("\r\n        should be:   %d\n", 18);
  pc.printf ("\r\n  Str_Comp:          %s\n",
  Next_Ptr_Glob->variant.var_1.Str_Comp);
  pc.printf ("\r\n        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  pc.printf ("\r\nInt_1_Loc:           %d\n", Int_1_Loc);
  pc.printf ("\r\n        should be:   %d\n", 5);
  pc.printf ("\r\nInt_2_Loc:           %d\n", Int_2_Loc);
  pc.printf ("\r\n        should be:   %d\n", 13);
  pc.printf ("\r\nInt_3_Loc:           %d\n", Int_3_Loc);
  pc.printf ("\r\n        should be:   %d\n", 7);
  pc.printf ("\r\nEnum_Loc:            %d\n", Enum_Loc);
  pc.printf ("\r\n        should be:   %d\n", 1);
  pc.printf ("\r\nStr_1_Loc:           %s\n", Str_1_Loc);
  pc.printf ("\r\n        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n");
  pc.printf ("\r\nStr_2_Loc:           %s\n", Str_2_Loc);
  pc.printf ("\r\n        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n");
  pc.printf ("\n");

  User_Time = End_Time - Begin_Time;

  if (User_Time < Too_Small_Time)
  {
        pc.printf ("\r\nEnd_Time = %ld\n",End_Time);
        pc.printf ("\r\nBegin_Time = %ld\n",Begin_Time);
        pc.printf ("\r\nUser_Time = %ld\n",User_Time);
        pc.printf ("\r\nToo_Small_Time = %ld\n",Too_Small_Time);
    pc.printf ("\r\nMeasured time too small to obtain meaningful results\n");
    pc.printf ("\r\nPlease increase number of runs\n");
    pc.printf ("\n");
  }
  else
  {
#ifdef TIME
    Microseconds = (float) User_Time * Mic_secs_Per_Second 
                        / (float) Number_Of_Runs;
    Dhrystones_Per_Second = (float) Number_Of_Runs / (float) User_Time;
#else
    Microseconds = (float) User_Time * Mic_secs_Per_Second 
                        / ((float) HZ * ((float) Number_Of_Runs));
    Dhrystones_Per_Second = ((float) HZ * (float) Number_Of_Runs)
                        / (float) User_Time;
#endif
    pc.printf ("\r\nMicroseconds for one run through Dhrystone: ");
    pc.printf ("\r\n%6.1f \n", Microseconds);
    pc.printf ("\r\nDhrystones per Second:                      ");
    pc.printf ("\r\n%6.1f \n", Dhrystones_Per_Second);
    pc.printf ("\n");
  }
  return 0;
}

static void Proc_1 (REG Rec_Pointer  Ptr_Val_Par)
/******************/
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;  
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */
  
  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob); 
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp 
        = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp 
                        == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp, 
           &Next_Record->variant.var_1.Enum_Comp);
    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10, 
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */



//Proc_1 (Ptr_Val_Par)
///******************/
//
//REG Rec_Pointer Ptr_Val_Par;
//    /* executed once */
//{
//  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;  
//                                        /* == Ptr_Glob_Next */
//  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
//  /* corresponds to "rename" in Ada, "with" in Pascal           */
//  
//  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob); 
//  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
//  Next_Record->variant.var_1.Int_Comp 
//        = Ptr_Val_Par->variant.var_1.Int_Comp;
//  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
//  Proc_3 (&Next_Record->Ptr_Comp);
//    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp 
//                        == Ptr_Glob->Ptr_Comp */
//  if (Next_Record->Discr == Ident_1)
//    /* then, executed */
//  {
//    Next_Record->variant.var_1.Int_Comp = 6;
//    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp, 
//           &Next_Record->variant.var_1.Enum_Comp);
//    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
//    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10, 
//           &Next_Record->variant.var_1.Int_Comp);
//  }
//  else /* not executed */
//    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
//} /* Proc_1 */
//
//





static void Proc_2 (One_Fifty   *Int_Par_Ref)
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */
{
  One_Fifty  Int_Loc;  
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */



//Proc_2 (Int_Par_Ref)
///******************/
//    /* executed once */
//    /* *Int_Par_Ref == 1, becomes 4 */
//
//One_Fifty   *Int_Par_Ref;
//{
//  One_Fifty  Int_Loc;  
//  Enumeration   Enum_Loc;
//
//  Int_Loc = *Int_Par_Ref + 10;
//  do /* executed once */
//    if (Ch_1_Glob == 'A')
//      /* then, executed */
//    {
//      Int_Loc -= 1;
//      *Int_Par_Ref = Int_Loc - Int_Glob;
//      Enum_Loc = Ident_1;
//    } /* if */
//  while (Enum_Loc != Ident_1); /* true */
//} /* Proc_2 */


static void Proc_3 (Rec_Pointer *Ptr_Ref_Par)
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */
{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */




//Proc_3 (Ptr_Ref_Par)
///******************/
//    /* executed once */
//    /* Ptr_Ref_Par becomes Ptr_Glob */
//
//Rec_Pointer *Ptr_Ref_Par;
//
//{
//  if (Ptr_Glob != Null)
//    /* then, executed */
//    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
//  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
//} /* Proc_3 */
//

static void Proc_4 () /* without parameters */
/*******/
    /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = Ch_1_Glob == 'A';
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */



//Proc_4 () /* without parameters */
///*******/
//    /* executed once */
//{
//  Boolean Bool_Loc;
//
//  Bool_Loc = Ch_1_Glob == 'A';
//  Bool_Glob = Bool_Loc | Bool_Glob;
//  Ch_2_Glob = 'B';
//} /* Proc_4 */

static void Proc_5 () /* without parameters */
/*******/
    /* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */


//Proc_5 () /* without parameters */
///*******/
//    /* executed once */
//{
//  Ch_1_Glob = 'A';
//  Bool_Glob = false;
//} /* Proc_5 */


        /* Procedure for the assignment of structures,          */
        /* if the C compiler doesn't support this feature       */
#ifdef  NOSTRUCTASSIGN
memcpy (d, s, l)
register char   *d;
register char   *s;
register int    l;
{
        while (l--) *d++ = *s++;
}
#endif

