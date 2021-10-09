## 测试平台：
·PlatformIO IDE（VSCode）

·正点原子潘多拉IOT开发板

·stlink v2仿真调试器（板载）


## 1.更新说明

添加led.cpp, led.h文件。


led.h

```cpp
    #ifndef _LED_H
    #define _LED_H
    #include <Arduino.h>

    #define LEDR    PE7
    #define LEDG    PE8
    #define LEDB    PE9

    #define LED_R(n)			(n?digitalWrite(LEDR,HIGH):digitalWrite(LEDR,LOW))
    #define LED_R_TogglePin		digitalToggle(LEDR)

    #define LED_G(n)			(n?digitalWrite(LEDG,HIGH):digitalWrite(LEDG,LOW))
    #define LED_G_TogglePin     digitalToggle(LEDG)

    #define LED_B(n)			(n?digitalWrite(LEDB,HIGH):digitalWrite(LEDB,LOW))
    #define LED_B_TogglePin     digitalToggle(LEDB)

    void LED_Init(void);

    #endif
```

led.cpp
```cpp
#include "led.h"

/**
 * @brief	LED IO初始化函数
 *
 * @param   void
 *
 * @return  void
 */
void LED_Init(void)
{
	/*
		LED-B	PE9
		LED-G	PE8
		LED-R	PE7	
	*/
    pinMode(PE7,OUTPUT);
    pinMode(PE8,OUTPUT);
    pinMode(PE9,OUTPUT);

	LED_R(1);
	LED_G(1);
	LED_B(1);


}


```

## 2.第一个编译的问题

在使用自己编写的文件时，源文件要以CPP文件后缀保存，头文件以.h文件保存。

## 3.文件夹设置

在编写驱动时，往往以文件夹保存文件的形式，例如
FEIL NAME : LED
            --led.cpp
            --led.h

像这样的一个LED驱动文件的编写是很简单的。但是在PIO的里面，引用这个驱动文件需要声明文件夹名称。
例如：在main.cpp文件中引用led.h:
```cpp
    #include "led/led.h"
```
这样的引用就像我们在对该文件夹进行强调，可以让PIO找到引用的路径。

注意：驱动文件夹可以放在src文件夹中。但是放在include文件夹中就会报错，我不知道为什么。









