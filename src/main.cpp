#include <Arduino.h>
// #include <TFT_eSPI.h>
// #include <SPI.h>
#include <SoftwareSerial.h>

// SoftwareSerial gm65(38, 37); // RX, TX
SoftwareSerial gm65(4, 5); // RX, TX
// TFT_eSPI tft = TFT_eSPI();

int s1;
int s2;
int s3;
int trig;

int alarm ; // alarm
int cutoff_sewing ; // on-off motor
int trig_barcode ; // trig barcode


String readString = "";
String input = "504-A";

const int BUFFER_SIZE = 50;
char buf[BUFFER_SIZE];

// String inputString = "";      // ตัวแปรสำหรับเก็บค่าจากตัวแสกนเนอร์
// String DataScanner = "";      //ตัวแปรสำหรับเก็บค่าในการประมวลผล
// bool stringComplete = false;  // ตัวแปรเช็คว่ารับข้อมูลครบแล้วหรือยัง

// void serialEvent() {
//   while (Serial.available()) {
//     // get the new byte:
//     char inChar = (char)Serial.read();
//     // add it to the inputString:
//     inputString += inChar;
//     // if the incoming character is a newline, set a flag so the main loop can
//     // do something about it:
//     if (inChar == '\n') {
//       stringComplete = true;
//       DataScanner = String(inputString);
//     }
//   }
// }

void setup(void) {
  Serial.begin(115200);
  while (!Serial) ;
  gm65.begin(9600);
  // inputString.reserve(200); // ประกาศตัวแปรสำหรับเก็บข้อความขนาด 200 ตัวอักษร
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
        Serial.print(readString);
      }else{
        Serial.print("no : ");
        Serial.print(readString);

      }
      delay(1);
    }
    Serial.println(); //Move to a new line
    // readString="______________";
  }  
}



