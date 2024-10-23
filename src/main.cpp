#include <Arduino.h>
#include <ArduinoJson.h>
#include "pin.h"

#ifndef ARDUINO_CPP
#define ARDUINO_CPP
// Define the device ID
String ID = "EC-LB-100-5110-01";
// Define the pin numbers to easily readable names
#define OP1 45
#define OP2 44
#define OP3 43
#define OP4 42
#define OP5 41
#define OP6 40
#define OP7 39
#define OP8 38
#define OP9 37

#define IP1 30
#define IP2 29
#define IP3 28
#define IP4 27
#define IP5 26
#define IP6 25
#define IP7 24
#define IP8 23
#define IP9 22

#define AI1 A1
#define AI2 A2

// Define the pin states based on pullup settings
const int ON = LOW;
const int OFF = HIGH;

// Define the commands received from the server

// Define the Pin class to hold the state of the pins

Pin op1(OP1, "OP1", "OFF");
Pin op2(OP2, "OP2", "OFF");
Pin op3(OP3, "OP3", "OFF");
Pin op4(OP4, "OP4", "OFF");
Pin op5(OP5, "OP5", "OFF");
Pin op6(OP6, "OP6", "OFF");
Pin op7(OP7, "OP7", "OFF");
Pin op8(OP8, "OP8", "OFF");
Pin op9(OP9, "OP9", "OFF");

Pin ip1(IP1, "IP1", "OFF");
Pin ip2(IP2, "IP2", "OFF");
Pin ip3(IP3, "IP3", "OFF");
Pin ip4(IP4, "IP4", "OFF");
Pin ip5(IP5, "IP5", "OFF");
Pin ip6(IP6, "IP6", "OFF");
Pin ip7(IP7, "IP7", "OFF");
Pin ip8(IP8, "IP8", "OFF");
Pin ip9(IP9, "IP9", "OFF");

// Define the array of output pins, output state, and output commands
#define OPARRAYSIZE 9
Pin opArray[OPARRAYSIZE] = {op1, op2, op3, op4, op5, op6, op7, op8, op9};

// Define the array of input pins and input state
#define IPARRAYSIZE 9

Pin ipArray[IPARRAYSIZE] = {ip1, ip2, ip3, ip4, ip5, ip6, ip7, ip8, ip9};

#endif
bool awaitingResponseFromServer = false;

// -------------Setup Start----------------
void setupDigitalPins()
{
  for (int i = 0; i < OPARRAYSIZE; i++)
  {
    pinMode(opArray[i].pinNumber, OUTPUT);
  }
  for (int i = 0; i < IPARRAYSIZE; i++)
  {
    pinMode(ipArray[i].pinNumber, INPUT_PULLUP);
  }
}

void initDigitalPins()
{
  for (int i = 0; i < OPARRAYSIZE; i++)
  {
    digitalWrite(opArray[i].pinNumber, OFF);
  }
  for (int i = 0; i < IPARRAYSIZE; i++)
  {
    digitalWrite(ipArray[i].pinNumber, OFF);
  }
}

void setup()
{
  Serial.begin(9600);  // For debugging
  Serial2.begin(9600); // For writing to Wifi chip which will be used to communicate with the server
  Serial2.setTimeout(1000);
  pinMode(LED_BUILTIN, OUTPUT);

  setupDigitalPins();
  initDigitalPins();
}
// -------------Setup End----------------

// -------------Loop Start----------------
void readDigitalOutput()
{
  for (int i = 0; i < OPARRAYSIZE; i++)
  {
    opArray[i].pinState = digitalRead(opArray[i].pinNumber) == ON ? "ON" : "OFF";
  }
}

void readDigitalInput()
{
  for (int i = 0; i < IPARRAYSIZE; i++)
  {
    ipArray[i].pinState = digitalRead(ipArray[i].pinNumber) == ON ? "ON" : "OFF";
  }
}

String createOutputJSON()
{
  // Create JSON
  JsonDocument doc;
  JsonDocument values;
  doc["ID"] = ID;
  for (int i = 0; i < OPARRAYSIZE; i++)
  {
    values[opArray[i].pinName] = opArray[i].pinState;
  }
  doc["values"] = values;

  String jsonString = "";
  // Serial.println("Output JSON: ");
  // serializeJsonPretty(doc, Serial);
  serializeJson(doc, jsonString);
  return jsonString;
}

int getValue(String command)
{
  if (command == "ON")
  {
    return ON;
  }
  else if (command == "OFF")
  {
    return OFF;
  }
  else
  {
    return -1;
  }
}

void sendData(String jsonString)
{

  Serial.println("Sending JSON to server: " + jsonString);

  // Send JSON to the server
  Serial2.println(jsonString);
  Serial2.flush();
}

void recieveCommands()
{

  if (Serial2.available())
  {
    JsonDocument doc;
    String serialData = Serial2.readStringUntil('\n');
    Serial.println("DATA FROM WIFI Chip: " + serialData);
    if (serialData == "" || serialData == "\n" || serialData.indexOf("COMMAND") <= 0)
    {
      return;
    }
    DeserializationError error = deserializeJson(doc, serialData);
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    else
    {

      int flag1 = getValue(doc["OPCOMMAND1"].as<String>());
      if (flag1 >= 0)
      {
        digitalWrite(op1.pinNumber, flag1);
      }
      int flag2 = getValue(doc["OPCOMMAND2"].as<String>());
      if (flag2 >= 0)
      {
        digitalWrite(op2.pinNumber, flag2);
      }
      int flag3 = getValue(doc["OPCOMMAND3"].as<String>());
      if (flag3 >= 0)
      {
        digitalWrite(op3.pinNumber, flag3);
      }
      int flag4 = getValue(doc["OPCOMMAND4"].as<String>());
      if (flag4 >= 0)
      {
        digitalWrite(op4.pinNumber, flag4);
      }
      int flag5 = getValue(doc["OPCOMMAND5"].as<String>());
      if (flag5 >= 0)
      {
        digitalWrite(op5.pinNumber, flag5);
      }
      int flag6 = getValue(doc["OPCOMMAND6"].as<String>());
      if (flag6 >= 0)
      {
        digitalWrite(op6.pinNumber, flag6);
      }
      int flag7 = getValue(doc["OPCOMMAND7"].as<String>());
      if (flag7 >= 0)
      {
        digitalWrite(op7.pinNumber, flag7);
      }
      int flag8 = getValue(doc["OPCOMMAND8"].as<String>());
      if (flag8 >= 0)
      {
        digitalWrite(op8.pinNumber, flag8);
      }
      int flag9 = getValue(doc["OPCOMMAND9"].as<String>());
      if (flag9 >= 0)
      {
        digitalWrite(op9.pinNumber, flag9);
      }
    }
  }
}
String prevJSONString = "";
unsigned long lastMeasure = 0;
unsigned long now = 0;

void loop()
{

  recieveCommands();
  delay(200);
  readDigitalOutput();
  String jsonString = createOutputJSON();
  now = millis();
  // Publishes new temperature and humidity every 5 seconds

  if (jsonString == prevJSONString && now - lastMeasure < 5000)
  {
    return;
  }
  lastMeasure = now;
  sendData(jsonString);
  prevJSONString = jsonString;

  Serial.println(" ************* Loop end ************* ");
}
