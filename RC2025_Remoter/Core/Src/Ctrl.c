#include "main.h"
#include "Ctrl.h"
#include "math.h"
#include "Calculate.h"
/* USER CODE BEGIN 1 */
short KNOB_L_FLAG,KNOB_R_FLAG;
int binary[4] ;
int highByte[6] ;
int lowByte[6] ;
uint8_t TXData[11]; 
int32_t LX,LY,RX,RY;
uint16_t ADC_Value[48]; 
uint8_t ADC1_Flag; 
int32_t INIT_data[4]={0};
uint32_t LXtemp, LYtemp, RXtemp, RYtemp;
uint32_t LXmax=4096,LXmin=0,LYmax=4096,LYmin=0,RXmax=4096,RXmin=0,RYmax=4096,RYmin=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_7)
	{
		switch(KNOB_L2){
			case 0: KNOB_L_FLAG=1;break;
			case 1: KNOB_L_FLAG=2;break;
		}
	}
	if(GPIO_Pin==GPIO_PIN_9)
	{
		switch(KNOB_R2){
			case 0: KNOB_L_FLAG=1;break;
			case 1: KNOB_L_FLAG=2;break;
		}
	}
}
/* USER CODE END 1 */

void Update_BOTTOM(void)
{
		static uint8_t current_bot=0;
	
		//PACK1
		if(BOTTOM_1==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_1_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_1_OFF;
		}
		
		if(BOTTOM_2==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_2_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_2_OFF;
		}

		if(BOTTOM_3==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_3_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_3_OFF;
		}

		if(BOTTOM_4==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_4_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_4_OFF;
		}

		if(BOTTOM_5==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_5_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_5_OFF;
		}

		if(BOTTOM_6==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_6_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_6_OFF;
		}

		if(BOTTOM_7==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_7_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_7_OFF;
		}

		if(BOTTOM_8==0)//A
		{		
				current_bot=1;
				TXData[BUTTON_PACKET] |= BOTTOM_8_ON;  
		}
		else
		{		
				current_bot=0;
				TXData[BUTTON_PACKET] &= BOTTOM_8_OFF;
		}


		//PACK2
		if(SWITCH_L==0)
		{
				 TXData[SWITCH_PACKET] |= SWITCH_L_ON;  
		}
		
		else
		{
				 TXData[SWITCH_PACKET] &= SWITCH_L_OFF;
		}
		
		if(SWITCH_R==0)//A
		{
				 TXData[SWITCH_PACKET] |= SWITCH_R_ON;  
		}
		else
		{
				 TXData[SWITCH_PACKET] &= SWITCH_R_OFF;
		}
		
		switch(KNOB_L_FLAG){
			case 0:TXData[SWITCH_PACKET] |= KNOB_L_NULL;break;
			case 1:TXData[SWITCH_PACKET] |= KNOB_L_UP;KNOB_L_FLAG=0;break;
			case 2:TXData[SWITCH_PACKET] &= KNOB_L_DOWN;KNOB_L_FLAG=0;break;
		}
		switch(KNOB_R_FLAG){
			case 0:TXData[SWITCH_PACKET] |= KNOB_R_NULL;break;
			case 1:TXData[SWITCH_PACKET] |= KNOB_R_UP;KNOB_L_FLAG=0;break;
			case 2:TXData[SWITCH_PACKET] &= KNOB_R_DOWN;KNOB_L_FLAG=0;break;
		}
}

void init_ADC_data()
{
	//标志位清零
	ADC1_Flag=0;  
	//读取ADC
	for(int i=0;i<BIT;)
	{
		LYtemp+=ADC_Value[i++];
		LXtemp+=ADC_Value[i++];
		RYtemp+=ADC_Value[i++];
		RXtemp+=ADC_Value[i++];
	}
	INIT_data[0]+=(LYtemp/=(BIT/NUM));
	INIT_data[1]+=(LXtemp/=(BIT/NUM));
	INIT_data[2]+=(RYtemp/=(BIT/NUM));
	INIT_data[3]+=(RXtemp/=(BIT/NUM));
}

void Update_ADC(void)
{
	//标志位清零
	ADC1_Flag=0;  
	//读取ADC
	for(int i=0;i<BIT;)
	{
		RXtemp+=ADC_Value[i++];
		LXtemp+=ADC_Value[i++];
		RYtemp+=ADC_Value[i++];
		LYtemp+=ADC_Value[i++];
	}
	//临时变量赋值
	LYtemp/=(BIT/NUM);
	LXtemp/=(BIT/NUM);
	RYtemp/=(BIT/NUM);
	RXtemp/=(BIT/NUM);
	
	//限幅
	if(LXtemp>LXmax) LXtemp=LXmax;
	if(LXtemp<LXmin) LXtemp=LXmin;
	if(LYtemp>LYmax) LYtemp=LYmax;
	if(LYtemp<LYmin) LYtemp=LYmin;
	if(RXtemp>RXmax) RXtemp=RXmax;
	if(RXtemp<RXmin) RXtemp=RXmin;
	if(RYtemp>RYmax) RYtemp=RYmax;
	if(RYtemp<RYmin) RYtemp=RYmin;
	//MAP
	LX=(int32_t)map( LXtemp, LXmin, LXmax, -32767, 32767 );
	LY=(int32_t)map( LYtemp, LYmin, LYmax, 32767, -32767 );
	RX=(int32_t)map( RXtemp, RXmin, RXmax, -32767, 32767 );
	RY=(int32_t)map( RYtemp, RYmin, RYmax, 32767, -32767 );
	
	//提取高八位和第八位
	// LX
	binary[0] = LX;  
	highByte[0] = (binary[0] >> 8) & 0xFF;  
	lowByte[0] = binary[0] & 0xFF;  
	// LY
	binary[1] = LY;  
	highByte[1] = (binary[1] >> 8) & 0xFF;  
	lowByte[1] = binary[1] & 0xFF;  
	// RX
	binary[2] = RX;  
	highByte[2] = (binary[2] >> 8) & 0xFF;  
	lowByte[2] = binary[2] & 0xFF;  
	// RY
	binary[3] = RY;  
	highByte[3] = (binary[3] >> 8) & 0xFF; 
	lowByte[3] = binary[3] & 0xFF; 
	
	//LX
	TXData[LX_LSB] =lowByte[0];
	TXData[LX_MSB] =highByte[0];
	//LY
	TXData[LY_LSB] =lowByte[1];
	TXData[LY_MSB] =highByte[1];
	//RX
	TXData[RX_LSB] =lowByte[2];
	TXData[RX_MSB] =highByte[2];
	//RY
	TXData[RY_LSB] =lowByte[3];
	TXData[RY_MSB] =highByte[3];

}
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
