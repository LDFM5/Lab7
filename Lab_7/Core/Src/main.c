/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
SPI_HandleTypeDef hspi1;
FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t totalSpace, freeSpace;
char buffer[100];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t buffer2;
uint8_t recibir = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*void transmit_uart (char *string){
	uint8_t len = strlen(string);
	HAL_UART_Transmit(&huart2, (uint8_t*) string, len, 200);
}*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  void transmit_uart(char *string);
  HAL_UART_Receive_IT(&huart2, &buffer2, 1);
  void MenuImagenes();
  void MostrarMenu();
  //Montar SD
  fres = f_mount(&fs, "/", 0);
  if (fres == FR_OK) {
  transmit_uart("Micro SD card is mounted successfully\r\n");
	  //uint8_t test1[] = "Micro SD card is mounted successfully!\r\n";
	  //HAL_UART_Transmit(&huart2, test1, sizeof(test1), 100);
  } else if (fres != FR_OK) {
  transmit_uart("Micro SD card's mount error!\r\n");
	  //uint8_t test2[] = "Micro SD card's mount error!\r\n";
	  //HAL_UART_Transmit(&huart2, test2, sizeof(test2), 100);
  }
/*
  //Abrir archivo
  fres = f_open(&fil, "1.txt", FA_OPEN_APPEND | FA_WRITE | FA_READ);
  if (fres == FR_OK) {
  transmit_uart("File opened for reading.\r\n");
	  //uint8_t test5[] = "File opened for reading.\r\n";
	  //HAL_UART_Transmit(&huart2, test5, sizeof(test5), 100);
  } else if (fres != FR_OK) {
  transmit_uart("File was not opened for reading!\r\n");
	  //uint8_t test6[] = "File was not opened for reading!\r\n";
	  //HAL_UART_Transmit(&huart2, test6, sizeof(test6), 100);
  }


  //Escribir en archivo
  //for (uint8_t i = 0; i < 10; i++) {
  f_puts("Hola Mundo. Este es el archivo 1.\r\n", &fil);
  //}

  //Cerrar archivo
    fres = f_close(&fil);
    if (fres == FR_OK) {
    transmit_uart("The file is closed.\r\n");
  	  //uint8_t test7[] = "The file is closed.\r\n";
  	  //HAL_UART_Transmit(&huart2, test7, sizeof(test7), 100);
    } else if (fres != FR_OK) {
    transmit_uart("The file was not closed.\r\n");
  	  //uint8_t test8[] = "The file was not closed.\r\n";
  	  //HAL_UART_Transmit(&huart2, test8, sizeof(test8), 100);
    }
*/

 MostrarMenu();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  MenuImagenes(); // Llama al menú dentro del bucle principal
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SD_SS_GPIO_Port, SD_SS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_SS_Pin */
  GPIO_InitStruct.Pin = SD_SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(SD_SS_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void transmit_uart (char *string){
	HAL_UART_Transmit(&huart2, (uint8_t*) string, strlen(string), 200);
}

// Función para mostrar el menú
void MostrarMenu() {
    char menu[] = "\r\n--- MENU ---\r\n"
                  "Seleccione una imagen:\r\n"
                  "1. Imagen 1\r\n"
                  "2. Imagen 2\r\n"
                  "3. Imagen 3\r\n"
    				"4. Salir\r\n"
                  "Ingrese una opcion: ";
    transmit_uart(menu);
}

// Función principal del menú
void MenuImagenes() {
	if (recibir) { // Solo entra si se ha recibido un dato
		recibir = 0; // Resetea la bandera

		switch (buffer2) {
			case '1':
				transmit_uart("\nMostrando Imagen 1...\n");
				fres = f_open(&fil, "mnm.txt", FA_READ);
					if (fres == FR_OK) {
					transmit_uart("File opened for reading.\r\n");
					  //uint8_t test5[] = "File opened for reading.\r\n";
					  //HAL_UART_Transmit(&huart2, test5, sizeof(test5), 100);
					} else if (fres != FR_OK) {
					transmit_uart("File was not opened for reading!\r\n");
					  //uint8_t test6[] = "File was not opened for reading!\r\n";
					  //HAL_UART_Transmit(&huart2, test6, sizeof(test6), 100);
					}

				  //Leer archivo
				  while (f_gets(buffer, sizeof(buffer), &fil)) {
				  char mRd[100];
				  sprintf(mRd, "%s", buffer);
				  transmit_uart(mRd);
				  //HAL_UART_Transmit(&huart2, (uint8_t*)mRd, strlen(mRd), 100);
				  }

				  //Cerrar archivo
				  fres = f_close(&fil);
				  if (fres == FR_OK) {
				  transmit_uart("The file is closed.\r\n");
					  //uint8_t test7[] = "The file is closed.\r\n";
					  //HAL_UART_Transmit(&huart2, test7, sizeof(test7), 100);
				  } else if (fres != FR_OK) {
				  transmit_uart("The file was not closed.\r\n");
					  //uint8_t test8[] = "The file was not closed.\r\n";
					  //HAL_UART_Transmit(&huart2, test8, sizeof(test8), 100);
				  }
				HAL_Delay(2000); // Simula una pausa antes de volver al menú
				MostrarMenu();
				break;

			case '2':
				transmit_uart("\nMostrando Imagen 2...\n");
				fres = f_open(&fil, "mr.txt", FA_READ);
					if (fres == FR_OK) {
					transmit_uart("File opened for reading.\r\n");
					  //uint8_t test5[] = "File opened for reading.\r\n";
					  //HAL_UART_Transmit(&huart2, test5, sizeof(test5), 100);
					} else if (fres != FR_OK) {
					transmit_uart("File was not opened for reading!\r\n");
					  //uint8_t test6[] = "File was not opened for reading!\r\n";
					  //HAL_UART_Transmit(&huart2, test6, sizeof(test6), 100);
					}

				  //Leer archivo
				  while (f_gets(buffer, sizeof(buffer), &fil)) {
				  char mRd[100];
				  sprintf(mRd, "%s", buffer);
				  transmit_uart(mRd);
				  //HAL_UART_Transmit(&huart2, (uint8_t*)mRd, strlen(mRd), 100);
				  }

				  //Cerrar archivo
				  fres = f_close(&fil);
				  if (fres == FR_OK) {
				  transmit_uart("The file is closed.\r\n");
					  //uint8_t test7[] = "The file is closed.\r\n";
					  //HAL_UART_Transmit(&huart2, test7, sizeof(test7), 100);
				  } else if (fres != FR_OK) {
				  transmit_uart("The file was not closed.\r\n");
					  //uint8_t test8[] = "The file was not closed.\r\n";
					  //HAL_UART_Transmit(&huart2, test8, sizeof(test8), 100);
				  }
				HAL_Delay(2000);
				MostrarMenu();
				break;

			case '3':
				transmit_uart("\nMostrando Imagen 3...\n");
				fres = f_open(&fil, "nya.txt", FA_READ);
					if (fres == FR_OK) {
					transmit_uart("File opened for reading.\r\n");
					  //uint8_t test5[] = "File opened for reading.\r\n";
					  //HAL_UART_Transmit(&huart2, test5, sizeof(test5), 100);
					} else if (fres != FR_OK) {
					transmit_uart("File was not opened for reading!\r\n");
					  //uint8_t test6[] = "File was not opened for reading!\r\n";
					  //HAL_UART_Transmit(&huart2, test6, sizeof(test6), 100);
					}

				  //Leer archivo
				  while (f_gets(buffer, sizeof(buffer), &fil)) {
				  char mRd[100];
				  sprintf(mRd, "%s", buffer);
				  transmit_uart(mRd);
				  //HAL_UART_Transmit(&huart2, (uint8_t*)mRd, strlen(mRd), 100);
				  }

				  //Cerrar archivo
				  fres = f_close(&fil);
				  if (fres == FR_OK) {
				  transmit_uart("The file is closed.\r\n");
					  //uint8_t test7[] = "The file is closed.\r\n";
					  //HAL_UART_Transmit(&huart2, test7, sizeof(test7), 100);
				  } else if (fres != FR_OK) {
				  transmit_uart("The file was not closed.\r\n");
					  //uint8_t test8[] = "The file was not closed.\r\n";
					  //HAL_UART_Transmit(&huart2, test8, sizeof(test8), 100);
				  }
				HAL_Delay(2000);
				MostrarMenu();
				break;

			case '4':
				 //Desmontar archivo
				  f_mount(NULL, "", 1);
				  if (fres == FR_OK) {
				  transmit_uart("The Micro SD card is unmounted!\r\n");
					  //uint8_t test3[] = "The Micro SD card is unmounted!\r\n";
					  //HAL_UART_Transmit(&huart2, test3, sizeof(test3), 100);
				  } else if (fres != FR_OK) {
				  transmit_uart("The Micro SD was not unmounted!\r\n");
					  //uint8_t test4[] = "The Micro SD was not unmounted!\r\n";
					  //HAL_UART_Transmit(&huart2, test4, sizeof(test4), 100);
				  }
				break;

			default:
				transmit_uart("\nOpción inválida. Intente de nuevo.\n");
				MostrarMenu();
				break;
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	//HAL_UART_Transmit(&huart2, &buffer, sizeof(&buffer), 100);
	recibir = 1;
	HAL_UART_Receive_IT(&huart2, &buffer2, 1);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
