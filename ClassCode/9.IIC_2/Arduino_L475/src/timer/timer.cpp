#include "timer.h"


void ledToggle(void){
  LED_R_Toggle;
} 

//!this is first demo
//定时器设置PWM模式的DEMO
#if DEMO1
void timer_Pwm_Init(void){

  //获取管脚的定时器
  TIM_TypeDef *Instance = TIM1;
  //获取管脚的定时器通道
  uint32_t channelGreen = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(PE9), PinMap_PWM));
  //定义定时器类 
  HardwareTimer *myTimer = new HardwareTimer(Instance);
  //设置闪烁频率
  myTimer->setOverflow(1000, HERTZ_FORMAT);
  //设置定时器通道的模式
  myTimer->setMode(channelGreen, TIMER_OUTPUT_COMPARE_PWM1, PE9);
  //设置定时器输出占空比
  myTimer->setCaptureCompare(channelGreen, 50, PERCENT_COMPARE_FORMAT);

  //开启定时器
  myTimer->resume();
}
#endif


//!this is the second demo
#if DEMO2
// this callback occurs when the timer reaches is maximum value and resets to 0
void overflow_interrupt(void)
{ 
  // Note: It is bad practice to do expensive operations like Serial.print in an interrupt!             
  Serial1.print(" |");
}
// this callback occurs when timer counter == the ch1's compare register value (set to 25% of overflow below)
void compare_ch1_interrupt(void)
{ 
  Serial1.print(" _");
}

// this callback occurs when timer counter == the ch2's compare register value (set to 50% below)
void compare_ch2_interrupt(void)
{ 
  Serial1.print(" .");
}

// this callback occurs when timer counter == the ch3's compare register value (set to 75% below)
void compare_ch3_interrupt(void)
{ 
  Serial1.print(" +");
}

HardwareTimer *timer;
//定时器中断模式DEMO
void timer_counter_interrupts_mode_Init(void){
  
    TIM_TypeDef *inst = TIM1;  // not all timers can count down/updown.  Timer1 should be good.

    timer = new HardwareTimer(inst);
    timer->setOverflow(1, HERTZ_FORMAT); // this will setup prescaler and overflow so that overflow event happens once a second
    timer->attachInterrupt(overflow_interrupt); //this callback happens when timer over/underflows

    // prepare timer1 channel1 at 25% of oveflow
    timer->setMode(1, TIMER_OUTPUT_COMPARE);
    timer->setCaptureCompare(1, 25, PERCENT_COMPARE_FORMAT);
    timer->attachInterrupt(1, compare_ch1_interrupt);

    // prepare timer1 channel2 at 50% of oveflow
    timer->setMode(2, TIMER_OUTPUT_COMPARE);
    timer->setCaptureCompare(2, 50, PERCENT_COMPARE_FORMAT);
    timer->attachInterrupt(2, compare_ch2_interrupt);

    // prepare timer1 channel3 at 75% of oveflow
    timer->setMode(3, TIMER_OUTPUT_COMPARE);
    timer->setCaptureCompare(3, 75, PERCENT_COMPARE_FORMAT);
    timer->attachInterrupt(3, compare_ch3_interrupt);

    // we are not using timer1 channel4!

    // start the timer
    timer->resume();
    Serial1.println("");
    // Note: We could remove all the code below and it would still print!
    // _ — ‾ | _ — ‾ | _ — ‾ | _ — ‾ |
    Serial1.println("\ncountermode up (default)");
    delay(8001); 
    Serial1.println("");
    // ‾ — _ | ‾ — _ | ‾ — _ | ‾ — _ |
    Serial1.println("\ncountermode down");
    LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_DOWN);
    delay(8001); // Wait for 4 overflows 
    Serial1.println("");
    // _ — ‾ | ‾ — _ | _ — ‾ | ‾ — _ |
    Serial1.println("\ncountermode center up/down (overflow and underflow events)");
    LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
    timer->refresh(); // this makes the above command happen immediately, otherwise it happens after next overflow
    delay(8001); // Wait for 4 overflows
    Serial1.println("");
    // _ — ‾ ‾ — _ | _ — ‾ ‾ — _ |
    Serial1.println("\ncountermode center up/down (underflow only events)");
    LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
    LL_TIM_SetRepetitionCounter(timer->getHandle()->Instance,1);
    timer->refresh(); // refresh() makes the above command happen immediately, otherwise it happens after next overflow
    delay(8001); // Wait for 4 overflows
    Serial1.println("");
    // reset to default countermod (up) for next loop
    LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_UP);
    LL_TIM_SetRepetitionCounter(timer->getHandle()->Instance,0);
    timer->refresh();

}
#endif

//!this is the third demo
#if DEMO3
HardwareTimer *timer;
byte dead_time = 220;  //non linear and clock speed dependent!
int duty = 50;

void complementary_channels_with_deadtime(void){
  timer = new HardwareTimer(TIM1);
  //ordering is impotant! Overflow first, LL_TIM* last.
  timer->setOverflow(40000, HERTZ_FORMAT); 
  timer->setCaptureCompare(1, duty, PERCENT_COMPARE_FORMAT);
  // I expect calling this is 'not the proper way'.  I should probably be configuring TIM_OC by hand, but this works!
  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE_8);
  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE_9);

  LL_TIM_OC_SetDeadTime(timer->getHandle()->Instance, dead_time);
  LL_TIM_CC_EnableChannel(timer->getHandle()->Instance, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH1N);
  // LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
  timer->resume();
}
#endif

//!this is the froth demo
#if DEMO4

HardwareTimer *timer;
int duty = 50;
byte dead_percent = 10;

void pwm1_2_with_deadtime_demo(void){
  timer = new HardwareTimer(TIM1);
  //ordering is impotant! Overflow first, LL_TIM* last.
  timer->setOverflow(40000, HERTZ_FORMAT); 

  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE_9);
  timer->setMode(2, TIMER_OUTPUT_COMPARE_PWM2, PE_11);
  timer->setCaptureCompare(1, duty, PERCENT_COMPARE_FORMAT);
  timer->setCaptureCompare(2, duty + dead_percent, PERCENT_COMPARE_FORMAT);

  LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
  
  timer->resume();
}

#endif


void timer_Init(void){
    #if DEMO1
    timer_Pwm_Init();
    #endif

    #if DEMO2
    timer_counter_interrupts_mode_Init();
    #endif
    
    #if DEMO3
    complementary_channels_with_deadtime();
    #endif

    #if DEMO4
    pwm1_2_with_deadtime_demo();
    #endif
}


void timer_demo_loop(void){
    #if DEMO3
    delay(20);
    Serial1.println(dead_time);
    dead_time++; // a byte will naturally flip from 255 to 0
    LL_TIM_OC_SetDeadTime(timer->getHandle()->Instance, dead_time);
    #endif 

    #if DEMO4
    delay(100);
    Serial1.println(dead_percent);
    dead_percent++;
    if (dead_percent >= 100 - duty) {
        dead_percent = 1;
    }
    timer->setCaptureCompare(2, duty + dead_percent, PERCENT_COMPARE_FORMAT);
    #endif 
}
