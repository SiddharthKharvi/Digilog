#define CH1 2
#define CH2 3
#define CH3 4
#define CH4 5
#define CH5 6



#define RP 7
#define RM 8
#define LP 9
#define LM 12

#define SPEED 150
int LSpeed = 0, RSpeed = 0;
int Steering = 0, Throttle = 0, C1 = 0, C2 = 0, C3 = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(15, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  //  digitalWrite(RP, HIGH);
  //  digitalWrite(LP, HIGH);
  //
  //  digitalWrite(RM, LOW);
  //  digitalWrite(LM, LOW);




  Serial.begin(9600);
  Serial.println("READY");
}

void loop() {
  Steering = map(pulseIn(2, HIGH), 870, 2120, -40, 40);
  Throttle = map(pulseIn(3, HIGH), 870, 2120, -40, 40);
  C1 = map(pulseIn(4, HIGH), 870, 2120, -40, 40);
  C2 = map(pulseIn(5, HIGH), 870, 2120, -40, 40);
  C3 = map(pulseIn(6, HIGH), 870, 2120, -40, 40);
  //Serial.println("C1:"+String(C3));
  if (C1 >= 0) {
    digitalWrite(15, 1);
    Serial.println("C1");
  }
  else {
    digitalWrite(15, 0);
  }
  if (C2 >= 0) {
    digitalWrite(17, 1);
    Serial.println("C2");
  }
  else {
    digitalWrite(17, 0);
  }
  if (C3 >= 0) {
    digitalWrite(18, 1);
    Serial.println("C3");
  }
  else {
    digitalWrite(18, 0);
  }

  LSpeed = Throttle  ;
  RSpeed = Throttle ;

  LSpeed = LSpeed - Steering ;
  RSpeed = RSpeed + Steering;

  if ((RSpeed >= 1)) {
    digitalWrite(RP, HIGH);
    digitalWrite(RM, LOW);
  }
  else {
    digitalWrite(RP, LOW);
    digitalWrite(RM, HIGH);
  }

  if ((LSpeed >= 1)) {
    digitalWrite(LP, HIGH);
    digitalWrite(LM, LOW);
  }
  else {
    digitalWrite(LP, LOW);
    digitalWrite(LM, HIGH);
  }

  LSpeed = abs(LSpeed);
  RSpeed = abs(RSpeed);
  LSpeed = map(LSpeed, 0, 40, 0, 255);
  RSpeed = map(RSpeed, 0, 40, 0, 255);
  if (LSpeed >= 255) {
    LSpeed = 255;
  }
  if (RSpeed >= 255) {
    RSpeed = 255;
  }

  analogWrite(10, RSpeed);
  analogWrite(11, LSpeed);

  //
  //
  //
  //Serial.println(String(LSpeed) + "||" + String(RSpeed));

  delay(10);
}

//if (C1 >= 0) {
//    digitalWrite(14, HIGH);
//  }
//  else {
//    digitalWrite(14, LOW);
//  }
//  if (C2 >= 0) {
//    digitalWrite(15, HIGH);
//  }
//  else {
//    digitalWrite(15, LOW);
//  }
//  if (C3 >= 0) {
//    digitalWrite(16, HIGH);
//  }
//  else {
//    digitalWrite(16, LOW);
//  }
