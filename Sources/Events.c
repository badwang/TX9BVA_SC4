/* ###################################################################
**     Filename    : Events.c
**     Project     : TX9BVA_SC4
**     Processor   : MC9S08SC4MTG
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2015-05-02, 12:06, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "PE_Types.h"

static byte PWM_Int_Counter=0;
extern byte PWM_Out_Duty_Lever, PWM_Out_Lever, PWM_In_Captured, Day_Mode;


/*
** ===================================================================
**     Event       :  PWM_Timer_OnInterrupt (module Events)
**
**     Component   :  PWM_Timer [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PWM_Timer_OnInterrupt(void)
{
  /* Write your code here ... */
	
	if(PWM_Int_Counter >= PWM_Out_Duty_Lever){
//	if(PWM_Int_Counter >= 30){
		Lever_Pos_MPND_PutVal(0);
		Lever_Pos_R_PutVal(0);
	}else{
		Lever_Pos_MPND_PutVal((byte)PWM_Out_Lever>>1);
		Lever_Pos_R_PutVal(PWM_Out_Lever & 0x01);
	}

	PWM_Int_Counter++;
	
}

/*
** ===================================================================
**     Event       :  PWM_In_OnOverflow (module Events)
**
**     Component   :  PWM_In [Capture]
**     Description :
**         This event is called if counter overflows (only when the
**         component is enabled - <Enable> and the events are enabled -
**         <EnableEvent>.This event is available only if a <interrupt
**         service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PWM_In_OnOverflow(void)
{
  /* Write your code here ... */
	
	if(PWM_In_Captured || PWM_In_GetPinValue()){
		Day_Mode = 0;								//Set to night mode.
	}else{
		Day_Mode = 1;								//Set to day mode.
	}
	PWM_In_Captured = FALSE;
}


/*
** ===================================================================
**     Event       :  PWM_In_OnCapture (module Events)
**
**     Component   :  PWM_In [Capture]
**     Description :
**         This event is called on capturing of Timer/Counter actual
**         value (only when the component is enabled - <Enable> and the
**         events are enabled - <EnableEvent>.This event is available
**         only if a <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PWM_In_OnCapture(void)
{
  /* Write your code here ... */
	
	PWM_In_Captured = TRUE;
}



/*
** ===================================================================
**     Event       :  Cpu_OnSwINT (module Events)
**
**     Component   :  Cpu [MC9S08SC4_16]
**     Description :
**         This event is called when the SWI interrupt had occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Cpu_OnSwINT(void)
{
  /* Write your code here ... */
	
	/* Use infinite loop to trigger watchdog reset.*/
	for(;;);
}



/* END Events */

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


