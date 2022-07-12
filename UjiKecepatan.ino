#define pwm 6//1

#define sensor 2//2

int tegangan = 12;//4
bool hitung=true;

int interval = 60;
long previousMillis = 0;
long currentMillis = 0;

int nilaiPWM;
float konstan = 0.95;//3
float rpm = 0;
int encoderValue = 0;
int data = 0;
bool n = true;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(pwm, OUTPUT);
  nilaiPWM = (tegangan*1.0/12.0)*255;
  analogWrite(pwm, nilaiPWM);
}

void loop() {
  while (data<=250){
    updateEncoder();
    currentMillis=millis();
    if((currentMillis - previousMillis) > interval){
      rpm = encoderValue*1.0/konstan;
      previousMillis = currentMillis;
      Serial.println(rpm);
//      Serial.print(",");
//      Serial.println(encoderValue);
      encoderValue = 0;
      data++;
    }
  }
  analogWrite(pwm, 0);
}
void updateEncoder(){
  if(digitalRead(sensor)){
    if(hitung){
      encoderValue++;
      hitung=false;
//      Serial.println(encoderValue);
    }
  }else{
    if(!hitung) hitung=true;
  }
}
