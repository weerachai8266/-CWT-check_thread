#include <Arduino.h>
#include <SoftwareSerial.h>

// DI
int io1 = 13; // D13
// int io2 = 12; // D12 do not use
int io2 = 14; // D14
int io3 = 27; // D27
int io4 = 26; // D26
int io5 = 33; // D33
int io6 = 25; // D25

// DQ
int alarm_on = 23; // alarm D23
int cutoff_sewing = 22; // on-off motor D22
int ready_lamp = 21; // DO_SPARE D21
int trig1 = 15; // D15
int trig2 = 5; // D5

// system
int tx_1 = 2;
int rx_1 = 4;
int tx_2 = 18;
int rx_2 = 19;

String read_card = "";
String read_barcode = "";

bool off = 1;
bool on = 0;

SoftwareSerial gm65(rx_1, tx_1); // RX, TX

String read_kanban(){
  String input; 
  // while (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) or digitalRead(io1) && digitalRead(io2) && digitalRead(io3))
  // {
  //   digitalWrite(cutoff_sewing, off); // barcode off 
  //   digitalWrite(alarm_on, off); // alarm off 
  // }
  
  if (!digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // 100
  {
    input = "504-A\r";
  }
  else if (!digitalRead(io1) && !digitalRead(io2) && digitalRead(io3)) // 110
  {
    input = "4519001660732\r";
  }
  else if (digitalRead(io1) && digitalRead(io2) && !digitalRead(io3)) // 001
  {
    input = "4519001660735\r";
  }
  else if (digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3)) // 011
  {
    input = "011";
  }
  else if (digitalRead(io1) && !digitalRead(io2) && digitalRead(io3)) // 010
  {
    input = "010";
  }
  else if (!digitalRead(io1) && digitalRead(io2) && !digitalRead(io3)) // 101
  {
    input = "bypass";
  }
  return input; 
}

void lamp_blynk(int lamp, int t_delay)
{
  digitalWrite(lamp, on);
  delay(t_delay);
  digitalWrite(lamp, off);
  delay(t_delay);
}
void setup(void) {
  Serial.begin(115200);
  while (!Serial) ;
  gm65.begin(9600);
  pinMode(io1, INPUT);
  pinMode(io2, INPUT);
  pinMode(io3, INPUT);
  pinMode(io4, INPUT);
  // pinMode(io5, INPUT);
  pinMode(io6, INPUT);

  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(alarm_on, OUTPUT);
  pinMode(cutoff_sewing, OUTPUT);
  pinMode(ready_lamp, OUTPUT);
  
  // digitalWrite(cutoff_sewing, on);
  // digitalWrite(alarm_on, off);
  // digitalWrite(trig1, 1);
  // delay(1000);

}
void loop() {
  digitalWrite(trig1, 1); // barcode off
  digitalWrite(cutoff_sewing, off); // barcode off 
  digitalWrite(alarm_on, off); // alarm off 
  digitalWrite(ready_lamp, off); // ready_lamp off 
  
  while (digitalRead(io6)) // check thread on
  {
    // if no card
    while (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) || digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // no card
    {
      digitalWrite(trig1, 1); // barcode off
      digitalWrite(cutoff_sewing, off); // barcode off 
      digitalWrite(alarm_on, off); // alarm off 
    }
    // Mode by pass
    while (read_kanban() == "bypass")
    {
      digitalWrite(trig1, 1); // barcode off
      digitalWrite(cutoff_sewing, on); // barcode on
      digitalWrite(alarm_on, off); // alarm off 
      if (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) || digitalRead(io1) && digitalRead(io2) && digitalRead(io3) || !digitalRead(io6)) // eject card and thread
        {
          read_card = "";
          read_barcode = "";
          digitalWrite(cutoff_sewing, off); // barcode off
          break;
        } 
    }

    // thread and card ready
    digitalWrite(trig1, 0); // barcode on

    if (gm65.available()) //Checking if any data has been received
    {
      while (gm65.available()) //Read bit by bit until UART buffer is empty
      {
        read_card = read_kanban(); // read card
        read_barcode = gm65.readString(); // read bar code
        
        // int len_card = read_card.length();
        // int len_bar = read_barcode.length();

        // if (read_barcode.compareTo(read_card) = 0)
        
        if (read_barcode == read_card)
        {
          Serial.println(read_barcode);
          Serial.println(read_card);
          // Serial.print("barcode : ");  Serial.println(len_bar);
          // Serial.print("card : ");  Serial.println(len_card);

          while (digitalRead(io6))
          {
            digitalWrite(trig1, 1); // barcode off 
            digitalWrite(alarm_on, off); // alarm off 
            digitalWrite(cutoff_sewing, on); // sewing on 
            if (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) || digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // eject card
            {
              read_card = "";
              read_barcode = "";
              break;
            }
          }          
        }else{
          Serial.print("no : ");  Serial.println(read_barcode);
          Serial.print("no : ");  Serial.println(read_card);
          // Serial.print("barcode : ");  Serial.println(len_bar);
          // Serial.print("card : ");  Serial.println(len_card);

          while (digitalRead(io6))
          {
            digitalWrite(trig1, 1); // barcode off
            digitalWrite(alarm_on, on); // alarm on 
            digitalWrite(cutoff_sewing, off); // sewing off 
            if (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) || digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // eject card
            {
              read_card = "";
              read_barcode = "";
              break;
            }
          }
        }
        delay(5);
      } // end while Read bit by bit until UART buffer is empty
    } // end if Checking if any data has been received 
  } // end while check thread on
} // end loop



