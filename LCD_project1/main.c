#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "LCD_interface.h"

#include "util/delay.h"

void GLOBAL_voidMoveLetter(u8 Copy_u8Letter);
void GLOBAL_voidMoveSinusoidal(void);
void GLOBAL_voidMoveSinusoidal2(void);
u8 GLOBAL_u8InverseLine(u8 Copy_u8Flag);
u8 GLOBAL_u8CheckNumbers(u8 Copy_u8Num);

void main(void)
{
//	LCD Pins Direction Initialisation
//	DIO_u8SetPortDirection(DIO_u8_PORTA, DIO_u8_PORT_OUTPUT);
//	DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN0, DIO_u8_PIN_OUTPUT);
//	DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN1, DIO_u8_PIN_OUTPUT);
//	DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN2, DIO_u8_PIN_OUTPUT);

	PORT_voidInit();
	LCD_voidInit();

//	LCD_voidSendData('O');
//	LCD_voidSendData('M');
//	LCD_voidSendData('A');
//	LCD_voidSendData('R');
//	LCD_voidWriteString("OMAR");
//	LCD_voidWriteString(" HASSAN");
//	LCD_voidWriteNumber(5020);
//	LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_FOURTH_COLUMN);
//	LCD_voidWriteString("OMAR");

	u8 Local_Pattern1[8] =
	{
			0b00000000,
			0b00001111,
			0b00010000,
			0b00010000,
			0b00011111,
			0b00000000,
			0b00000000
	};
	u8 Local_Pattern2[8] =
	{
			0b00000000,
			0b00001110,
			0b00010001,
			0b00010001,
			0b00011111,
			0b00000000,
			0b00000000
	};
	u8 Local_Pattern3[8] =
	{
			0b00000000,
			0b00000001,
			0b00000001,
			0b00000001,
			0b00000010,
			0b00000100,
			0b00001000
	};
//	LCD_voidWriteSpecialCharacter(Local_Pattern1, 1, 0, 10);
//	LCD_voidWriteSpecialCharacter(Local_Pattern2, 2, 0, 9);
//	LCD_voidWriteSpecialCharacter(Local_Pattern3, 3, 0, 8);

//	while(1)
//	{
//		GLOBAL_voidMoveLetter('O');
		GLOBAL_voidMoveSinusoidal2();
//	}
}

void GLOBAL_voidMoveLetter(u8 Copy_u8Letter)
{
	u8 Local_u8Iterator1, Local_u8Iterator2;
	for(Local_u8Iterator1 = 0; Local_u8Iterator1 < 2; Local_u8Iterator1++)
	{
		for(Local_u8Iterator2 = 0; Local_u8Iterator2 < 16; Local_u8Iterator2++)
		{
			LCD_voidGotoXY(Local_u8Iterator1, Local_u8Iterator2);
			LCD_voidSendData(Copy_u8Letter);
			_delay_ms(200);
			LCD_voidSendCommand(LCD_CLEAR);
		}
	}
}

void GLOBAL_voidMoveSinusoidal(void)
{
	u8* Local_u8Name = "OMAR";
	u8 Local_u8Iterator = 0, Local_u8X = 0 , Local_u8Y = 0, Local_u8Counter = 0;
	while(1)
	{
		if(Local_u8X > 1)	{Local_u8X = 0;}
		if(Local_u8Y > 12)	{Local_u8Y = 0;}

		for(Local_u8Iterator = 0; Local_u8Name[Local_u8Iterator] != '\0'; Local_u8Iterator++)
		{
			LCD_voidGotoXY(Local_u8X, Local_u8Y);
			LCD_voidSendData(Local_u8Name[Local_u8Iterator]);
			_delay_ms(300);
			Local_u8Y++;
		}
		LCD_voidSendCommand(LCD_CLEAR);

		Local_u8X++;
	}
}

void GLOBAL_voidMoveSinusoidal2(void)
{
	u8* Local_u8Name = "OMAR";
	u8 Local_u8Iterator = 0, Local_u8X = 0 , Local_u8Y = 0, Local_u8Counter = 0;
	u8 Local_u8Y2 = 0, Local_u8StringSize = 4, Local_u8Inverse = 0, Local_u8InverseFlag = 0;
	while(1)
	{
		if(Local_u8Y > 15)
		{
			Local_u8Y = 0;
			Local_u8StringSize = 4;
			Local_u8Inverse = GLOBAL_u8InverseLine(Local_u8X);
			Local_u8X = Local_u8Inverse;
		}
		if(Local_u8Y > Local_u8StringSize)	{Local_u8StringSize += 4;}

		if(Local_u8InverseFlag == 1)
		{
			if(!GLOBAL_u8CheckNumbers(Local_u8Y))
			{
				Local_u8Inverse = GLOBAL_u8InverseLine(Local_u8X);
				Local_u8X = Local_u8Inverse;
				Local_u8InverseFlag = 0;
			}
		}

		Local_u8Counter = 0;
		Local_u8Y2 = Local_u8Y;

		for(Local_u8Iterator = 0; Local_u8Name[Local_u8Iterator] != '\0'; Local_u8Iterator++)
		{
			if(Local_u8StringSize - Local_u8Counter == Local_u8Y)
			{
				if(Local_u8Y > 12)	{Local_u8Y2 = 0;}
				Local_u8Inverse = GLOBAL_u8InverseLine(Local_u8X);
				Local_u8X = Local_u8Inverse;
				Local_u8InverseFlag = 1;
			}
			LCD_voidGotoXY(Local_u8X, Local_u8Y2);
			LCD_voidSendData(Local_u8Name[Local_u8Iterator]);
			_delay_ms(500);
			Local_u8Y2++;
			Local_u8Counter++;
		}
		LCD_voidSendCommand(LCD_CLEAR);

		Local_u8Y++;
	}
}

u8 GLOBAL_u8InverseLine(u8 Copy_u8Flag)
{
	if(Copy_u8Flag == 0)	{return 1;}
	else	{return 0;}
}

u8 GLOBAL_u8CheckNumbers(u8 Copy_u8Num)
{
	if(Copy_u8Num == 5 || Copy_u8Num == 9 || Copy_u8Num == 13 || Copy_u8Num == 16)	{return 1;}
	else	{return 0;}
}

