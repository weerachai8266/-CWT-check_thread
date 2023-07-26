#include <Arduino.h>
// #include <TFT_eSPI.h>
// #include <SPI.h>
#include <SoftwareSerial.h>

// DI
int io1 = 13; // D13
int io2 = 12; // D12
int io3 = 14; // D14
int io4 = 27; // D27
int io5 = 26; // D26
int io6 = 25; // D25

// DQ
int alarm_on = 23; // alarm D23
int cutoff_sewing = 22; // on-off motor D22
int DO_SPARE = 21; // DO_SPARE D21
int trig1 = 15; // D15
int trig2 = 5; // D5

// system
int tx_1 = 2;
int rx_1 = 4;
int tx_2 = 18;
int rx_2 = 19;

String readString = "";
// String input = "504-A"; 
String read_card; 

const int BUFFER_SIZE = 50;
char buf[BUFFER_SIZE];

bool off = 1;
bool on = 0;

SoftwareSerial gm65(rx_1, tx_1); // RX, TX
// TFT_eSPI tft = TFT_eSPI();

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

String read_kanban(){
  String input; 
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
  return input; 
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
void tring (int x){
  digitalWrite(x, 0);
  delay(5);
  digitalWrite(x, 1);
  delay(5);
  Serial.println("tring on");
}
void setup(void) {
  Serial.begin(115200);
  while (!Serial) ;
  gm65.begin(9600);
  // pinMode(io1, INPUT);
  pinMode(io2, INPUT);
  pinMode(io3, INPUT);
  pinMode(io4, INPUT);
  pinMode(io5, INPUT);
  pinMode(io6, INPUT);

  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(alarm_on, OUTPUT);
  pinMode(cutoff_sewing, OUTPUT);
  pinMode(DO_SPARE, OUTPUT);
  
  digitalWrite(cutoff_sewing, off);
  digitalWrite(alarm_on, off);
  digitalWrite(trig1, 1);
  // delay(5);

}
void loop() {
  read_card = read_kanban();
  // digitalWrite(trig1, 1); // barcode off
  digitalWrite(cutoff_sewing, off); // barcode off 
  digitalWrite(alarm_on, off); // alarm off 

  while (!digitalRead(io6)) // check thread on
  {
    digitalWrite(trig1, 1); // barcode off
  }  

  while (digitalRead(io6)) // check thread on
  {
    digitalWrite(trig1, 0); // barcode on

    if (gm65.available()) //Checking if any data has been received
    {
      while (gm65.available()) //Read bit by bit until UART buffer is empty
      {
        readString = gm65.readString();
        Serial.print(readString); //Display input variable

        if (readString.compareTo("504-A")> 0)
        {
          Serial.print(readString);
          while (digitalRead(io6))
          {
            digitalWrite(trig1, 1); // barcode off 
            digitalWrite(alarm_on, off); // alarm off 
            digitalWrite(cutoff_sewing, on); // sewing on 
          }          
        }else{
          Serial.print("no : ");
          Serial.print(readString);
          while (digitalRead(io6))
          {
            digitalWrite(trig1, 1); // barcode off
            digitalWrite(alarm_on, on); // alarm on 
            digitalWrite(cutoff_sewing, off); // sewing off 
          }
        }
        delay(1);
      } // end while Read bit by bit until UART buffer is empty
      Serial.println(); //Move to a new line
    } // end if Checking if any data has been received 
  } // end while check thread on
} // end loop



