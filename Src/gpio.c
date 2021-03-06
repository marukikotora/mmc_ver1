/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */
#include "global.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, led0_Pin|led1_Pin|paluse0_Pin|paluse1_Pin 
                          |paluse2_Pin|paluse3_Pin|gyro_int_Pin|led2_Pin 
                          |led3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(gyro_cs_GPIO_Port, gyro_cs_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin 
                           PCPin PCPin PCPin PCPin 
                           PCPin */
  GPIO_InitStruct.Pin = led0_Pin|led1_Pin|paluse0_Pin|paluse1_Pin 
                          |paluse2_Pin|paluse3_Pin|gyro_int_Pin|led2_Pin 
                          |led3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = gyro_cs_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(gyro_cs_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = push0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(push0_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/****************************************************************************************
 * outline  : push -> ON , else -> OFF
 * argument : void
 * return   : ON or OFF
********************************************************************************************/
uint8_t Push(void){
  uint8_t push;
  if(HAL_GPIO_ReadPin(push0_GPIO_Port,push0_Pin) == GPIO_PIN_RESET){
    push=1;
  }
  if(HAL_GPIO_ReadPin(push0_GPIO_Port,push0_Pin) == GPIO_PIN_SET){
    push = 0;
  }
  return push;
}

/****************************************************************************************
 * outline  : turn on all led
 * argument : void
 * return   : void
********************************************************************************************/
void All_LED_ON(void)
{
  HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
}

/****************************************************************************************
 * outline  : turn off all led
 * argument : void
 * return   : void
********************************************************************************************/
void All_LED_OFF(void)
{
  HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_SET);
}

void LED_Control(unsigned char pattern){
  if(pattern == 0) All_LED_OFF();
  if((pattern & 0b0001) == 0b0001) HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
  else                             HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_SET);
  if((pattern & 0b0010) == 0b0010) HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
  else                             HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
  if((pattern & 0b0100) == 0b0100) HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_RESET);
  else                             HAL_GPIO_WritePin(led2_GPIO_Port,led2_Pin,GPIO_PIN_SET);
  if((pattern & 0b1000) == 0b1000) HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_RESET);
  else                             HAL_GPIO_WritePin(led3_GPIO_Port,led3_Pin,GPIO_PIN_SET);
}

/****************************************************************************************
 * outline  : turn on all infrared led
 * argument : void
 * return   : void
********************************************************************************************/
void All_IR_ON(void){
  if(flag.ir_led == ON){
    HAL_GPIO_WritePin(paluse0_GPIO_Port,paluse0_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(paluse1_GPIO_Port,paluse1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(paluse2_GPIO_Port,paluse2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(paluse3_GPIO_Port,paluse3_Pin,GPIO_PIN_SET);
  }else{
    All_IR_OFF();
  }
}

/****************************************************************************************
 * outline  : turn off all infrared led
 * argument : void
 * return   : void
********************************************************************************************/
void All_IR_OFF(void){
  HAL_GPIO_WritePin(paluse0_GPIO_Port,paluse0_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(paluse1_GPIO_Port,paluse1_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(paluse2_GPIO_Port,paluse2_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(paluse3_GPIO_Port,paluse3_Pin,GPIO_PIN_RESET);
}

/****************************************************************************************
 * outline  : control infrared led
 * argument : pattern
 *            (front_left  side_right  side_left  front_right
 *                1000        0100        0010       0001     )
 * return   : void
********************************************************************************************/
void IR_Contoroll(int pattern){
  if((pattern & 0b0001) == 0b0001) HAL_GPIO_WritePin(paluse0_GPIO_Port,paluse0_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse0_GPIO_Port,paluse0_Pin,GPIO_PIN_RESET);
  if((pattern & 0b0010) == 0b0010) HAL_GPIO_WritePin(paluse1_GPIO_Port,paluse1_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse1_GPIO_Port,paluse1_Pin,GPIO_PIN_RESET);
  if((pattern & 0b0100) == 0b0100) HAL_GPIO_WritePin(paluse2_GPIO_Port,paluse2_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse2_GPIO_Port,paluse2_Pin,GPIO_PIN_RESET);
  if((pattern & 0b1000) == 0b1000) HAL_GPIO_WritePin(paluse3_GPIO_Port,paluse3_Pin,GPIO_PIN_SET);
  else                             HAL_GPIO_WritePin(paluse3_GPIO_Port,paluse3_Pin,GPIO_PIN_RESET);
}
/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
