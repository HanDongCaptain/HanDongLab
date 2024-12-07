#ifndef __Ctrl_H__
#define __Ctrl_H__

#include <stdint.h>
#include "main.h"

#define BIT 48
//通道数
#define NUM 7



#define LX_LSB               0
#define LX_MSB               1
#define LY_LSB               2
#define LY_MSB               3
#define RX_LSB               4
#define RX_MSB               5
#define RY_LSB               6
#define RY_MSB               7
//#define	LP_LSB               8
//#define	LP_MSB               9
//#define	RP_LSB               10
//#define	RP_MSB               11
#define BUTTON_PACKET     	 8
#define SWITCH_PACKET     	 9
//#define KNOB_PACKET       10
//#define SCREEN_DATA          14


#define BOTTOM_1   HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)
#define BOTTOM_2   HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)
#define BOTTOM_3   HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)
#define BOTTOM_4   HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)
#define BOTTOM_5   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)
#define BOTTOM_6   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)
#define BOTTOM_7   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)
#define BOTTOM_8   HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)
//BOTTOM 9-16 reserved
#define SWITCH_L  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)
#define SWITCH_R  HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11)
#define KNOB_L1  	HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)
#define KNOB_L2  	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)
#define KNOB_R1  	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7) 
#define KNOB_R2  	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8)


#define BOTTOM_1_ON     0X01
#define BOTTOM_1_OFF		0xFE
#define BOTTOM_2_ON     0X02
#define BOTTOM_2_OFF		0xFD
#define BOTTOM_3_ON     0X04
#define BOTTOM_3_OFF		0xFB
#define BOTTOM_4_ON     0X08
#define BOTTOM_4_OFF		0xF7
#define BOTTOM_5_ON     0X10
#define BOTTOM_5_OFF		0xEF
#define BOTTOM_6_ON     0X20
#define BOTTOM_6_OFF		0xDF
#define BOTTOM_7_ON     0X40
#define BOTTOM_7_OFF		0xBF
#define BOTTOM_8_ON     0X80
#define BOTTOM_8_OFF		0x7F
#define SWITCH_L_ON    	0X01
#define SWITCH_L_OFF		0xFE
#define SWITCH_R_ON    	0X02
#define SWITCH_R_OFF		0xFD
#define KNOB_L_UP   	 	0X04
#define KNOB_L_DOWN			0xFB
#define KNOB_L_NULL   	0X08
#define KNOB_R_UP				0x10
#define KNOB_R_DOWN			0xEF
#define KNOB_R_NULL			0x20
#define RESET						0X40
#define NRESET			    0xBF

/*------------------------------------------------------------------------------
  屏幕接收RX缓冲区
------------------------------------------------------------------------------*/
//extern uint8_t Rx_Buffer;
//extern uint8_t Rx_Buffer_FLAG;
//旋钮方向


/*------------------------------------------------------------------------------
  ADC临时变量
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
  电量读取变量
  Int_Voltage：映射电量
  Avg_Voltage：平均电量
  Vol_Level：电量百分比
  Vol_Color：电量颜色
  Trans_Time：转换时间（ms）
------------------------------------------------------------------------------*/
extern short KNOB_L_FLAG,KNOB_R_FLAG;

/*------------------------------------------------------------------------------
  ADC最大最小值定义
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
  解算ADC数据
------------------------------------------------------------------------------*/
extern int32_t LX,LY,RX,RY;  
//开始标志
extern uint8_t ADC1_Flag; 

/*------------------------------------------------------------------------------
  ADC读取变量
------------------------------------------------------------------------------*/
extern uint16_t ADC_Value[BIT]; 

/*------------------------------------------------------------------------------
  高低八位临时变量
------------------------------------------------------------------------------*/
extern int binary[4] ;
extern int highByte[6] ;
extern int lowByte[6] ;

/*------------------------------------------------------------------------------
  初始化数组
------------------------------------------------------------------------------*/
extern int32_t INIT_data[4];

/*------------------------------------------------------------------------------
  传输数据数组
------------------------------------------------------------------------------*/
extern uint8_t TXData[11]; 

/*------------------------------------------------------------------------------
  MAP函数
------------------------------------------------------------------------------*/
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

/*------------------------------------------------------------------------------
    ADC更新函数
------------------------------------------------------------------------------*/
void Update_ADC(void);

/*------------------------------------------------------------------------------
    按键更新函数
------------------------------------------------------------------------------*/
void Update_BOTTOM(void);

/*------------------------------------------------------------------------------
    ADC初始化函数
------------------------------------------------------------------------------*/
void init_ADC_data(void);


#endif
