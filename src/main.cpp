#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

AsyncWebServer server(8888);
// WiFiServer server(8888);
// DI
int io1 = 13; // D13
// int io2 = 12; // D12 do not use
int io2 = 14; // D14
int io3 = 27; // D27
int io4 = 26; // D26
int io5 = 33; // D33
int io6 = 25; // D25

// DQ
int alarm_ = 23; // alarm D23
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

// wifi setting
// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "GM65001";
const char* password = "357113800";

// const char* ssid = "TrueGigatexFiber_2.4G_6f8";
// const char* password = "0000099999";

// IPAddress local_ip(192,168,10,100);
// IPAddress gateway(192,168,10,1);
// IPAddress subnet(255,255,255,0);

const char* PARAM_STRING1 = "param_1"; // 100
const char* PARAM_STRING2 = "param_2"; // 110
const char* PARAM_STRING3 = "param_3"; // 001
const char* PARAM_STRING4 = "param_4"; // 011
const char* PARAM_STRING5 = "param_5"; // 010
const char* PARAM_STRING6 = "param_6"; // 101

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

// Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "param_1"){
    return readFile(SPIFFS, "/param_1.txt");
  }
  else if(var == "param_2"){
    return readFile(SPIFFS, "/param_2.txt");
  }
  else if(var == "param_3"){
    return readFile(SPIFFS, "/param_3.txt");
  }
  else if(var == "param_4"){
    return readFile(SPIFFS, "/param_4.txt");
  }
  else if(var == "param_5"){
    return readFile(SPIFFS, "/param_5.txt");
  }
  else if(var == "param_6"){
    return readFile(SPIFFS, "/param_6.txt");
  }
  return String();
}

String read_kanban(){
  String input; 
  String code;
  // while (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) or digitalRead(io1) && digitalRead(io2) && digitalRead(io3))
  // {
  //   digitalWrite(cutoff_sewing, off); // barcode off 
  //   digitalWrite(alarm_on, off); // alarm off 
  // }
  
  if (!digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // 100
  {
    code = readFile(SPIFFS, "/param_1.txt");
    input = code+"\r";
  }
  else if (!digitalRead(io1) && !digitalRead(io2) && digitalRead(io3)) // 110
  {
    code = readFile(SPIFFS, "/param_2.txt");
    input = code+"\r";
  }
  else if (digitalRead(io1) && digitalRead(io2) && !digitalRead(io3)) // 001
  {
    code = readFile(SPIFFS, "/param_3.txt");
    input = code+"\r";
  }
  else if (digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3)) // 011
  {
    code = readFile(SPIFFS, "/param_4.txt");
    input = code+"\r";
  }
  else if (digitalRead(io1) && !digitalRead(io2) && digitalRead(io3)) // 010
  {
    code = readFile(SPIFFS, "/param_5.txt");
    input = code+"\r";
  }
  else if (!digitalRead(io1) && digitalRead(io2) && !digitalRead(io3)) // 101
  {
    code = readFile(SPIFFS, "/param_6.txt");
    input = code+"\r";
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
  while (!Serial);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  gm65.begin(9600);
  pinMode(io1, INPUT);
  pinMode(io2, INPUT);
  pinMode(io3, INPUT);
  pinMode(io4, INPUT);

  // pinMode(io5, INPUT);
  pinMode(io6, INPUT);

  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(alarm_, OUTPUT);
  pinMode(cutoff_sewing, OUTPUT);
  pinMode(ready_lamp, OUTPUT);

  digitalWrite(trig1, off); 
  digitalWrite(cutoff_sewing, off);
  digitalWrite(alarm_, off);
  digitalWrite(ready_lamp, off);

  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  // if (WiFi.waitForConnectResult() != WL_CONNECTED) {
  //   Serial.println("WiFi Failed!");
  //   return;
  // }
  // Serial.println();
  // Serial.print("IP Address: ");
  // Serial.println(WiFi.localIP());

  // WiFi.mode(WIFI_AP);
  // WiFi.softAP(ssid, password);
  while (digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // 111
  {
    // Serial.print("Setting AP (Access Point)…");
    WiFi.softAP(ssid, password);
    // WiFi.softAPConfig(local_ip, gateway, subnet);
    IPAddress IP = WiFi.softAPIP();
    // Serial.print("AP IP address: ");
    // Serial.println(IP);
    
    // Send web page with input fields to client
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage;
      // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
      if (request->hasParam(PARAM_STRING1)) {
        inputMessage = request->getParam(PARAM_STRING1)->value();
        writeFile(SPIFFS, "/param_1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(PARAM_STRING2)) {
        inputMessage = request->getParam(PARAM_STRING2)->value();
        writeFile(SPIFFS, "/param_2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(PARAM_STRING3)) {
        inputMessage = request->getParam(PARAM_STRING3)->value();
        writeFile(SPIFFS, "/param_3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(PARAM_STRING4)) {
        inputMessage = request->getParam(PARAM_STRING4)->value();
        writeFile(SPIFFS, "/param_4.txt", inputMessage.c_str());
      }
      else if (request->hasParam(PARAM_STRING5)) {
        inputMessage = request->getParam(PARAM_STRING5)->value();
        writeFile(SPIFFS, "/param_5.txt", inputMessage.c_str());
      }
      else if (request->hasParam(PARAM_STRING6)) {
        inputMessage = request->getParam(PARAM_STRING6)->value();
        writeFile(SPIFFS, "/param_6.txt", inputMessage.c_str());
      }
      else {
        inputMessage = "No message sent";
      }
      // Serial.println(inputMessage);
      // request->send(200, "text/text", inputMessage);
      request->send(SPIFFS, "/index.html", String(), false, processor);
    });
    server.onNotFound(notFound);
    server.begin();
    
    break;
  }

  // Testing file updoad

  // File file = SPIFFS.open("/param_2.txt");
  // if(!file){
  //   Serial.println("Failed to open file for reading");
  //   return;
  // }  
  // Serial.println("File Content:");
  // while(file.available()){
  //   Serial.write(file.read());
  // }
  // file.close();
}
void loop() {
  digitalWrite(trig1, off); // barcode off
  digitalWrite(cutoff_sewing, off); //  off 
  digitalWrite(alarm_, off); // alarm off 
  digitalWrite(ready_lamp, off); // ready_lamp off 
  // Serial.println(read_kanban());
  delay(50);

  while (digitalRead(io6)) // check thread on
  {
    // if no card
    while (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3)) // no card
    // while (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) || digitalRead(io1) && digitalRead(io2) && digitalRead(io3)) // no card
    {
      digitalWrite(trig1, 1); // barcode off
      digitalWrite(cutoff_sewing, off); // barcode off 
      digitalWrite(alarm_, off); // alarm off 
      lamp_blynk(ready_lamp, 500);
      break;
    }
    // Mode by pass
    while (read_kanban() == "bypass")
    {
      digitalWrite(trig1, 1); // barcode off
      digitalWrite(cutoff_sewing, on); // barcode on
      digitalWrite(ready_lamp, on); // ready_lamp off 
      digitalWrite(alarm_, off); // alarm off 
      if (!digitalRead(io1) && !digitalRead(io2) && !digitalRead(io3) || digitalRead(io1) && digitalRead(io2) && digitalRead(io3) || !digitalRead(io6)) // eject card and thread
        {
          read_card = "";
          read_barcode = "";
          digitalWrite(cutoff_sewing, off); // barcode off
          digitalWrite(ready_lamp, off); // ready_lamp off 
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
            digitalWrite(alarm_, off); // alarm off 
            digitalWrite(cutoff_sewing, on); // sewing on 
            digitalWrite(ready_lamp, on); // ready_lamp off 
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
            digitalWrite(alarm_, on); // alarm on 
            digitalWrite(cutoff_sewing, off); // sewing off 
            digitalWrite(ready_lamp, off); // ready_lamp off
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
