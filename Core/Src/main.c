
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "cmsis_os2.h"
#include "rtx_os.h"
#include "lcd_zk.h"
//#include "EventRecorder.h"
//#include "ugui.H"
#include "spi.h"
#include "config.h"

#include "arm_math.h"
#include "arm_const_structs.h"
/* USER CODE BEGIN Includes */
uint8_t BufferAry[128]={63};

#define TEST_LENGTH_SAMPLES 2048

/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
//static float32_t testOutput[TEST_LENGTH_SAMPLES/2];

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
uint8_t fall_pot[128];
/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, testIndex = 0;


void worker(void *arg)
{
	//GUI_Init();
	//GUI_DispStringAt( "Hello!!!", 10, 10 );
	

	
  while(1) 
  {
    //work
		//EventStartA(0); 
		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    osDelay(200);
		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		osDelay(200);
	//	EventStopA(0);
  }  
}

void oledblink(void *arg)
{
	static uint8_t x=0,y=0;

//	OLED_ShowString(1,0,"RED IR Leaning");
//	OLED_ShowString(2,1,"RED IR Leaning");
//	OLED_ShowString(3,2,"RED IR Leaning");
//	OLED_ShowString(4,3,"RED IR Leaning");
//OLED_draw_pixel(10,50,1);
//OLED_draw_pixel(64,2,1);

//OLED_draw_pixel(64,4,1);
//
//OLED_draw_pixel(63,8,1);
	//OLED_DrawPoint(0,0,1);
  while(1) 
  {
//	OLED_draw_pixel(x,y,1);
//	x++;
//		if(x>127)
//		{
//			x=0;
//			y++;
//		}
		//osDelay(2);
//	OLED_ShowString(1,2,"    DSI");
//		printf("The value of i is %d\n", 1);
//		osDelay(200);
//	OLED_ShowString(1,4," LT_T Delta");
//		osDelay(200);
//	OLED_ShowString(1,6," 2018-7-02");
//	osDelay(200);
//		OLED_Clear();
//		osDelay(200);
  }
}
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
osRtxThread_t worker_thread_tcb_1;
 osRtxThread_t worker_thread_tcb_2;
// Reserve two areas for the stacks of worker thread 1
// uint64_t makes sure the memory alignment is 8
uint64_t worker_thread_stk_1[1024];
 uint64_t worker_thread_stk_2[64];
// Define the attributes which are used for thread creation
// Optional const saves RAM memory and includes the values in periodic ROM tests 
const osThreadAttr_t worker_attr_1 = {
  "wrk1",
  osThreadJoinable,		//可执行线程
  &worker_thread_tcb_1,	//任务控制块
  sizeof(worker_thread_tcb_1),	//任务控制块大小
  &worker_thread_stk_1[0],	//任务堆栈起始地址
  sizeof(worker_thread_stk_1),	//任务堆栈大小
  osPriorityAboveNormal, //任务优先级
  0
};


const osThreadAttr_t worker_attr_2 = {
  "wrk2",							
  osThreadJoinable,		//可执行线程
  &worker_thread_tcb_2,	//任务控制块
  sizeof(worker_thread_tcb_2),	//任务控制块大小
  &worker_thread_stk_2[0],	//任务堆栈起始地址
  sizeof(worker_thread_stk_2),	//任务堆栈大小
  osPriorityNormal, //任务优先级
  0
};


osThreadId_t th1;		//线程名字
osThreadId_t th2;	
void app_main (void *argument) {
  uint32_t param = NULL;
 
  // Create an instance of the worker thread with static resources (TCB and stack)
  th1 = osThreadNew(worker, &param, &worker_attr_1);
  th2 = osThreadNew(oledblink, &param, &worker_attr_2);
  for (;;) {osDelay(1000);}
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void DrawPotLine(void);
void DrawWeithLine(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
//UG_GUI gui;

//void UserPixelSetFunction ( UG_S16 x , UG_S16 y ,UG_COLOR c )
//{
//	OLED_draw_pixel(x,y,c);
//}
int main(void)
{
  /* USER CODE BEGIN 1 */
//	 arm_status status;
//  float32_t maxValue;
uint8_t i=0;
//  status = ARM_MATH_SUCCESS;
//		static uint8_t x=0,y=0;

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  //EventRecorderInitialize(EventRecordAll,1);
	//EventRecorderStart();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
//		for(i=0;i<128;i++)
//			fall_pot[i] = 63;
//	osKernelInitialize();                 // Initialize CMSIS-RTOS
//  osThreadNew(app_main, NULL, NULL);    // Create application main thread
//  osKernelStart();                      // Start thread execution
//  for (;;) {
//	
//	osDelay(10);
//	}
// UG_Init( &gui , UserPixelSetFunction , 128 , 64 );
////UG_FillFrame(10,10,50,50,C_WHITE);
// UG_DrawCircle(50,30,20,C_WHITE);
// UG_FontSelect( &FONT_7X12 );
////UG_SetBackcolor(C_BLACK);
//UG_SetForecolor (C_WHITE);
//UG_PutString(1,1,"I Love You!");
//UG_DrawLine(0,63,0,60,2);


//GUI_Initialize();


  /* Process the data through the CFFT/CIFFT module */
// arm_cfft_f32(&arm_cfft_sR_f32_len1024, testInput_f32_10khz, ifftFlag, doBitReverse);

//  /* Process the data through the Complex Magnitude Module for
//  calculating the magnitude at each bin */
//  arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);

//  /* Calculates maxValue and returns corresponding BIN value */
//  arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);

//  if(testIndex !=  refIndex)
//  {
//   status = ARM_MATH_TEST_FAILURE;
//  }

//  /* ----------------------------------------------------------------------
//  ** Loop here if the signals fail the PASS check.
//  ** This denotes a test failure
//  ** ------------------------------------------------------------------- */

//  if( status != ARM_MATH_SUCCESS)
//  {
//    while(1);
//  }
//GUI_RectangleFill(10,10,50,50,1);

  /* USER CODE END 2 */
//GUI_LineWith(1,63,1,63-5,3,1);
//GUI_LineWith(5,63,5,63-10,3,1);
//GUI_LineWith(9,63,9,63-15,3,1);
//GUI_LineWith(13,63,13,63-20,3,1);
//GUI_LineWith(17,63,17,63-25,3,1);
//GUI_LineWith(21,63,21,63-30,3,1);
//GUI_LineWith(25,63,25,63-35,3,1);
//GUI_LineWith(29,63,29,63-40,3,1);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHIkLE */
DrawWeithLine();
//HAL_Delay(100);
  /* USER CODE BEGIN 3 */
	//	OLED_ShowString(4,3,"RED IR Leaning");
//		OLED_draw_pixel(x,y,1);
//	x++;
//	if(x>127)
//	{
//		x=0;
//		y++;
//	}

  }
  /* USER CODE END 3 */

}


void DrawPotLine(void)
{
uint8_t i = 0;
uint8_t y = 0;
	//GUI_ClearSCR();
		for(i=0;i<128;i++)
	{
			//	y = rand()%62+1;
		y=BufferAry[i];
			//fall_pot[i] = rand();
			GUI_RLine(i,y,1,0);
			GUI_RLine(i,y,64,1);
			if(fall_pot[i]<(64-y)) fall_pot[i]=(64-y);
			else{
			GUI_RLine(i,64-fall_pot[i],64-fall_pot[i]+1,1);
			if (fall_pot[i]>2)
			fall_pot[i] -=2;
			}
	}
	GUI_Exec();
}

void DrawWeithLine(void)
{
uint8_t i = 0;
uint8_t x,y = 0;
//	GUI_ClearSCR();
		for(i=1;i<32;i++)
	{
				x=(i<<2);
			//fall_pot[i] = rand();
				y=BufferAry[i];
				GUI_LineWith(x,y,x,64,3,1);
				GUI_LineWith(x,y,x,1,3,0);
			if(fall_pot[i]<(63-y)) fall_pot[i]=(63-y);
			else{
			GUI_LineWith(x,64-fall_pot[i],x,64-fall_pot[i]+1,3,1);
			if (fall_pot[i]>2)
			fall_pot[i] -=2;
			
			}
	}
	GUI_Exec();
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enables the Clock Security System 
  */
  HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
static uint16_t i,j = 0;
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
		i++;
		if(i<2000)
		{
			for(j=0;j<128;j++)
			BufferAry[j]=62;
		}
		if(i>2000&&i<4000)
		{
			for(j=0;j<128;j++)
			BufferAry[j]=1;
		}
		if(i>4000)
		{
		i=0;
		}
//for(i=0;i<128;i++)
//		{
//			BufferAry[i]=rand()%62+1;
//		}
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
