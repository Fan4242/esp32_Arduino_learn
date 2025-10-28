#include <Arduino.h>
#include "PWM.h"

#define LED_PWM_PIN 15    /* PWM 信号输出的引脚 */
#define LED_PWM_CHANNEL 0 /* LED PWM 通道号 */

void LEDC_Init(uint16_t frequency, uint8_t resolution)
{
    
    ledcSetup(LED_PWM_CHANNEL, frequency, resolution); 
    /* PWM 初始化,引脚和通道由 pwm.h 的 LED_PWM_PIN 和 LED_PWM_CHANNEL 宏修改 */
    ledcAttachPin(LED_PWM_PIN, LED_PWM_CHANNEL); 
    /* 绑定 PWM 通道到 LED_PWM_PIN 上 */
}

/**
* @brief PWM 占空比设置
* @param duty: PWM 占空比
* @retval 无
*/
void pwm_set_duty(uint16_t duty)
{
    ledcWrite(LED_PWM_CHANNEL, duty); 
    /* 改变 PWM 的占空比,通道由 pwm.h 的 LED_PWM_CHANNEL 宏修改 */
}
