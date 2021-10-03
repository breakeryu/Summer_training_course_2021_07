#include "usart.h"




void usart_init(void){

    Serial1.begin(115200);
    Serial1.write("1");


}



//hal 库使用串口例子

#if DEMO1

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling ****  **** UART_TwoBoards_ComPolling **** ";

/* Buffer used for reception */
uint8_t aRxBuffer[RXBUFFERSIZE];

UART_HandleTypeDef UartHandle;

void demo_usart_rx_tx(void){

    UartHandle.Instance        = USART1;

    UartHandle.Init.BaudRate     = 115200;
    UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits     = UART_STOPBITS_1;
    UartHandle.Init.Parity       = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode         = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
    {
        LED_R(1);
    }  
    if(HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        LED_G(1);
    }
    /*##-2- Start the transmission process #####################################*/  
    /* While the UART in reception process, user can transmit data through 
        "aTxBuffer" buffer */
    HAL_UART_Transmit(&UartHandle, (uint8_t*)aTxBuffer, TXBUFFERSIZE, 5000);
   
    LED_R(0);
    delay(500);
    LED_R(1);
    delay(500);

    /*##-3- Put UART peripheral in reception process ###########################*/  
    while(HAL_UART_Receive(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE, 5000) != HAL_OK)
    {
        LED_G(1);
    }
    
    HAL_UART_Transmit(&UartHandle, (uint8_t*)"\r\nReceive data:\r\n", TXBUFFERSIZE, 5000);
    HAL_UART_Transmit(&UartHandle, (uint8_t*)aRxBuffer, TXBUFFERSIZE, 5000);
    LED_G(0);

    
}

/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    if(huart->Instance == USART1){
            /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* Enable GPIO TX/RX clock */
        USARTx_TX_GPIO_CLK_ENABLE();
        USARTx_RX_GPIO_CLK_ENABLE();


        /* Enable USARTx clock */
        USARTx_CLK_ENABLE(); 
        
        /*##-2- Configure peripheral GPIO ##########################################*/  
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin       = USARTx_TX_PIN;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = USARTx_TX_AF;

        HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        GPIO_InitStruct.Pin = USARTx_RX_PIN;
        GPIO_InitStruct.Alternate = USARTx_RX_AF;

        HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
    }
  
}

/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1){
        /*##-1- Reset peripherals ##################################################*/
        USARTx_FORCE_RESET();
        USARTx_RELEASE_RESET();

        /*##-2- Disable peripherals and GPIO Clocks #################################*/
        /* Configure USART1 Tx as alternate function  */
        HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
        /* Configure USART1 Rx as alternate function  */
        HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
    }
}


#endif



#if DEMO2
void demo_usart_rx_tx(void){

}


#endif

#if DEMO3
void demo_usart_rx_tx(void){

}


#endif