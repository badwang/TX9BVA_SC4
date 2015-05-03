/*
 * main.h
 *
 *  Created on: Dec 30, 2014
 *      Author: zhengdw
 */

#ifndef MAIN_H_
#define MAIN_H_

void Set_Output(byte Lever_Duty_Cycle, byte Levers);
byte Get_Levers(void);
void Check_RAM(void);
void Check_RAM_Single(byte * RAM_Byte);
#endif /* MAIN_H_ */
