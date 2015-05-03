/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Lever_Pos_MPND.h
**     Project     : TX9BVA_SC4
**     Processor   : MC9S08SC4MTG
**     Component   : BitsIO
**     Version     : Component 02.108, Driver 03.28, CPU db: 3.00.003
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2015-05-03, 22:08, # CodeGen: 4
**     Abstract    :
**         This component "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This component is set to work in Output direction only.
**     Settings    :
**         Port name                   : PTB
**
**         Bit mask of the port        : $00F0
**         Number of bits/pins         : 4
**         Single bit numbers          : 0 to 3
**         Values range                : 0 to 15
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         Port data register          : PTBD      [$0002]
**         Port control register       : PTBDD     [$0003]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    8    |   PTB4_TPM2CH1
**                    1      |    7    |   PTB5_TPM1CH1
**                    2      |    6    |   PTB6_XTAL
**                    3      |    5    |   PTB7_EXTAL
**             ----------------------------------------------------
**
**         Optimization for            : speed
**     Contents    :
**         GetDir - bool Lever_Pos_MPND_GetDir(void);
**         GetVal - byte Lever_Pos_MPND_GetVal(void);
**         PutVal - void Lever_Pos_MPND_PutVal(byte Val);
**         GetBit - bool Lever_Pos_MPND_GetBit(byte Bit);
**         PutBit - void Lever_Pos_MPND_PutBit(byte Bit, bool Val);
**         SetBit - void Lever_Pos_MPND_SetBit(byte Bit);
**         ClrBit - void Lever_Pos_MPND_ClrBit(byte Bit);
**         NegBit - void Lever_Pos_MPND_NegBit(byte Bit);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Lever_Pos_MPND.h
** @version 03.28
** @brief
**         This component "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This component is set to work in Output direction only.
*/         
/*!
**  @addtogroup Lever_Pos_MPND_module Lever_Pos_MPND module documentation
**  @{
*/         

#ifndef Lever_Pos_MPND_H_
#define Lever_Pos_MPND_H_

/* MODULE Lever_Pos_MPND. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_GetVal (component BitsIO)
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pins and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---        - Input value (0 to 15)
** ===================================================================
*/
byte Lever_Pos_MPND_GetVal(void);

/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_PutVal (component BitsIO)
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val        - Output value (0 to 15)
**     Returns     : Nothing
** ===================================================================
*/
void Lever_Pos_MPND_PutVal(byte Val);

/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_GetBit (component BitsIO)
**     Description :
**         This method returns the specified bit of the input value.
**           a) direction = Input  : reads the input value from pins
**                                   and returns the specified bit
**           b) direction = Output : returns the specified bit
**                                   of the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to read (0 to 3)
**     Returns     :
**         ---        - Value of the specified bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
** ===================================================================
*/
bool Lever_Pos_MPND_GetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_PutBit (component BitsIO)
**     Description :
**         This method writes the new value to the specified bit
**         of the output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit (0 to 3)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void Lever_Pos_MPND_PutBit(byte Bit, bool Val);

/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_ClrBit (component BitsIO)
**     Description :
**         This method clears (sets to zero) the specified bit
**         of the output value.
**         [ It is the same as "PutBit(Bit,FALSE);" ]
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to clear (0 to 3)
**     Returns     : Nothing
** ===================================================================
*/
void Lever_Pos_MPND_ClrBit(byte Bit);

/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_SetBit (component BitsIO)
**     Description :
**         This method sets (sets to one) the specified bit of the
**         output value.
**         [ It is the same as "PutBit(Bit,TRUE);" ]
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to set (0 to 3)
**     Returns     : Nothing
** ===================================================================
*/
void Lever_Pos_MPND_SetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_NegBit (component BitsIO)
**     Description :
**         This method negates (inverts) the specified bit of the
**         output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to invert (0 to 31)
**     Returns     : Nothing
** ===================================================================
*/
void Lever_Pos_MPND_NegBit(byte Bit);

/*
** ===================================================================
**     Method      :  Lever_Pos_MPND_GetDir (component BitsIO)
**     Description :
**         This method returns direction of the component.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the component (always <true>, Output only)
**                      <false> = Input, <true> = Output
** ===================================================================
*/
#define Lever_Pos_MPND_GetDir() ( \
    (bool)1U                           /* Pins are fixed to GPO mode */ \
  )



/* END Lever_Pos_MPND. */
#endif /* #ifndef __Lever_Pos_MPND_H_ */
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