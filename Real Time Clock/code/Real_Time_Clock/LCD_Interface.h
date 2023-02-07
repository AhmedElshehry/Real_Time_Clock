/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************  Name   :Ahmed elshehry *******************/
/***************  Date   : 12/12/2021  **********************/
/***************  SWC    : LCD       **********************/
/*************** Version : 1.0        **********************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

/* Function: LCD_voidInit to confg the lcd at used the 8 pin of microcontre 	   */
/*This Function initialize LCD	                                                                   	    **/
void LCD_voidInit(void);

/* Function: LCD_voidSendInstruction                        				    **/
/* This Function Send a command "an instruction" to LCD to work			     **/
void LCD_voidSendInstruction(u8 Copy_u8instruction);

/* Function: LCD_voidWriteChar		                        				    **/
/*This Function writes a character "data" at  LCD	at  start frist address			       	**/
void LCD_voidWriteChar(u8 Copy_u8Data);

/* This Function writes a string "array of characters" on LCD		       	**/
//void LCD_voidWriteString(u8 *Copy_u8String, u8 Copy_u8Size);
void LCD_voidSendString(char *Copy_u8String);
/* This Function Clears the whole LCD display						       	**/
/*********************************************************************************/
void LCD_voidClearDisplay();
/*********************************************************************************/
/* Function: LCD_voidGotoXY			                        				    **/
/* I/P Parameters: Copy_u8Row, Copy_u8Column				          		    **/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function Goes to a specific location (r,c) on LCD			       	**/
/*********************************************************************************/
/* Copy_u8Row Options: 1 - 2													**/
/* Copy_u8Column Options: 0 --> 15												**/
/*********************************************************************************/
void LCD_voidGotoXY(u8 Copy_u8Row, u8 Copy_u8Column);


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
void LCD_voidWriteSpecialChar(u8 *Copy_u8Pattern, u8 Copy_u8PatternNumber ,u8 Copy_u8Row, u8 Copy_u8Column);

void LCD_IntToString(int integer,char *String);
void LCD_void_WriteNumber(u32 Copy_u32Number);
#endif
