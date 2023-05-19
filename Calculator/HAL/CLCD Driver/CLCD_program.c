/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:   CLCD				******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO Driver/DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"
#include <util/delay.h>

u8 Global_u8CurrentRaw =0 , Global_u8ReadingStyle = READ_FROM_LEFT;
s8  Global_u8CurrentColumn = 0;

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
#if CLCD_Mode == EIGHT_BIT_MODE
	/*Set RS LOW for Command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*Set RW LOW for Write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Put command in data port*/
	/*For 8-bit Mode*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	/*Put Enable pin high to show the data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(2);
	/*For 4-bit Mode*/
#elif CLCD_Mode == FOUR_BIT_MODE

	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN7,GET_BIT(Copy_u8Command,7));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN6,GET_BIT(Copy_u8Command,6));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN5,GET_BIT(Copy_u8Command,5));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN4,GET_BIT(Copy_u8Command,4));


	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Put Enable pin high to show the data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_us(1);

	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN7,GET_BIT(Copy_u8Command,3));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN6,GET_BIT(Copy_u8Command,2));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN5,GET_BIT(Copy_u8Command,1));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN4,GET_BIT(Copy_u8Command,0));
	/*Put Enable pin high to show the data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(2);
#endif
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
#if CLCD_Mode == EIGHT_BIT_MODE
	/*Set RS HIGH for Data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	/*Set RW LOW for Write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Put Data in data port*/
	/*For 8-bit Mode*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	/*Put Enable pin high to show the data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(2);
	/*For 4-bit Mode*/
#elif CLCD_Mode == FOUR_BIT_MODE
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN7,GET_BIT(Copy_u8Data,7));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN6,GET_BIT(Copy_u8Data,6));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN5,GET_BIT(Copy_u8Data,5));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN4,GET_BIT(Copy_u8Data,4));


	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Put Enable pin high to show the data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_us(1);

	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN7,GET_BIT(Copy_u8Data,3));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN6,GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN5,GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_DATA_PORT,DIO_u8PIN4,GET_BIT(Copy_u8Data,0));

	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(2);

#endif

	/*To continue displaying text in the second line if exceeds number of columns*/
	if (Global_u8ReadingStyle == READ_FROM_LEFT)
	{
		Global_u8CurrentColumn++;
		if (Global_u8CurrentColumn == 16)
		{
			if (Global_u8CurrentRaw == 0)
			{
				CLCD_u8GoToXY(Global_u8CurrentRaw+1,0);
			}
			else
			{
				CLCD_u8GoToXY(0,0);
			}
		}
	}
	else if (Global_u8ReadingStyle == READ_FROM_RIGHT)
	{
		Global_u8CurrentColumn--;
		if (Global_u8CurrentColumn == -1)
		{
			if (Global_u8CurrentRaw == 1)
			{
				CLCD_u8GoToXY(Global_u8CurrentRaw-1,15);
			}
			else
			{
				CLCD_u8GoToXY(1,15);
			}
		}
	}
}

void CLCD_voidInit(void)
{
#if CLCD_Mode == EIGHT_BIT_MODE
	/*Wait for more than 30ms */
	_delay_ms(40);
	/*For 8-bit Mode*/
	/*Function set command : :DL->1 for 8-bit mode and N->1 for two line display and F->0 for 5*8 font size.*/
	CLCD_voidSendCommand(0b00111000);

	/*Display ON/OFF Control :  D->1 for display enable and C->0 for cursor disable and B->0 for disable cursor blinking*/
	CLCD_voidSendCommand(0b00001100);

	/*Display Clear*/
	CLCD_voidSendCommand(1);
	/*For 4-bit Mode*/
#elif CLCD_Mode == FOUR_BIT_MODE
	_delay_ms(40);

	/*CLCD RESET Command*/
	CLCD_voidSendCommand(0x33);

	/*Function set command :DL->0 for 4-bit mode and N->1 for two line display and F->0 for 5*8 font size.*/
	CLCD_voidSendCommand(0x02);
	CLCD_voidSendCommand(0x28);

	/*Display ON/OFF Control :  D->1 for display enable and C->0 for cursor disable and B->0 for disable cursor blinking*/
	CLCD_voidSendCommand(0x0C);

	/*Display Clear*/
	CLCD_voidSendCommand(0x01);

	/*Entry Mode set: I/D->1 for Increase the DDRAM Address by 1 when code is written and SH->0 to disable shifting of CLCD Display*/
	CLCD_voidSendCommand(0x06);
#endif
}

void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;
	/*Sending the string to the CLCD*/
	while(Copy_pcString[Local_u8Counter] != NULL)
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

u8 CLCD_u8GoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	u8 Local_u8ErrorState = 0 , Local_u8Address;
	/*Go to the First line in CLCD at Specific Position (y)*/
	if (Copy_u8XPos == 0)
	{
		Local_u8Address = Copy_u8YPos;
	}
	/*Go to the Second line in CLCD at Specific Position (y)*/
	else if (Copy_u8XPos == 1)
	{
		Local_u8Address = Copy_u8YPos + 0x40;
	}
	else
	{
		Local_u8ErrorState = 1;
	}
	/*Set bit 7 in DDRAM Address command and send this command*/
	CLCD_voidSendCommand(Local_u8Address+128);

	Global_u8CurrentRaw = Copy_u8XPos;
	Global_u8CurrentColumn = Copy_u8YPos;

	return Local_u8ErrorState;
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNumber , u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress =0 , Local_u8Iterator =0 ;

	/*Calculate the Address of the block you will access in CGRAM*/
	Local_u8CGRAMAddress = Copy_u8PatternNumber*8;
	/*Send command that we will write in this CGRAM Address with setting bit 6 to 1*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);
	/*Putting the pattern in this in the CGRAM Address*/
	for(Local_u8Iterator=0 ; Local_u8Iterator<8 ; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}

	/*Choosing the place on the CLCD of the special character*/
	CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos);
	/*Display the Character on the CLCD  (DDRAM access the locations in CGRAM with blocks from 0 to 7*/
	CLCD_voidSendData(Copy_u8PatternNumber);

}

void CLCD_voidClearDisplay()
{
	CLCD_voidSendCommand(1);
}

void CLCD_voidWriteNumber(u32 Copy_u32Number , u8 Copy_u8XPos, u8 Copy_u8YPos ,u8 Copy_u8ReadingStyle)
{
	Global_u8ReadingStyle = Copy_u8ReadingStyle;
	if (Copy_u8ReadingStyle == READ_FROM_LEFT)
	{
		if(Copy_u32Number ==0)
		{
			CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos);
			CLCD_voidSendData(48);
		}
		else
		{
			u32 Local_u32ReversedNum = 0,Local_u8Reminder =0;
			/*Reverse the number first*/
			while(Copy_u32Number != 0)
			{
				Local_u8Reminder = Copy_u32Number%10;
				Copy_u32Number /= 10;
				Local_u32ReversedNum = Local_u8Reminder+Local_u32ReversedNum*10;
			}

			/*Choosing the Position of Printing the Number*/
			CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos);

			/*Display the number on the CLCD*/
			while(Local_u32ReversedNum != 0)
			{
				CLCD_voidSendData((Local_u32ReversedNum%10)+48);
				Local_u32ReversedNum /= 10;
			}
		}
	}
	/*I can make this function with I/D bit by clearing it to read the number in reverse order instead of reversing the number
	 * first then reading it*/
	else if (Copy_u8ReadingStyle == READ_FROM_RIGHT)
	{
		if(Copy_u32Number ==0)
		{
			CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos);
			CLCD_voidSendData(48);
		}
		else
		{
			/*Choosing the Position of Printing the Number*/
			CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos);

			/*Sending command which make I/D->0 to read it with reverse order*/
			CLCD_voidSendCommand(0x04);

			/*Reading the Number*/
			while(Copy_u32Number !=0)
			{
				CLCD_voidSendData((Copy_u32Number%10)+48);
				Copy_u32Number /=10;
			}
			/*Return back and make I/D->1 for incrementing the addresses for the DDRAM again*/
			CLCD_voidSendCommand(0x06);
		}
	}
	Global_u8ReadingStyle =READ_FROM_LEFT;
}

void CLCD_voidSinWaveDisplay(const char* Copy_pu8Pattern)
{
	u8 Local_u8Iterator=0 , row=0;
	for(Local_u8Iterator=0;Local_u8Iterator<16;Local_u8Iterator++)
	{
		CLCD_u8GoToXY(row,Local_u8Iterator);
		CLCD_voidSendString(Copy_pu8Pattern);
		_delay_ms(1000);
		CLCD_voidClearDisplay();
		row ^=1;
	}
}
