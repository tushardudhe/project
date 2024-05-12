#define OLED_RESET LED_BUILTIN
#include <Adafruit_SSD1306.h>
#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
Adafruit_SSD1306 oled(OLED_RESET);
const char* ssid = "ESP8266";
const char* password = "12345678";
String Voltage = "NA", Current = "NA", Power = "NA";
String data = "";
const int relay = D5;
String Load = "DISABLED";
const int ThreshPin = A0;
int Threshold = 0;
int flag = 0;
void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  pinMode(ThreshPin, INPUT);
  digitalWrite(relay, HIGH);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.fillScreen(WHITE);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.print("ENERGY MANAGEMENT SYS");
    oled.setCursor(0, 7);
    oled.print("---------------------");
    oled.setCursor(0, 14);
    oled.print("CONNECTING TO");
    oled.setCursor(0, 24);
    oled.print("WIRELESS NETWORK");
    oled.setCursor(0, 34);
    oled.print("Wi-Fi NAME: ESP8266");
    oled.setCursor(0, 44);
    oled.print("PASSWORD: 12345678");
    oled.display();
    delay(1000);
  }
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.print("ENERGY MANAGEMENT SYS");
  oled.setCursor(0, 7);
  oled.print("---------------------");
  oled.setCursor(0, 14);
  oled.print("CONNECTED TO");
  oled.setCursor(0, 24);
  oled.print("WIRELESS NETWORK");
  oled.setCursor(0, 34);
  oled.print("WELCOME TO MIT, PUNE");
  oled.setCursor(0, 44);
  oled.print("---------------------");
  oled.display();
  delay(5000);
}

void loop() {
  Threshold = map(analogRead(ThreshPin), 0, 1024, 0, 2000);
  Serial.println(Threshold);
  if (Serial.available() > 0)
  {
    data = Serial.readString();
    Serial.println(data);
    Voltage = getValue(data, ',', 0);
    Current = getValue(data, ',', 1);
    Power = getValue(data, ',', 2);
    int PowerInt = Power.toInt();
    Serial.println(Power);
     Serial.println(PowerInt);
     if (PowerInt >= Threshold)
    {
      digitalWrite(relay, LOW);
      delay(4000);
      Load = "ENABLED";
      flag = 1;
    }
    else
    {
      digitalWrite(relay, HIGH);
      delay(4000);
      Load = "DISABLED";
      flag = 0;
    }

    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.print("ENERGY MANAGEMENT SYS");
    oled.setCursor(0, 7);
    oled.print("---------------------");
    oled.setCursor(0, 14);
    oled.print("VOLTAGE: " + (String)Voltage + " Volts");
    oled.setCursor(0, 24);
    oled.print("CURRENT: " + (String)Current + " Amps");
    oled.setCursor(0, 34);
    oled.print("POWER: " + (String)Power + " Watts");
    oled.setCursor(0, 44);
    oled.print("PROTECTION: ");
    oled.print(Load);
    oled.setCursor(0, 54);
    oled.print("THRESHOLD: ");
    oled.print(Threshold);
    oled.print(" Watts");
    oled.display();
    delay(5000);
    cloud();
    //Serial.flush();
  }
  else
  {
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.print("ENERGY MANAGEMENT SYS");
    oled.setCursor(0, 7);
    oled.print("---------------------");
    oled.setCursor(0, 14);
    oled.print("VOLTAGE: " + (String)Voltage + " Volts");
    oled.setCursor(0, 24);
    oled.print("CURRENT: " + (String)Current + " Amps");
    oled.setCursor(0, 34);
    oled.print("POWER: " + (String)Power + " Watts");
    oled.setCursor(0, 44);
    oled.print("PROTECTION: ");
    oled.print(Load);
    oled.setCursor(0, 54);
    oled.print("THRESHOLD: ");
    oled.print(Threshold);
    oled.print(" Watts");
    oled.display();
    delay(2000);
  }
  delay(1000);
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void cloud()
{
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.print("ENERGY MANAGEMENT SYS");
  oled.setCursor(0, 7);
  oled.print("---------------------");
  oled.setCursor(0, 14);
  oled.print("SENDING PARAMETRS");
  oled.setCursor(0, 24);
  oled.print("TO THE WEB");
  oled.setCursor(0, 34);
  oled.print("PLEASE WAIT....");
  oled.display();
  delay(2000);
  HTTPClient http;
  http.begin("http://www.techvegan.in/power-mit/script.php?c=" + (String)Current + "&v=" + (String)Voltage);
  int httpCode = http.GET();
  http.end();
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.print("ENERGY MANAGEMENT SYS");
  oled.setCursor(0, 7);
  oled.print("---------------------");
  oled.setCursor(0, 14);
  oled.print("SENDING PARAMETRS");
  oled.setCursor(0, 24);
  oled.print("TO THE WEB");
  oled.setCursor(0, 34);
  oled.print("DATA SENT....");
  oled.display();
  delay(2000);
}
