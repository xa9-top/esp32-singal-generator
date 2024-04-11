#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT
#include <MD_AD9833.h>
#include <SPI.h>
#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>

#include <U8g2lib.h>
#include <Wire.h>

WidgetTerminal terminal(V3);

String terminal_text ;
WidgetTerminal terminalV3(V3);

char auth[] = "";                                                       //此处填blynk app获取的授权码
String type_list[]={"Sine", "Triangle", "Squart"};

volatile int freq;
volatile int freq_type;
String freq_dp;
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,  22, 23, U8X8_PIN_NONE);

BLYNK_WRITE(V3){
  terminal_text = param.asStr();
  if (isnum(terminal_text) == true) {
    if (String(terminal_text).toFloat() <= 10000000 && String(terminal_text).toInt() >= 1) {
      freq = String(terminal_text).toInt();
      if (String(terminal_text).toFloat() >= 1000000) {
        freq_dp = String(String((String(terminal_text).toFloat() / 1000000))) + String("MHz");

      } else if (String(terminal_text).toFloat() >= 1000) {
        freq_dp = String(String((String(terminal_text).toFloat() / 1000))) + String("KHz");
      } else {
        freq_dp = String(terminal_text) + String("Hz");

      }
      u8g2.firstPage();
      do
      {
        page1();
      }while(u8g2.nextPage());
      freq_chg();
      terminalV3.println(String("The singal frequency is switch to:") + String(String(freq_dp)));
      terminalV3.flush();

    } else {
      terminalV3.println("Your input is out of the data range!\nThe singal frequency range is 1Hz to 10MHz.");
      terminalV3.flush();

    }

  } else {
    String str_cmp = terminal_text;
    str_cmp.toLowerCase();
    if (str_cmp == "sine") {
      freq_type = 0;
      u8g2.firstPage();
      do
      {
        page1();
      }while(u8g2.nextPage());
      freq_chg();
      terminalV3.println(String("The singal type is switch to:") + String(type_list[freq_type]));
      terminalV3.flush();

    } else if (str_cmp == "triangle") {
      freq_type = 1;
      u8g2.firstPage();
      do
      {
        page1();
      }while(u8g2.nextPage());
      freq_chg();
      terminalV3.println(String("The singal type is switch to:") + String(type_list[freq_type]));
      terminalV3.flush();
    } else if (str_cmp == "squart") {
      freq_type = 2;
      u8g2.firstPage();
      do
      {
        page1();
      }while(u8g2.nextPage());
      freq_chg();
      terminalV3.println(String("The singal type is switch to:") + String(type_list[freq_type]));
      terminalV3.flush();
    } else if (str_cmp == "help" || str_cmp == "h") {
      terminalV3.println("You can enter the signal frequency (1-10000000 Hz) to switch frequency.\nOr input 'sine', 'triangle', or 'squart' to switch signal type.\nOr you can input 'help' or 'h' for help.\nIf you need other help or have any questions, you can send an email to 'xa9@xa9.top'.");
      terminalV3.flush();
    } else {
      terminalV3.println(String("The command '") + String(terminal_text) + String("' cannot be recognized as runnable.\nPlease check the spelling and try again.\nInput 'h' or 'help' for help."));
      terminalV3.flush();

    }

  }
  terminal.flush();
}

MD_AD9833 AD(/*DATA*/5, /*CLK*/18, /*FSYNC*/19);
void page1() {
  u8g2.setFont(u8g2_font_ncenR08_tf);
  u8g2.setFontPosTop();
  u8g2.setCursor(0,0);
  u8g2.print("Signal Generator   By Xa9");
  u8g2.drawHLine(0,10,128);
  u8g2.drawHLine(0,12,128);
  u8g2.setFont(u8g2_font_ncenR10_tf);
  u8g2.setFontPosTop();
  u8g2.setCursor(0,16);
  u8g2.print("Freq");
  u8g2.setCursor(38,16);
  u8g2.print(freq_dp);
  u8g2.setCursor(0,32);
  u8g2.print("Type");
  u8g2.setCursor(38,32);
  u8g2.print(type_list[freq_type]);
}

boolean isnum(String str) {
  for (int i = 0; i < str.length(); i++){
      int tmp = (int)str[i];
      if (tmp >= 48 && tmp <= 57){
        continue;
      }else{
          return false;
      }
  }
  return true;
}

void freq_chg() {
  if (freq_type == 0) {
    AD.setMode(MD_AD9833::MODE_SINE);

  } else if (freq_type == 1) {
    AD.setMode(MD_AD9833::MODE_TRIANGLE);
  } else {
    AD.setMode(MD_AD9833::MODE_SQUARE1);

  }
  AD.setFrequency(MD_AD9833::CHAN_0, freq);
}

void setup(){
  Serial.begin(9600);
  Serial.println("Waiting for connections...");
  Blynk.setDeviceName("Blynk");
  Blynk.begin(auth);

  freq = 1000;
  freq_type = 2;
  freq_dp = "1.00KHz";
  u8g2.setI2CAddress(0x3C*2);
  u8g2.begin();
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  u8g2.firstPage();
  do
  {
    page1();
  }while(u8g2.nextPage());
  digitalWrite(17,LOW);
  digitalWrite(16,HIGH);
  AD.begin();
  AD.setMode(MD_AD9833::MODE_SQUARE1);
  AD.setFrequency(MD_AD9833::CHAN_0, 1000);
  u8g2.enableUTF8Print();

}

void loop(){
  Blynk.run();

}
