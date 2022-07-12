//Y=0.25982X+38.49091
#define pwm 6

#define sensor 2

int target = 70;
//float point = 0;
bool hitung=true;

int interval = 60;
long previousMillis = 0;
long currentMillis = 0;

float newPWM=0;
float nilaiPWM=0;
float konstan = 1.02;
float rpm = 0;
int encoderValue = 0;
int data = 0;

float kp = 0.095;
float ki = 0.003;
float error = 0;
float lastError = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(pwm, OUTPUT);
//  point = (target*102.0)/100.0;
}

void loop() {
  while (data<=250){
    updateEncoder();
    currentMillis=millis();
    if((currentMillis - previousMillis) > interval){
      rpm = encoderValue*1.0/konstan;
      previousMillis = currentMillis;
//      error = point-encoderValue;
      error = target-rpm;
      newPWM = kp*error-ki*lastError;
      nilaiPWM = nilaiPWM+newPWM;
      if(nilaiPWM>255) nilaiPWM = 255;
      else if(nilaiPWM<0) nilaiPWM = 0;
      Serial.print(rpm);
      Serial.print(",");
      analogWrite(pwm, int(nilaiPWM));
      lastError=error;
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
    }
  }else{
    if(!hitung) hitung=true;
  }
}
