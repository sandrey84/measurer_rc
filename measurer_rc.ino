const int enA = 2;
const int in1 = 22;
const int in2 = 24;
const int in3 = 23;
const int in4 = 25;
const int enB = 3;

const int CHANNEL_1_PIN = 36;
const int CHANNEL_2_PIN = 34;

const int MIN_MOTOR = 47;
const int MAX_MOTOR = 255;
const int CHANNEL_MEASURE_MICROS = 50000;
const int CHANNEL_MIN = 1000;
const int CHANNEL_MAX = 1960;
const int CHANNEL_MID = (CHANNEL_MAX + CHANNEL_MIN) / 2;

int ch1Value = 0;
int ch2Value = 0;

void setup() {
  pinMode(CHANNEL_1_PIN, INPUT);
  pinMode(CHANNEL_2_PIN, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);  
  pinMode(in4, OUTPUT);
///  Serial.begin(9600);
}

void loop() {
  ch1Value = pulseIn(CHANNEL_1_PIN, HIGH, CHANNEL_MEASURE_MICROS);
  ch2Value = pulseIn(CHANNEL_2_PIN, HIGH, CHANNEL_MEASURE_MICROS);
  setMotorsSpeed();
  
//  Serial.println("ch1=" + String(ch1Value) + ", ch2=" + String(ch2Value));
}

void setMotorsSpeed() {
   if(ch1Value > CHANNEL_MAX) {
      ch1Value = CHANNEL_MAX;
   }
   if(ch2Value > CHANNEL_MAX) {
      ch2Value = CHANNEL_MAX;
   }
   if(ch1Value < CHANNEL_MIN) {
      ch1Value = CHANNEL_MIN;
   }
   if(ch2Value < CHANNEL_MIN) {
      ch2Value = CHANNEL_MIN;
   }

   if (abs(ch1Value - CHANNEL_MID) < 50) {
      analogWrite(enB, 0);
   } else {
      analogWrite(enB, ch1Value > CHANNEL_MID 
          ? map(ch1Value, CHANNEL_MID, CHANNEL_MAX, MIN_MOTOR, MAX_MOTOR) 
          : map(ch1Value, CHANNEL_MIN, CHANNEL_MID, MAX_MOTOR, MIN_MOTOR));
      digitalWrite(in1, ch1Value > CHANNEL_MID ? LOW : HIGH);
      digitalWrite(in2, ch1Value > CHANNEL_MID ? HIGH : LOW);
   }

   if (abs(ch2Value - CHANNEL_MID) < 50) {
      analogWrite(enA, 0);
   } else {
     analogWrite(enA, ch2Value > CHANNEL_MID 
          ? map(ch2Value, CHANNEL_MID, CHANNEL_MAX, MIN_MOTOR, MAX_MOTOR) 
          : map(ch2Value, CHANNEL_MIN, CHANNEL_MID, MAX_MOTOR, MIN_MOTOR));
     digitalWrite(in3, ch2Value > CHANNEL_MID ? LOW : HIGH);
     digitalWrite(in4, ch2Value > CHANNEL_MID ? HIGH : LOW);
   }
}
