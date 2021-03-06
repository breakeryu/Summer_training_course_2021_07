# SPI驱动LCD屏幕调试

## 1.调用的SPI库
现在使用的SPI库没有用？？？
怎么说我现在出的问题呢？
首先说一下我需要做的一件事情，我需要驱动一块TFT-LCD屏幕，这个屏幕的PCB电器属性连接是这样子的:

![输入图片说明](https://images.gitee.com/uploads/images/2020/0223/212531_106f9fcc_2085323.png "1.png")

emm,引脚的功能如下：

![输入图片说明](https://images.gitee.com/uploads/images/2020/0223/212543_0604e229_2085323.png "2.png")

相关的SPI的通信是单向的，也就是说，spi的管脚实际上只是使用了2个，一个是SPI3的PB3-->SPI_SCK , 另外一个是SPI3的PB5-->SPI_MOSI 。

然后，在HAL库中，你可以使用单主机模式，只使用有关SPI3的两个管脚进行SPI驱动。

但是，现在的问题，对于arduino，他没有真正的单主机模式，在内部的函数定义中，很多都是不能够只赋值MOSI，而不去赋值MISO的。

所以这样让我苦恼了很久。
## 2. 内核定义的改写

对于内部的Pins的声明中，我发现了对于 PB_3是没有定义的，这里我查找了相关的资料，发现我现在使用的PLATFROMIO的内核（core)是根据ST官方做的B_L475G_IOT的板子改写的arduino平台驱动，所以，根据这个版本来说，需要去找ST给出的资料，我去了MBED.COM查找该板子的硬件资料。

结果发现ST官方给出的资料之丰富是我没有想到的。

ST官方做的网页介绍了该板子的硬件功能设备，板子的特性，还有引脚的图片等重要信息。我仔细查阅该网站的时候，竟然发现下面的给出的更多资料中竟然有该板子和之后的更新的版本的原理图，PCB整个工程文件。这让我对ST官方更加的崇拜了，真的很佩服他们的开源性质的无私。他们做的MBED.OS操作系统也是非常好的。有机会我一定要试一下。

回归正题，在下载了ST的资料之后，对比原来文件对应的PINS的配置，我确定了，我的方向是对的，这样的配置都和ST官方的这块开发板是对应的。

下面是ST IOT开发板的豪华配置：


主板功能

* 64 Mb Quad-SPI（Macronix）

* 闪存蓝牙V4.1模块（SPBTLE-RF）

* 低于GHz（868或915 MHz）的低功耗可编程RF模块（SPSGRF-868或SPSGRF-915）

* Wi-Fi®模块Inventek ISM43362-M3G-L44（符合802.11 b / g / n）

* 基于M24SR的动态NFC标签及其印刷的NFC天线

* 2个数字全向麦克风（MP34DT01）

* 相对湿度和温度的电容式数字传感器（HTS221）

* 高性能3轴磁力计（LIS3MDL）

* 3D加速度计和3D陀螺仪（LSM6DSL）

* 260-1260 hPa绝对数字输出气压计（LPS22HB）

* 飞行时间和手势检测传感器（VL53L0X）

* 2个按钮（用户和复位）

* 带有Micro-AB连接器的USB OTG FS

* 扩展连接器：
            * Arduino™Uno V3    *  PMOD

* 灵活的电源选项：ST LINK USB VBUS或外部电源

* 带有USB重新枚举功能的板载ST-LINK / V2-1调试器/编程器：大容量存储，虚拟COM端口和调试端口

我在该板子中查找相关的PB3对应的外设，发现是ST-LINK的下载口相关的，所以内核中就没有这个引脚的相关定义。那么，这里我需要该引脚，而且是作为SPI3的一个MOSI的数据输出重要的一环，所以必须在内核文件中定义相关的声明。

这里，我在添加相关的PINS 中也遇到了一些问题，在相关的Pins_map中，这里的也涉及到有关Analog引脚的冲突定义，而且需要看的相关很多，因为不只是在Pins_map中添加一个Pin，而且需要确保其他的引脚没有被干扰到，其他的功能之后还是可以正常工作。

下面是对内核声明的部分：

首先，更改variant.cpp中const PinName digitalPin[]这个一维数组中关于PB3的定义，

![输入图片说明](https://images.gitee.com/uploads/images/2020/0223/212604_5f2cb39c_2085323.png "3.png")

然后，进入variant.h中，进行修改

![输入图片说明](https://images.gitee.com/uploads/images/2020/0223/212613_5761a858_2085323.png "4.png")

这样，在内核声明文件中，PB3就可以作为一个数字引脚可以被识别到。

另外，需要更改以下的数值，修改过后：

![输入图片说明](https://images.gitee.com/uploads/images/2020/0223/212622_955a907d_2085323.png "5.png")

我原来以为还需要修改这一部分的SPI引脚定义，但是实验过后，这里不用额外定义。可能是使用了外部的库的原因，不过要找到真正的逻辑上面的原因，还是需要在外部的库中的定义中去寻找答案。下面是一个截图，是我修改的地方。

![输入图片说明](https://images.gitee.com/uploads/images/2020/0223/212631_63d0ff68_2085323.png "6.png")

    
    
    
   ## 3.外部库函数的调用
   
    
啊啊，稍等，我好像找到了一个靠谱的。

哇，我可以了！！！！！！！

真正的猛士，真的找到了。

我在外面的石板上坐着，浏览手机网站中的信息，检索信息，我发现了这个网址 : [STM32+ST7789+XPT2046测试程序](https://www.arduino.cn/thread-93865-1-1.html) , 其实，这样的标题和我检索的只有部分的重合，但是我看了一下之后，我的直觉就是，这个没准可以实现我想要的功能。

接着，我回家，把相关的库文件安装在我的工程文件中，然后进行了库的调用，然后是一些和该贴一样的初始化和一些赋值操作等。

接着，我进行实验，就好使了。可以驱动TFT-LCD并且可以完成我想要的功能：打印我的名字在LCD屏幕上。


当然，我在论坛上还找到了一个有关菜单的介绍，是 [OLED128*64自制可达10000000个选项的菜单](
https://www.arduino.cn/thread-89659-1-1.html)

那么这里的驱动工作我也做的差不多了。其实我还蛮想研究一下相关的算法的，因为这里面挺多的画线，画⚪等算法还是比较好玩的。


## 4.接下来的工作

SPI的FLASH读取和写入，我想驱动一下这个SPI的FLASH。
    