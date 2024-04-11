# esp32-singal-generator

一个刚玩嵌入式的fw一晚上的成果

使用了AD9833模块来生成信号

功能是生成频率为1-10mhz的正弦波，三角波和方波

![image-20240411115411177](https://github.com/xa9-top/esp32-singal-generator/raw/img/1.png)

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

![image-20240411115411177](https://github.com/xa9-top/esp32-singal-generator/raw/img/2.png)

逻辑很简单吧

app使用blynk，由于官方的服务器在国外太慢，于是自己使用docker搭了个

**mpherg/blynk-server**

这个应该都会吧（

不会去问搜索引擎（其实是懒得写，本人极其稀有的INTP女生）

然后添加一个工程(ESP32 Dev Board)，BLE方式连接，再添加个终端(虚拟管脚V3)

就可以van了

因为考虑到中文乱码问题终端全用的英文（

最后放效果图（只测了1khz的方波,也是默认）

![image-20240411120623507](https://github.com/xa9-top/esp32-singal.generator/raw/img/3.png)

最后请大佬们多多指教（
