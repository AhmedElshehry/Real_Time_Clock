/*
 * mian.c
 *
 *  Created on: Jan 17, 2023
 *      Author: Ahmed Elshehry
 */
#include "DIO_interface.h"
#include"timer_interface.h"
#include "gi_interface.h"
#include"LCD_Interface.h"
#include"sevenseg_interface.h"
#include"KPD_interface.h"
#define F_CPU 8000000UL
#include<util/delay.h>
#define DELAY_TO_PARALLEL_SEVSG   7
void updata_TimeSecond(void);
void display_void_timeclock(void);
void GetSetting_Clock(u8 *capy_u16PtrArray,u8 capy_SizeArray);
void UpdataSetting_Clock(u8 *ptrcount_Second,u8 *ptrcount_Minutes,u8 *ptrcount_Hours,u8 *capy_u16PtrArray);
/*Global varible to set time clock */
volatile u8 count_Second=0;
u8 count_Hours=0,count_Minutes=0;

int main(void) {
	u8 cheek_pressed = KPD_u8_KEY_NOT_PRESSED;
	u8 Array[6]={'#','#','#','#','#','#'};
	DIO_voidInit();
	GI_interrupt_void_enable();
	TIMER_voidTimer0Init();
	TIMER_u8Timer0SetCallBackOCR(&updata_TimeSecond);
	LCD_voidInit();
	LCD_voidClearDisplay();
	LCD_voidSendString(" TO SET CLOCK ");
	LCD_voidGotoXY(2, 1);
	LCD_voidSendString(" PRESSED ---> 9 ");
	while (1) {
		KPD_u8GetKeyState(&cheek_pressed);
		if (cheek_pressed != KPD_u8_KEY_NOT_PRESSED) {
			if (cheek_pressed == '9') {
			    GetSetting_Clock(Array,6);
			    UpdataSetting_Clock(&count_Second,&count_Minutes,&count_Hours,Array);
			} else {
				LCD_voidClearDisplay();
				LCD_voidGotoXY(1, 0);
				LCD_voidSendString(" WORNG CHOIES ");
				_delay_ms(500);
				LCD_voidClearDisplay();
				LCD_voidGotoXY(1, 0);
				LCD_voidSendString(" TO SET CLOCK ");
				LCD_voidGotoXY(2, 0);
				LCD_voidSendString(" PRESSED ---> 9 ");
				_delay_ms(500);
			}
		}
		display_void_timeclock();
	}

	return 0;
}
/*call back function when ISR Happen */
void updata_TimeSecond(void)
{
	count_Second++;
}
void display_void_timeclock(void)
{
	for(int i=0;i<6;i++)
	{
		switch(i)
		{
		case 0:
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_HIGH);
		    Sev_voidDisplayNumber(count_Second%10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_LOW);
			break;
		case 1:
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_HIGH);
		    Sev_voidDisplayNumber(count_Second/10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_LOW);
			break;
		case 2:
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_HIGH);
		    Sev_voidDisplayNumber(count_Minutes%10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_LOW);
			break;
		case 3:
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_HIGH);
		    Sev_voidDisplayNumber(count_Minutes/10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_LOW);
			break;
		case 4:
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_HIGH);
		    Sev_voidDisplayNumber(count_Hours%10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_LOW);
			break;
		case 5:
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_HIGH);
		    Sev_voidDisplayNumber(count_Hours/10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_u8SetPinValue(DIO_u8_PORTD, i, DIO_u8_LOW);
			break;
		default:break;
		}
	}

//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN4, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0, DIO_u8_HIGH);
//    Sev_voidDisplayNumber(count_Second%10);
//	_delay_ms(DELAY_TO_PARALLEL_SEVSG);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN4, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1, DIO_u8_HIGH);
//    Sev_voidDisplayNumber(count_Second/10);
//	_delay_ms(DELAY_TO_PARALLEL_SEVSG);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN4, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2, DIO_u8_HIGH);
//    Sev_voidDisplayNumber(count_Minutes%10);
//	_delay_ms(DELAY_TO_PARALLEL_SEVSG);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN4, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3, DIO_u8_HIGH);
//    Sev_voidDisplayNumber(count_Minutes/10);
//	_delay_ms(DELAY_TO_PARALLEL_SEVSG);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN4, DIO_u8_HIGH);
//    Sev_voidDisplayNumber(count_Hours%10);
//	_delay_ms(DELAY_TO_PARALLEL_SEVSG);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN4, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3, DIO_u8_LOW);
//	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_HIGH);
//    Sev_voidDisplayNumber(count_Hours/10);
//	_delay_ms(DELAY_TO_PARALLEL_SEVSG);

	if(count_Second==60)
	{
		count_Second=0;
		count_Minutes++;
	}
	if(count_Minutes==60)
	{
		count_Minutes=0;
		count_Hours++;
	}
}
void GetSetting_Clock(u8 *capy_u16PtrArray,u8 capy_SizeArray)
{
	u8 local_counter=0;
	u8 local_pu8ReturnedKey=KPD_u8_KEY_NOT_PRESSED;
	LCD_voidClearDisplay();
	LCD_voidSendString(" Enter Hours=");
	_delay_ms(300);
	while(local_counter <=capy_SizeArray)
	{   /*recived clock from user */
		do{
            KPD_u8GetKeyState(&local_pu8ReturnedKey);
		}while (local_pu8ReturnedKey==KPD_u8_KEY_NOT_PRESSED);
		if((local_pu8ReturnedKey!=KPD_u8_KEY_NOT_PRESSED) && (local_pu8ReturnedKey!='A'))
		{
			capy_u16PtrArray[local_counter]=local_pu8ReturnedKey;
			LCD_voidWriteChar(capy_u16PtrArray[local_counter]);
		}
		if(local_counter==1)
		{
			LCD_voidClearDisplay();
			LCD_voidSendString(" Enter Minutes=");
			_delay_ms(500);
		}
		if(local_counter==3)
		{
			LCD_voidClearDisplay();
			LCD_voidSendString(" Enter Second=");
			_delay_ms(500);
		}
		if(local_counter==5)
		{
			LCD_voidClearDisplay();
			LCD_voidSendString("    THANK YOU  ");
			LCD_voidGotoXY(2, 0);
			LCD_voidSendString("    TO SETTING  ");
			_delay_ms(500);
		}
		if(local_pu8ReturnedKey=='A')
		{
			LCD_voidClearDisplay();
			LCD_voidSendString(" TO SET CLOCK ");
			LCD_voidGotoXY(2, 0);
			LCD_voidSendString(" PRESSED ---> 9 ");
			_delay_ms(500);
			break ; /* to out from while loop */
		}
		local_counter++;
	}
}
void UpdataSetting_Clock(u8 *ptrcount_Second,u8 *ptrcount_Minutes,u8 *ptrcount_Hours,u8 *capy_u16PtrArray)
{

   *ptrcount_Hours  = 10*(capy_u16PtrArray[0]-48)+(capy_u16PtrArray[1]-48);
   *ptrcount_Minutes= 10*(capy_u16PtrArray[2]-48)+(capy_u16PtrArray[3]-48);
   *ptrcount_Second = 10*(capy_u16PtrArray[4]-48)+(capy_u16PtrArray[5]-48);

}
