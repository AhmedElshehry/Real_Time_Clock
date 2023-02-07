/*******************************************/
/*************Name:Ahmed Elshehry ************/
/*************data 23/12/2021 ************/
/************* sw:globle interrupt   ************/
/*************version 1.0 ************/


#include "STD_TYPES.h"

#include "BIT_MATH.h"
#include "gi_interface.h"
#define SREG                                   *((volatile u8*) 0x5F)
void GI_interrupt_void_enable(void)
{
	SET_BIT(SREG ,7);
}

 



void GI_interrupt_void_disable(void){
	
	
	CLR_BIT(SREG,7);
}
