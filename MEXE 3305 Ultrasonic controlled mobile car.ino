const int N1 = 2, N2 = 3, N3 = 4, N4= 5;
const int trigPin = 10;
const int echoPin = 11;
int x, y;

void setup() {
  pinMode(trigPin, INPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(N3, OUTPUT);
  pinMode(N4, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  x = analogRead(trigPin);
  y = analogRead(echoPin);

  if(x < 400) {
    digitalWrite(N1, HIGH);
    digitalWrite(N2, LOW);
    digitalWrite(N3, HIGH);
    digitalWrite(N4, LOW);
  } else if(x < 600){
    digitalWrite(N1, LOW);
    digitalWrite(N2, LOW);
    digitalWrite(N3, LOW);
    digitalWrite(N4, LOW);
  }else {
    digitalWrite(N1, LOW);
    digitalWrite(N2, HIGH);
    digitalWrite(N3, LOW);
    digitalWrite(N4, HIGH);
  }
  if(y < 400) {
    digitalWrite(N1, HIGH);
    digitalWrite(N2, LOW);
    digitalWrite(N3, LOW);
    digitalWrite(N4, HIGH);
  } else if(y < 600){
    digitalWrite(N1, LOW);
    digitalWrite(N2, LOW);
    digitalWrite(N3, LOW);
    digitalWrite(N4, LOW);
  }else {
    digitalWrite(N1, LOW);
    digitalWrite(N2, HIGH);
    digitalWrite(N3, HIGH);
    digitalWrite(N4, LOW);
  }
  
}