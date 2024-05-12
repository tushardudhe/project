
// CURRENT SENSOR
const int sensorIn = A0;
int mVperAmp = 66;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

// VOLTAGE SENSOR
const int vSensor = A1;
double sensorValue1 = 0;
double sensorValue2 = 0;
int crosscount = 0;
int climb_flag = 0;
int val[100];
int max_v = 0;
double VmaxD = 0;
double VeffD = 0;
double Veff = 0;

// POWER
unsigned int Power = 0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  //CURRENT SENSOR
  Voltage = getVPP();
  VRMS = (Voltage / 2.0) * 0.707;
  AmpsRMS = (VRMS * 1000) / mVperAmp;

  // VOLTAGE SENSOR
  for ( int i = 0; i < 100; i++ ) {
    sensorValue1 = analogRead(vSensor);
    if (analogRead(vSensor) > 511) {
      val[i] = sensorValue1;
    }
    else {
      val[i] = 0;
    }
    delay(1);
  }

  max_v = 0;

  for ( int i = 0; i < 100; i++ )
  {
    if ( val[i] > max_v )
    {
      max_v = val[i];
    }
    val[i] = 0;
  }
  if (max_v != 0) {

    VmaxD = max_v;
    VeffD = VmaxD / sqrt(2);
    Veff = (((VeffD - 420.76) / -90.24) * -210.2) + 210.2;
  }
  else {
    Veff = 0;
  }
  VmaxD = 0;
  Power = Veff * AmpsRMS;
  Serial.print(Veff);
  Serial.print(",");
  Serial.print(AmpsRMS);
  Serial.print(",");
  Serial.print(Power);
  delay(60000);
}
float getVPP()
{
  float result;
  int readValue;
  int maxValue = 0;
  int minValue = 1024;

  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000)
  {
    readValue = analogRead(sensorIn);
    if (readValue > maxValue)
    {
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      minValue = readValue;
    }
  }
  result = ((maxValue - minValue) * 5.0) / 1024.0;
  return result;
}
