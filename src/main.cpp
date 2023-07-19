#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial gm65(38, 37); // RX, TX
TFT_eSPI tft = TFT_eSPI();

int s1;
int s2;
int s3;
int trig;

String readString = "";
String input = "504-A";

const int BUFFER_SIZE = 50;
char buf[BUFFER_SIZE];

void setup(void) {
  Serial.begin(115200);
  while (!Serial) ;
  gm65.begin(9600);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

}
void loop() {
  if (gm65.available()) //Checking if any data has been received
  {
    while (gm65.available()) //Read bit by bit until UART buffer is empty
    {
      readString = gm65.readString();
      Serial.print(readString); //Display input variable

      if (readString.compareTo(input)> 0)
      {
        tft.fillScreen(TFT_CASET);
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        // tft.setTextSize(1);
        // tft.setCursor (8, 52);
        tft.drawString(readString, 0, 0, 2);
      }else{
        tft.fillScreen(TFT_RED);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("no bar", 0, 0, 2);

      }
      delay(1);
    }
    Serial.println(); //Move to a new line
    // readString="______________";
  }  
}



