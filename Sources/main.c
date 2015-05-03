/* ###################################################################
**     Filename    : main.c
**     Project     : TX9BVA_SC4
**     Processor   : MC9S08SC4MTG
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2015-05-02, 12:06, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Signal_In.h"
#include "Lever_Pos_MPND.h"
#include "Lever_Pos_R.h"
#include "AD1.h"
#include "PWM_In.h"
#include "PWM_Timer.h"
#include "WDT.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "main.h"

byte PWM_Out_Duty_Lever=0, PWM_Out_Lever=0;				//Set the output PWM duty. Max 255, Min 0.
bool PWM_In_Captured = FALSE;							//Flags for PWM input captured.

byte Day_Mode=1;
byte Current_Duty_Cycle, Current_Levers;
byte Levers_Tmp[10]={0};
byte Levers_Tmp_Ptr=0;
byte Lever_Error_Count=0;

#define DAY_MODE_DUTY_CYCLE_LEVER 200					//Output duty cycle for levers day mode
#define NIGHT_MODE_DUTY_CYCLE_LEVER 40					//Output duty cycle for levers night mode

//Defines input & output bits pattern for levers.
#define IN_P 0b00000100				//4
#define IN_R 0b00000110				//6
#define IN_N 0b00000111				//7
#define IN_D 0b00000011				//3
#define IN_M 0b00000001				//1

/* Defined by HW schematic. Not aligned with real PCB design.
#define LeverP 0b10000
#define LeverR 0b01000
#define LeverN 0b00100
#define LeverD 0b00010
#define LeverM 0b00001
*/

//Below definitions aligned with real PCB.
#define LeverP 0b01000
#define LeverR 0b00001
#define LeverN 0b00100
#define LeverD 0b00010
#define LeverM 0b10000


void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  Check_RAM();
  
  (void) PWM_Timer_Enable();
  (void) PWM_In_Enable();

  //Main loop starts here.
  for(;;){
	  
	  Current_Levers = Get_Levers();
	  
//	  Current_Levers=LeverD;							//For debugging.
	  
	  if(Current_Levers == 0xFF){																//Wrong input signal combination detected.
		  /* Turn off all lever and backlight LEDs.*/
		  Set_Output(0, 0);
	  }else if(Day_Mode == 0){																
		  //PWM_In exists, night mode.
		  Set_Output(NIGHT_MODE_DUTY_CYCLE_LEVER, Current_Levers); 							//Night mode. PWM in MAX.
	  }else{															
		  //PWM_In not exists, day mode.
		  Set_Output(DAY_MODE_DUTY_CYCLE_LEVER, Current_Levers); 							//Day mode.
	  }
	  
	  (void) WDT_Clear();																		//Kick watch dog
	  
	  Cpu_Delay100US(10);									//Delay 1mS.
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */

void Set_Output(byte Lever_Duty_Cycle, byte Levers)
{
	PWM_Out_Duty_Lever = Lever_Duty_Cycle;
	PWM_Out_Lever = Levers;
}


byte Get_Levers(void)
{
	byte temp;
	byte i;
	byte Output;
	
	temp = Signal_In_GetVal();
	
	Levers_Tmp[Levers_Tmp_Ptr]=temp;
	Levers_Tmp_Ptr++;
	if(Levers_Tmp_Ptr>9)Levers_Tmp_Ptr=0;
	
	for(i=0;i<10;i++){
		if(Levers_Tmp[i]!=Levers_Tmp[0]){
			temp=0;
			break;
		}
		temp=1;
	}
	
	if(temp==0){
		Lever_Error_Count++;
		if(Lever_Error_Count>=15){
			Lever_Error_Count--;
			return 0xFF;							//Continuous Errors > 15, turn off all lever LEDs.
		}else{
			return Current_Levers;					//Error found but not reach 15. Keep last detection result.
		}
	}else{
		Lever_Error_Count=0;
		Output=Levers_Tmp[0];
	}
	
	switch(Output){
	case IN_P:
		return LeverP;
		break;
	case IN_R:
		return LeverR;
		break;
	case IN_N:
		return LeverN;
		break;
	case IN_D:
		return LeverD;
		break;
	case IN_M:
		return LeverM;
		break;
	default:
		return 0xFF;
	}
}


void Check_RAM(void)
{
/*
	byte PWM_Out_Duty_Lever=0, PWM_Out_Lever=0;				//Set the output PWM duty. Max 255, Min 0.
	bool PWM_In_Captured = FALSE;							//Flags for PWM input captured.

	byte Day_Mode=1;
	byte Current_Duty_Cycle, Current_Levers;
	byte Levers_Tmp[10]={0};
	byte Levers_Tmp_Ptr=0;
	byte Lever_Error_Count=0;
*/
	Check_RAM_Single(&PWM_Out_Duty_Lever);
	Check_RAM_Single(&PWM_Out_Lever);
	Check_RAM_Single(&PWM_In_Captured);
	Check_RAM_Single(&Day_Mode);
	Day_Mode=1;
	Check_RAM_Single(&Current_Duty_Cycle);
	Check_RAM_Single(&Current_Levers);
	Check_RAM_Single(&Levers_Tmp[0]);
	Check_RAM_Single(&Levers_Tmp[1]);
	Check_RAM_Single(&Levers_Tmp[2]);
	Check_RAM_Single(&Levers_Tmp[3]);
	Check_RAM_Single(&Levers_Tmp[4]);
	Check_RAM_Single(&Levers_Tmp[5]);
	Check_RAM_Single(&Levers_Tmp[6]);
	Check_RAM_Single(&Levers_Tmp[7]);
	Check_RAM_Single(&Levers_Tmp[8]);
	Check_RAM_Single(&Levers_Tmp[9]);
	Check_RAM_Single(&Levers_Tmp_Ptr);
	Check_RAM_Single(&Lever_Error_Count);
}

void Check_RAM_Single(byte * RAM_Byte)
{
	(* RAM_Byte)=0x55;
	while((* RAM_Byte)!=0x55);
	(* RAM_Byte)=0xAA;
	while((* RAM_Byte)!=0xAA);
	(* RAM_Byte)=0;
}


/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
