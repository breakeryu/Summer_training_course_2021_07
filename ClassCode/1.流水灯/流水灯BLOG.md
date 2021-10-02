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

## 2.发现问题

使用IDE（VSCode）的时候，编译出现一些错误。这里我把错误放在这里。

```
.pio/build/disco_l475vg_iot01a/src/main.cpp.o: In function `setup':
main.cpp:(.text.setup+0x0): undefined reference to `LED_Init()'
collect2.exe: error: ld returned 1 exit status
*** [.pio\build\disco_l475vg_iot01a\firmware.elf] Error 1

```


出现错误的原因，是因为我在第一次创建文件的时候，将我的led.cpp文件命名的时候
命名成为了led.c文件。

所以，这样子的命名会出现错误。

解决办法：之后的自己写的SRC文件和HEADER文件需要注意命名后缀，分别为.h,还有.cpp。







