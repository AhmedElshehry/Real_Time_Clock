/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************  Name   :Ahmed elshehry *******************/
/***************  Date   : 12/12/2021  **********************/
/***************  SWC    : LCD       **********************/
/*************** Version : 1.0        **********************/

/* Header files Inclusions	 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "DIO_Interface.h"
// lcd file 
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"
#include<util/delay.h>
#include <stdio.h>
/* Function: LCD_voidInit to confg the lcd at used the 8 pin of microcontre
 This Function initialize LCD	    */
void LCD_voidInit(void) {
	//Configure the direction of all control o/p
	// if not intialtion in DIO driver
//	DIO_u8SetPinDirection(LCD_u8_CTRL_PORT, LCD_u8_RSPIN, DIO_u8_OUTPUT);
//	DIO_u8SetPinDirection(LCD_u8_CTRL_PORT, LCD_u8_RWPIN, DIO_u8_OUTPUT);
//	DIO_u8SetPinDirection(LCD_u8_CTRL_PORT, LCD_u8_EPIN, DIO_u8_OUTPUT);

	//Configure the direction of data port
	DIO_u8SetPortDirection(LCD_u8_DATA_PORT, DIO_u8_OUTPUT);

	/*LCD Initialization*/
	/* Delay 35ms to ensure the initialization of the LCD driver */
	_delay_ms(35);
	/*Funcation set return cursor to first position on first line   that write commend 0b00111100 */
	LCD_voidSendInstruction(0b00111100);
	_delay_us(40); // delay need
	/*Display ON/OFF*/
	LCD_voidSendInstruction(0b00001111);
	_delay_us(40);
	/*Clear Display lcd*/
	LCD_voidSendInstruction(0b00000001);
	_delay_ms(2);
	/*Entry Mode Set*/
	LCD_voidSendInstruction(0b00000110);
	_delay_ms(2);
}

/* Function LCD_voidSendInstruction                     **/
/* This Function Send a command  to LCD			       	**/
void LCD_voidSendInstruction(u8 Copy_u8_command) {
	//RS = 0 (Command), RW = 0 (Write), E = 1 (Enable)
	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RSPIN, DIO_u8_LOW); //RS = 0 (Command)Set RS to LOW
//	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RWPIN, DIO_u8_LOW); //	RW = 0 (Write)Set R/W to LOW
	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_EPIN, DIO_u8_HIGH); //E = 1 (Enable)Set E to HIGH
	//001,DL(8-bit data),N(2-lines),F(5*10 dots)
	/* Load Command on Data bus */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8_command);

	/* Set E to LOW */
	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_EPIN, DIO_u8_HIGH);
	_delay_us(2);
	/* Set E to HIGH */
	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_EPIN, DIO_u8_LOW);
}

/*Function: LCD_voidWriteChar		                        				    **/
/*This Function writes a character "data" at  LCD	at  start frist address		**/

void LCD_voidWriteChar(u8 Copy_u8Data) {

	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RSPIN, DIO_u8_HIGH); //RS = 0 (Data)
	//DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RWPIN, DIO_u8_LOW); //RW = 0 (Write)
	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_EPIN, DIO_u8_HIGH); //E = 1 (Enable)

	/* Load Command on Data bus */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Data);

	//E =1
	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_EPIN, DIO_u8_HIGH);
	_delay_us(2);
	//E =0
	DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_EPIN, DIO_u8_LOW);
}
//Another Way
//* This Function writes a string "array of characters" on LCD		       	**/

//void LCD_voidWriteString(u8 *Copy_u8String, u8 Copy_u8Size)
//{
//	//String is an array of characters
//	for(u8 i=0; i<Copy_u8Size; i++)
//	{
//		LCD_voidWriteChar(Copy_u8String[i]);	//Write a char on each iteration
//	}
//}
//

void LCD_voidSendString(char *Copy_u8String) {
	u8 i = 0;
	while (Copy_u8String[i] != '\0') {
		LCD_voidWriteChar(Copy_u8String[i]);
		i++;
	}
}

/*********************************************************************************/
/* Function: LCD_voidGotoXY			                        				    **/
/* I/P Parameters: Copy_u8Row, Copy_u8Column				          		    **/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function Goes to a specific location (r,c) on LCD			       	**/
/*********************************************************************************/
/* Copy_u8Row Options: 1 - 2													**/
/* Copy_u8Column Options: 0 --> 15												**/
/*********************************************************************************/
void LCD_voidGotoXY(u8 Copy_u8Row, u8 Copy_u8Column) {
	if ((Copy_u8Row == 1) && (Copy_u8Column < 16))//Writing on Any grid resides on the 1st row
			{
		LCD_voidSendInstruction(0x80 + Copy_u8Column-1);//0x80 is the address of the 1st location in the 1st row
	} else if ((Copy_u8Row == 2) && (Copy_u8Column < 16))//Writing on Any grid resides on the 2nd row
			{
		LCD_voidSendInstruction(0xC0 + Copy_u8Column-1);//0xC0 is the address of the 1st location in the 1st row
	} else {
		//Do Nothing
	}
}

/* This Function Clears the whole LCD display						       	**/
void LCD_voidClearDisplay() {
	LCD_voidSendInstruction(0b00000001);//sending Instruction to clear the whole display
}

/*since the lcd is alpha Numeric print characters only*/
void LCD_IntToString(int integer, char *String)
{
	itoa(integer, String, 10);
}

/***********************************************************************************/
/* Function: LCD_voidWriteSpecialChar                        				      **/
/* I/P Parameters: *Copy_u8Pattern, Copy_u8PatternNumber ,Copy_u8Row,Copy_u8Column**/
/* Returns:it returns No thing                                				      **/
/* Desc:This Function writes a custom character on LCD					       	  **/
/***********************************************************************************/
/* Copy_u8Pattern Options: Character Pattern array								  **/
/* Copy_u8PatternNumber Options: Num of Pattern to be displayed					  **/
/* Copy_u8Row Options: 1 - 2													  **/
/* Copy_u8Column Options: 0 --> 15												  **/
/***********************************************************************************/
void LCD_voidWriteSpecialChar(u8 *Copy_u8Pattern, u8 Copy_u8PatternNumber,
		u8 Copy_u8Row, u8 Copy_u8Column) {
	/*Set CGRAM address */
	/*calculate the CGRAM address*/
	u8 Local_u8Adress = (Copy_u8PatternNumber * 8);
	LCD_voidSendInstruction(Local_u8Adress + 64);
	//   address    +64th bit

	/*save the pattern in CGRAM address */
	/* or Write data to CGRAM or DDRAM */
	for (u8 i = 0; i < 8; i++) {
		LCD_voidWriteChar(Copy_u8Pattern[i]);
		//the address counter counter AC will auto increment the next address
	}

	/*Set DDRAM Address */
	/*or go back to DDRAM to display the pattern*/
	LCD_voidGotoXY(Copy_u8Row, Copy_u8Column);

	/* Read data from CGRAM or DDRAM*/
	/*or display the pattern*/
	LCD_voidWriteChar(Copy_u8PatternNumber); //instead of ASCII letter in CGROM
}

void LCD_void_WriteNumber(u32 Copy_u32Number)
{
	u8 Local_u8Array[10];
	s8 Local_counter = 0;
		if (Copy_u32Number == 0)
		{
			LCD_voidWriteChar('0');
		}
		else
		{
			while (Copy_u32Number > 0)
			{
				Local_u8Array[Local_counter++]=((Copy_u32Number % 10) == 0) ? (48) : ((Copy_u32Number % 10) + 48);
				Copy_u32Number /= 10;
			}
			Local_counter--;
			while (Local_counter >= 0)
			{
				LCD_voidWriteChar(Local_u8Array[Local_counter]);
				Local_counter--;
			}
		}
}
