#include <Wire.h>
#include <SparkFun_MMA8452Q.h>
MMA8452Q accel;

#define LCD_ADRS 0x3E
#define up control[0]
#define down control[1]
#define ban control[2]
#define right control[3]
#define left control[4]

byte plankton[] = "PLANKTON SUMMIT";
byte control[5][16] = {  "       UP       ","      DOWN      ","      STOP      ","      RIGHT     ","      LEFT      "};


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  init_LCD();
  for (int i = 0; i < 15; i++) {
    writeData(plankton[i]);
  }
  accel.init();
}


void loop()
{
  if (accel.available())
  {
    accel.read();
    control_accel();
  }
}


void init_LCD() {
  delay(100);
  writeCommand(0x39);
  delay(20);
  writeCommand(0x39);
  delay(20);
  writeCommand(0x14);
  delay(20);
  writeCommand(0x7F);
  delay(20);
  writeCommand(0x53);
  delay(20);
  writeCommand(0x6C);
  delay(20);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x01);
  delay(20);
  writeCommand(0x0C);
  delay(20);
}


void control_lcd(int x) {
  writeCommand(0x40 + 0x80);
  for (int i = 0; i < 16; i++) {
    writeData(control[x][i]);
  }
}


void control_accel()
{
  byte pl = accel.readPL();
  switch (pl)
  {
    case PORTRAIT_D:
      Serial.print("F");
      control_lcd(0);
      break;
    case PORTRAIT_U:
      Serial.print("B");
      control_lcd(1);
      break;
    case LOCKOUT:
      Serial.print("S");
      control_lcd(2);
      break;
    case LANDSCAPE_L:
      Serial.print("L");
      control_lcd(4);
      break;
    case LANDSCAPE_R:
      Serial.print("R");
      control_lcd(3);
      break;
  }
}


void writeData(byte t_data)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x40);
  Wire.write(t_data);
  Wire.endTransmission();
  delay(1);
  //  }
}


void writeCommand(byte t_command)
{
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
  delay(10);
}
