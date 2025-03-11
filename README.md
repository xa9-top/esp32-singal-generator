# esp32-singal-generator

一个刚玩嵌入式的fw一晚上的成果

使用了AD9833模块来生成信号

功能是生成频率为1-10mhz的正弦波，三角波和方波

![image-20240411115411177](https://github.com/xa9-top/esp32-singal-generator/raw/main/img/image-20240411114326410.png)

很简洁吧，不打板子应该没有比这简洁的方式了吧

⚡即插即用⚡

显示屏的SCL和SDA分别是22，23脚，这种屏幕电子人应该都有吧（

然后上pdd花9块钱买一个AD9833的模块

因为模块功耗很低，使用数字引脚供电即可

`digitalWrite(17,LOW);#GND`
`digitalWrite(16,HIGH);#VCC`

接下来是9833模块

因为用直插使用5，18，19三个IO口分别作为DATA，CLK，SYNC的引脚

`MD_AD9833 AD(/*DATA*/5, /*CLK*/18, /*FSYNC*/19);`

9833是上cdsn抄的（

然后昨天晚上基本80%的时间用到了写blynk终端的逻辑上了（）

基本就是

![image-20240411115411177](https://github.com/xa9-top/esp32-singal-generator/raw/main/img/image-20240411115411177.png)

逻辑很简单吧

app使用blynk，由于官方的服务器在国外太慢，于是自己使用docker搭了个

**mpherg/blynk-server**

这个应该都会吧（

不会去问搜索引擎（其实是懒得写）-->这句删掉

然后添加一个工程(ESP32 Dev Board)，BLE方式连接，再添加个终端(虚拟管脚V3)

就可以van了

因为考虑到中文乱码问题终端全用的英文（

最后放效果图（只测了1khz的方波,也是默认）

![image-20240411120623507](https://github.com/xa9-top/esp32-singal-generator/raw/main/img/image-20240411120623507.png)

最后请大佬们多多指教（

然后来更新readme力(公元2024年4月21日)

感觉直接放上面的内容有可能有人不会操作（

先去下载**blynk**

然后点**Log In**

再点一下最底下Log In上面的**红绿灯**

点一下最显眼的那个开关，切到**CUSTOM**

输入xa9.top(这是我自己搭建的，如果自己有搭建就填自己的域名或者ip)

端口默认(如果docker里面改了端口这里也改下)

再点击OK

然后Email是**exp@xa9.top**

Password是**test**

进去之后直接点击第一个

然后点一下"![image-20240421063627266](https://github.com/xa9-top/esp32-singal-generator/raw/main/img/image-20240421063627266.png)"

点击"**Connect BLE Device**"

在底下找到**Blynk**并点击右边的**OK**

然后返回终端

帮助の翻译：

**您可以输入信号频率（1-1000000 Hz）来切换频率**

**或者输入'sine'（正弦）、'triangle'（三角波）或'squart'（方波）来切换信号类型**

**或者您可以输入'help'或'h'获取帮助**

**如果您需要其他帮助或有任何问题，您可以发送电子邮件至'[xa9.top@gmail.com](mailto:xa9.top@gmail.com)'**

![image-20240421065846334](https://github.com/xa9-top/esp32-singal-generator/raw/main/img/image-20240421065846334.png)

然后像这样操作即可（

