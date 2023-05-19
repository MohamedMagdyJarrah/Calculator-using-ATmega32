/*****************************************************************/
/*****************************************************************/
/*****************		Author: Mohamed Magdy	******************/
/*****************		Layer:  HAL				******************/
/*****************		SWC:   CLCD				******************/
/*****************		Version:1.00 			******************/
/*****************************************************************/
/*****************************************************************/

/*Preproccesor File guard*/
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define FOUR_BIT_MODE  			0
#define EIGHT_BIT_MODE  		1

/*For calculator to display the number in the most bottom right of the lcd */
#define READ_FROM_RIGHT			0
#define READ_FROM_LEFT			1

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidSendString(const char* Copy_pcString);

u8 CLCD_u8GoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos);

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNumber , u8 Copy_u8XPos, u8 Copy_u8YPos);

void CLCD_voidClearDisplay();

void CLCD_voidWriteNumber(u32 Copy_u32Number , u8 Copy_u8XPos, u8 Copy_u8YPos,u8 Copy_u8ReadingStyle);

void CLCD_voidSinWaveDisplay(const char* Copy_pu8Pattern);

#endif
