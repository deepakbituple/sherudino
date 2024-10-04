#include <Arduino.h>
#include <ArduinoJson.h>

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
const int ON = LOW;
const int OFF = HIGH;

String OPSTATECOMMAND1 = "OFF";
String OPSTATECOMMAND2 = "OFF";
String OPSTATECOMMAND3 = "OFF";
String OPSTATECOMMAND4 = "OFF";
String OPSTATECOMMAND5 = "OFF";

String OPSTATECOMMAND6 = "OFF";
String OPSTATECOMMAND7 = "OFF";
String OPSTATECOMMAND8 = "OFF";
String OPSTATECOMMAND9 = "OFF";

String OPSTATE1 = "OFF";
String OPSTATE2 = "OFF";
String OPSTATE3 = "OFF";
String OPSTATE4 = "OFF";

String OPSTATE5 = "OFF";
String OPSTATE6 = "OFF";
String OPSTATE7 = "OFF";
String OPSTATE8 = "OFF";
String OPSTATE9 = "OFF";

String IPSTATE1 = "OFF";
String IPSTATE2 = "OFF";
String IPSTATE3 = "OFF";
String IPSTATE4 = "OFF";

String IPSTATE5 = "OFF";
String IPSTATE6 = "OFF";
String IPSTATE7 = "OFF";
String IPSTATE8 = "OFF";
String IPSTATE9 = "OFF";

class Pin
{
public:
  int pinNumber;
  String pinName;
  String pinState;
  String pinCommand;
  Pin(int pinNumber, String pinName, String pinState, String pinCommand)
  {
    this->pinNumber = pinNumber;
    this->pinName = pinName;
    this->pinState = pinState;
    this->pinCommand = pinCommand;
  }
};

Pin op1(OP1, "OP1", OPSTATE1, OPSTATECOMMAND1);
Pin op2(OP2, "OP2", OPSTATE2, OPSTATECOMMAND2);
Pin op3(OP3, "OP3", OPSTATE3, OPSTATECOMMAND3);
Pin op4(OP4, "OP4", OPSTATE4, OPSTATECOMMAND4);
Pin op5(OP5, "OP5", OPSTATE5, OPSTATECOMMAND5);
Pin op6(OP6, "OP6", OPSTATE6, OPSTATECOMMAND6);
Pin op7(OP7, "OP7", OPSTATE7, OPSTATECOMMAND7);
Pin op8(OP8, "OP8", OPSTATE8, OPSTATECOMMAND8);
Pin op9(OP9, "OP9", OPSTATE9, OPSTATECOMMAND9);

Pin ip1(IP1, "IP1", IPSTATE1, "");
Pin ip2(IP2, "IP2", IPSTATE2, "");
Pin ip3(IP3, "IP3", IPSTATE3, "");
Pin ip4(IP4, "IP4", IPSTATE4, "");
Pin ip5(IP5, "IP5", IPSTATE5, "");
Pin ip6(IP6, "IP6", IPSTATE6, "");
Pin ip7(IP7, "IP7", IPSTATE7, "");
Pin ip8(IP8, "IP8", IPSTATE8, "");
Pin ip9(IP9, "IP9", IPSTATE9, "");

// Define the array of output pins, output state, and output commands
#define OPARRAYSIZE 9
Pin opArray[OPARRAYSIZE] = {op1, op2, op3, op4, op5, op6, op7, op8, op9};

// Define the array of input pins and input state
#define IPARRAYSIZE 9

Pin ipArray[IPARRAYSIZE] = {ip1, ip2, ip3, ip4, ip5, ip6, ip7, ip8, ip9};

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

void initDigitalOutputPins()
{
  for (int i = 0; i < OPARRAYSIZE; i++)
  {
    digitalWrite(opArray[i].pinNumber, ON);
  }
  for (int i = 0; i < IPARRAYSIZE; i++)
  {
    digitalWrite(ipArray[i].pinNumber, OFF);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  setupDigitalPins();
  initDigitalOutputPins();
}

void readDigitalOutput()
{
  for (int i = 0; i < OPARRAYSIZE; i++)
  {
    if (digitalRead(opArray[i].pinNumber) == ON)
    {
      opArray[i].pinState = "ON";
    }
    else
    {
      opArray[i].pinState = "OFF";
    }
  }
}

void readDigitalInput()
{
  for (int i = 0; i < IPARRAYSIZE; i++)
  {
    if (digitalRead(ipArray[i].pinNumber) == ON)
    {
      ipArray[i].pinState = "ON";
    }
    else
    {
      ipArray[i].pinState = "OFF";
    }
  }
}



void createOutputJSON()
{
  // Create JSON
  JsonDocument doc;
JsonDocument values;

  for(int i = 0; i < OPARRAYSIZE; i++) {
    values[opArray[i].pinName] = opArray[i].pinState;
  }
  doc["values"] = values;

  Serial.println("Output JSON: ");
  serializeJsonPretty(doc, Serial);
}

void loop()
{
  // digitalWrite(LED_BUILTIN, LOW);
  readDigitalOutput();
  // print Digital Output State;
  // for (int i = 0; i < OPARRAYSIZE; i++) {
  //   Serial.println("Output Pin: "+ String(opArray[i]) + " State: " + opStateArray[i]);

  // }
  // Sleep 1 second
  delay(1000);
  createOutputJSON();
  Serial.println(" ************* Loop end ************* ");
}
