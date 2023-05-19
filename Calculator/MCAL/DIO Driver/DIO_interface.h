/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  MCAL			******************/
/*****************		SWC:    DIO				******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_u8PIN_HIGH			1
#define DIO_u8PIN_LOW 			0

#define DIO_u8PORT_HIGH			0xff
#define DIO_u8PORT_LOW 			0

#define DIO_u8PORTA 			0
#define DIO_u8PORTB 			1
#define DIO_u8PORTC 			2
#define DIO_u8PORTD 			3

#define DIO_u8PIN0 				0
#define DIO_u8PIN1 				1
#define DIO_u8PIN2 				2
#define DIO_u8PIN3 				3
#define DIO_u8PIN4 				4
#define DIO_u8PIN5 				5
#define DIO_u8PIN6 				6
#define DIO_u8PIN7 				7

/*************************************DESCRIPTION****************************************/
/*
 1- To Enter your Port name you should enter DIO_u8PORTx (A,B,C,D)
 2- To Enter your Pin name you should enter DIO_u8PINx (0,1,2,3,4,5,6,7)
 3- To Enter your Port value you should enter DIO_u8PORT_HIGH or DIO_u8PORT_LOW
 4- To Enter your Pin value you should enter DIO_u8PIN_HIGH or DIO_u8PIN_LOW
 5- To get value of pin you should pass address of variable with port and pin to store the value in it
 */


u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_pu8Value);




#endif
