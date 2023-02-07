/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************  Name   :Ahmed elshehry *******************/
/***************  Date   : 12/12/2021  **********************/
/***************  SWC    : SEVEN SEGMENT DISPLAY      **********************/
/*************** Version : 1.0        **********************/
/***************************************************************************************/

#include "DIO_interface.h"
#include "sevenseg_config.h"
#include "sevenseg_privat.h"
#include "DIO_interface.h"
#include"STD_TYPES.h"
static u8 seg [10]={ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE};

void Sev_voidDisplayNumber(u8 capy_u8_NumberDisplay)
{
	#if   COMMAN == COMENN_CATHODE

	FuncSev_valueDisplayNumber(SEV_SEG_PORT, ~seg[capy_u8_NumberDisplay]);
	
	#elif   COMMAN == COMENN_ANODE
	
	FuncSev_valueDisplayNumber(SEV_SEG_PORT, seg[capy_u8_NumberDisplay]);

	#else
		//#error "Worning to selection Type of seven segment display"
    #endif
}
