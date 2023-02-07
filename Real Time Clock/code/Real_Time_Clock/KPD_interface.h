 /***********************************************************/
/***************  Name   : Ahmed Elshehry **********************/
/***************  Date   : 29/12/2021  **********************/
/***************  SWC    : Keypad       **********************/
/*************** Version : 1.0        **********************/
/***********************************************************/
#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

/*the function to get the buttom is pressed */
u8 KPD_u8GetKeyState(u8 * Copy_pu8ReturnedKey);

#define KPD_u8_KEY_NOT_PRESSED        0xff

#endif
