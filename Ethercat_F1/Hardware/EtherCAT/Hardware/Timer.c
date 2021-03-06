/**
 *************************************************************************************
 * @file 
 * @author
 * @version
 * @date
 * @brief Ethercat hardware timer (USE tim5)
 *************************************************************************************
*/

#include "stm32f1xx.h"
#include "ecat_def.h"

#include "tim.h"

/*******************************************************************************
* Function Name  : TIM_Configuration
* Description    : TIM_Configuration program.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TIM_Configuration(uint8_t period)		//100us
{
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure; 
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
//	
//  TIM_DeInit(TIM2);
//  TIM_TimeBaseStructure.TIM_Period= period*200 ; //200;		 					/* 自动重装载寄存器周期的值(计数值) */
//																	/* 累计 TIM_Period个频率后产生一个更新或者中断 */
//  TIM_TimeBaseStructure.TIM_Prescaler= (42 - 1);				    /* 时钟预分频数   例如：时钟频率=72MHZ/(时钟预分频+1) */
//  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 			/* 采样分频 */
//  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		/* 向上计数模式 */
//  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//  TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    /* 清除溢出中断标志 */
//	#if ECAT_TIMER_INT
//  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//	#endif
//  TIM_Cmd(TIM2, ENABLE);											/* 开启时钟 */
//	
//	#if ECAT_TIMER_INT
//						/* Configure NVIC Interrupt  -------------------------*/	
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  													
//		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);
//	#endif

//   MX_TIM2_Init();
	TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 18-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = period*200 ; //200;		 					/* 自动重装载寄存器周期的值(计数值) */
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	
//	#if ECAT_TIMER_INT
//	HAL_TIM_Base_MspInit(&htim2);
//	#endif
}
