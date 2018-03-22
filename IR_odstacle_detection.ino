
int LED = D1; 
int BUZZER=D2;
int obstaclePin = D5;  
int hasObstacle = HIGH;  

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(obstaclePin, INPUT);
  Serial.begin(9600);  
}
void loop() {
  hasObstacle = digitalRead(obstaclePin); 
  if (hasObstacle == HIGH) 
  {
    digitalWrite(LED, HIGH);
    analogWrite(BUZZER, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
    analogWrite(BUZZER, LOW);
  }
  delay(10);
}
