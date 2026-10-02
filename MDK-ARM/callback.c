#include "main.h"

/* rx_msg真正定义在main.c中 */
extern uint8_t rx_msg[4];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 确认本次接收完成中断来自USART1 */
    if (huart->Instance == USART1)
    {
        if (rx_msg[0] == 'R')
        {
            /* C板PH10蓝灯：高电平点亮 */
            HAL_GPIO_WritePin(
                LED_B_GPIO_Port,
                LED_B_Pin,
                GPIO_PIN_SET
            );
        }
        else if (rx_msg[0] == 'M')
        {
            /* 低电平熄灭 */
            HAL_GPIO_WritePin(
                LED_B_GPIO_Port,
                LED_B_Pin,
                GPIO_PIN_RESET
            );
        }

        /*
         * 本次接收已经完成。
         * 重新开启下一次1字节中断接收。
         */
        HAL_UART_Receive_IT(
            huart,
            rx_msg,
            1U
        );
    }
}