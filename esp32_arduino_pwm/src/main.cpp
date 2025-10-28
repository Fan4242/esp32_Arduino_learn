#include <Arduino.h>
#include "../lib/PWM/PWM.h"

#define PMW_EN 1

int interruptCounter = 0;
hw_timer_t *timer = NULL;
volatile uint8_t led_status = 0;
uint16_t g_ledpwmval = 0;
uint8_t g_dir = 0;

//	函数名称：onTimer()
//	函数功能：中断服务的功能，它必须是一个返回void（空）且没有输入参数的函数
//  为使编译器将代码分配到IRAM内，中断处理程序应该具有 IRAM_ATTR 属性
void IRAM_ATTR TimerEvent()
{
    led_status = ~led_status;
    digitalWrite(15, led_status);
}
void setup()
{
    pinMode(15, OUTPUT);


#if PMW_EN
    LEDC_Init(1000, 10);/* LED PWM 初始化,PWM 输出频率为 1000HZ,占空比分辨率为 10 */
    

#else

    //	函数名称：timerBegin()
    //	函数功能：Timer初始化，分别有三个参数
    //	函数输入：1. 定时器编号（0到3，对应全部4个硬件定时器）
    //			 2. 预分频器数值（ESP32计数器基频为80M，80分频单位是微秒）
    //			 3. 计数器向上（true）或向下（false）计数的标志
    //	函数返回：一个指向 hw_timer_t 结构类型的指针
    timer = timerBegin(0, 80, true);

    //	函数名称：timerAttachInterrupt()
    //	函数功能：绑定定时器的中断处理函数，分别有三个参数
    //	函数输入：1. 指向已初始化定时器的指针（本例子：timer）
    //			 2. 中断服务函数的函数指针
    //			 3. 表示中断触发类型是边沿（true）还是电平（false）的标志
    //	函数返回：无
    timerAttachInterrupt(timer, &TimerEvent, true);

    //	函数名称：timerAlarmWrite()
    //	函数功能：指定触发定时器中断的计数器值，分别有三个参数
    //	函数输入：1. 指向已初始化定时器的指针（本例子：timer）
    //			 2. 第二个参数是触发中断的计数器值（1000000 us -> 1s）
    //			 3. 定时器在产生中断时是否重新加载的标志
    //	函数返回：无
    timerAlarmWrite(timer, 2000000, true);
    timerAlarmEnable(timer); //	使能定时器

#endif

}
void loop()
{

#if PMW_EN
    if (g_dir)
    {
        g_ledpwmval += 5;
    }
    else
    {
        g_ledpwmval -= 5;
    }
    if (g_ledpwmval > 1005)
    {
        g_dir = 0;
    }
    if (g_ledpwmval < 5)
    {
        g_dir = 1;
    }
    pwm_set_duty(g_ledpwmval);
    delay(10);
#endif
}