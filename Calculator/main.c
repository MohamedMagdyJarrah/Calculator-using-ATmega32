#include "LIB/STD_TYPES.h"
#include "MCAL/PORT Driver/PORT_interface.h"
#include "MCAL/DIO Driver/DIO_interface.h"
#include "HAL/CLCD Driver/CLCD_interface.h"
#include "HAL/KEYPAD Driver/KPD_interface.h"

#include "util/delay.h"

void main(void)
{
	//Port Initialization
	PORT_voidInit();
	//CLCD Initialization
	CLCD_voidInit();
	u8 Local_u8ColumnIdx=0;
	//Keypad
	u8 Local_u8PressedKey;
	//Calculator
	u32 Local_u32FirstNum=0 , Local_u32SecondNum=0;
	u8 Local_u8Operator;
	u8 Local_u8NegativeResult =0;
	u16 fractionsmod[10] ={0,0,500,333,250,200,166,142,125,111};
	u8 Local_u8BodyGreeting[] = {0b00010100,0b00011110,0b00000101,0b00000100,0b00000100,0b00000100,0b00001010,0b00001010};
	u8 Local_u8Smile[] = {0b00000000,0b00000000,0b00001010,0b00000000,0b00010001,0b00001110,0b00000000,0b00000000};

	//---------------------------------Welcome!-------------------------------------
	CLCD_voidSendString("Welcome to");
	CLCD_u8GoToXY(1,0);
	CLCD_voidSendString("my Calculator");
	CLCD_u8GoToXY(0,15);
	CLCD_voidSendData('o');
	CLCD_voidWriteSpecialCharacter(Local_u8BodyGreeting,0,1,15);
	_delay_ms(3000);

	CLCD_voidClearDisplay();

	CLCD_voidSendString("Press Any button");
	CLCD_u8GoToXY(1,0);
	CLCD_voidSendString("to start");
	CLCD_voidWriteSpecialCharacter(Local_u8Smile,1,1,10);
	do
	{
		Local_u8PressedKey = KPD_u8GetPressedKey();
	}while(Local_u8PressedKey == 0xff);
	CLCD_voidClearDisplay();



	while(1)
	{

		//---------------------------------First Number-------------------------------------
		do
		{
			Local_u8PressedKey = KPD_u8GetPressedKey();
		}while(Local_u8PressedKey == 0xff);

		while (Local_u8PressedKey !='+' && Local_u8PressedKey !='-' && Local_u8PressedKey !='*' && Local_u8PressedKey !='/')
		{
			CLCD_voidWriteNumber(Local_u8PressedKey,0,Local_u8ColumnIdx,READ_FROM_LEFT);
			Local_u8ColumnIdx++;
			Local_u32FirstNum += Local_u8PressedKey;
			Local_u32FirstNum*=10;
			do
			{
				Local_u8PressedKey = KPD_u8GetPressedKey();
			}while(Local_u8PressedKey == 0xff);
		}
		Local_u32FirstNum/=10;



		//---------------------------------Operator-------------------------------------
		CLCD_u8GoToXY(0,Local_u8ColumnIdx);
		CLCD_voidSendData(Local_u8PressedKey);
		Local_u8Operator = Local_u8PressedKey;
		do
		{
			Local_u8PressedKey = KPD_u8GetPressedKey();
		}while(Local_u8PressedKey == 0xff);

		if (Local_u8PressedKey =='+' || Local_u8PressedKey =='-' || Local_u8PressedKey =='*' || Local_u8PressedKey =='/')
		{
			if (Local_u8PressedKey == '-' && Local_u8Operator == '+')
			{
				CLCD_voidSendData(Local_u8PressedKey);
				Local_u8ColumnIdx++;
				Local_u8Operator = '-';
				do
				{
					Local_u8PressedKey = KPD_u8GetPressedKey();
				}while(Local_u8PressedKey == 0xff);
			}
			else if (Local_u8PressedKey == '+' && Local_u8Operator == '-')
			{
				CLCD_voidSendData(Local_u8PressedKey);
				Local_u8ColumnIdx++;
				do
				{
					Local_u8PressedKey = KPD_u8GetPressedKey();
				}while(Local_u8PressedKey == 0xff);
			}
			else if ((Local_u8PressedKey == '-' && Local_u8Operator == '*') || (Local_u8PressedKey == '-' && Local_u8Operator == '/'))
			{
				Local_u8NegativeResult = 1;
				CLCD_voidSendData(Local_u8PressedKey);
				Local_u8ColumnIdx++;
				do
				{
					Local_u8PressedKey = KPD_u8GetPressedKey();
				}while(Local_u8PressedKey == 0xff);
			}
			else if(Local_u8PressedKey != Local_u8Operator)
			{
				CLCD_voidSendData(Local_u8PressedKey);
				CLCD_u8GoToXY(1,0);
				CLCD_voidSendString("Error Typing!!!");
				return;
			}
			else
			{
				while (Local_u8PressedKey == Local_u8Operator)
				{
					Local_u8ColumnIdx++;
					CLCD_voidSendData(Local_u8PressedKey);
					do
					{
						Local_u8PressedKey = KPD_u8GetPressedKey();
					}while(Local_u8PressedKey == 0xff);
				}
			}
		}
		Local_u8ColumnIdx++;



		//---------------------------------Second Number-------------------------------------

		while (Local_u8PressedKey !='+' && Local_u8PressedKey !='-' && Local_u8PressedKey !='*' && Local_u8PressedKey !='/' && Local_u8PressedKey !='=')
		{
			CLCD_voidWriteNumber(Local_u8PressedKey,0,Local_u8ColumnIdx,READ_FROM_LEFT);
			Local_u8ColumnIdx++;
			Local_u32SecondNum += Local_u8PressedKey;
			Local_u32SecondNum*=10;
			do
			{
				Local_u8PressedKey = KPD_u8GetPressedKey();
			}while(Local_u8PressedKey == 0xff);
		}
		Local_u32SecondNum/=10;


		while(Local_u8PressedKey !='=')
		{
			CLCD_u8GoToXY(1,0);
			CLCD_voidSendString("Please enter '='");
			do
			{
				Local_u8PressedKey = KPD_u8GetPressedKey();
			}while(Local_u8PressedKey == 0xff);
		}
		CLCD_u8GoToXY(1,0);
		CLCD_voidSendString("                ");

		//---------------------------------Result-------------------------------------
		CLCD_u8GoToXY(0,Local_u8ColumnIdx);
		CLCD_voidSendData(Local_u8PressedKey);
		Local_u8ColumnIdx++;

		switch(Local_u8Operator)
		{
		//Addition
		case '+':CLCD_voidWriteNumber(Local_u32FirstNum+Local_u32SecondNum,0,Local_u8ColumnIdx,READ_FROM_LEFT);break;

		//Subtraction
		case '-':
			if (Local_u32FirstNum >= Local_u32SecondNum)
			{
				CLCD_voidWriteNumber(Local_u32FirstNum-Local_u32SecondNum,0,Local_u8ColumnIdx,READ_FROM_LEFT);
			}
			else if(Local_u32FirstNum < Local_u32SecondNum)
			{
				CLCD_u8GoToXY(0,Local_u8ColumnIdx);
				CLCD_voidSendData('-');
				Local_u8ColumnIdx++;
				CLCD_voidWriteNumber(Local_u32SecondNum-Local_u32FirstNum,0,Local_u8ColumnIdx,READ_FROM_LEFT);
			}
			break;


			//Multiplication
		case '*':
			if (Local_u32FirstNum == 0 || Local_u32SecondNum == 0)
			{
				CLCD_voidWriteNumber(0,0,Local_u8ColumnIdx,READ_FROM_LEFT);
			}
			else
			{
				if (Local_u8NegativeResult == 1)
				{
					CLCD_u8GoToXY(0,Local_u8ColumnIdx);
					CLCD_voidSendData('-');
					Local_u8ColumnIdx++;
					CLCD_voidWriteNumber(Local_u32FirstNum*Local_u32SecondNum,0,Local_u8ColumnIdx,READ_FROM_LEFT);
				}
				else
				{
					CLCD_voidWriteNumber(Local_u32FirstNum*Local_u32SecondNum,0,Local_u8ColumnIdx,READ_FROM_LEFT);
				}
			}
			break;


			//Division
		case '/':
			if (Local_u32SecondNum == 0)
			{
				CLCD_u8GoToXY(1,0);
				CLCD_voidSendString("E:division by 0");
			}
			else
			{
				if (Local_u8NegativeResult == 1)
				{
					CLCD_u8GoToXY(0,Local_u8ColumnIdx);
					CLCD_voidSendData('-');
					Local_u8ColumnIdx++;
				}

				if ((Local_u32FirstNum%Local_u32SecondNum) == 0)
				{
					CLCD_voidWriteNumber(Local_u32FirstNum/Local_u32SecondNum,0,Local_u8ColumnIdx,READ_FROM_LEFT);
				}
				else
				{
					u8 mod = Local_u32FirstNum % Local_u32SecondNum;
					CLCD_voidWriteNumber(Local_u32FirstNum/Local_u32SecondNum,0,Local_u8ColumnIdx,READ_FROM_LEFT);
					Local_u8ColumnIdx++;
					CLCD_u8GoToXY(0,Local_u8ColumnIdx);
					CLCD_voidSendData('.');
					Local_u8ColumnIdx++;
					CLCD_voidWriteNumber(fractionsmod[Local_u32SecondNum]*mod,0,Local_u8ColumnIdx,READ_FROM_LEFT);
				}
			}
			break;
		}

		//To Try again
		CLCD_u8GoToXY(1,0);
		CLCD_voidSendString("Restart ? (+,-)");

		do
		{
			do
			{
				Local_u8PressedKey = KPD_u8GetPressedKey();
			}while(Local_u8PressedKey == 0xff);

		}while (Local_u8PressedKey != '+' && Local_u8PressedKey != '-');

		if (Local_u8PressedKey == '-')
		{
			CLCD_voidClearDisplay();
			CLCD_u8GoToXY(0,0);
			CLCD_voidSendString("Thanks for using");
			CLCD_u8GoToXY(1,0);
			CLCD_voidSendString("my Calculator");
			return;
		}
		CLCD_voidClearDisplay();
		Local_u8ColumnIdx = 0 , Local_u8NegativeResult = 0, Local_u32FirstNum=0 , Local_u32SecondNum=0;
	}
}


