#include <Arduino.h>
// #include <TFT_eSPI.h>
// #include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial gm65(38, 37); // RX, TX
// TFT_eSPI tft = TFT_eSPI();

// DI
int io1 = 13; // D13
int io2 = 12; // D12
int io3 = 14; // D14
int io4 = 27; // D27
int io5 = 26; // D26
int io6 = 25; // D25

// DQ
int alarm = 23; // alarm D23
int cutoff_sewing = 22; // on-off motor D22
int DO_SPARE = 21; // DO_SPARE D21
int trig1 = 15; // D15
int trig2 = 5; // D5

/*
Program
1.000
2.100
3.110
4.111
5.001
6.011
7.010
8.101
*/

String readString = "";
String input = "504-A"; 

const int BUFFER_SIZE = 50;
char buf[BUFFER_SIZE];

void read_kanban(){
  if (digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // 000
  {
    if (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3)) // 111
    {
      if (digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3)) // 100
      {
        input = "100";
      }
      else if (digitalRead(io1) && digitalRead(io2) && !digitalRead(io3)) // 110
      {
        input = "110";
      }
      else if (!digitalRead(io1) && !digitalRead(io2) && digitalRead(io3)) // 001
      {
        input = "001";
      }
      else if (!digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // 011
      {
        input = "011";
      }
      else if (!digitalRead(io1) && digitalRead(io2) && !digitalRead(io3)) // 010
      {
        input = "010";
      }
      else if (digitalRead(io1) && !digitalRead(io2) && digitalRead(io3)) // 101
      {
        input = "101";
      }
    }    
  }
  
}
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
  }  
}



