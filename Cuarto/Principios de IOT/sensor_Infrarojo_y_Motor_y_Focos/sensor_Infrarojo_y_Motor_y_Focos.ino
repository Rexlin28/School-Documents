#include <Servo.h>
const int foquito1 = 6;
const int foquito2 = 7;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;

Servo myServo; // Crea un objeto de tipo Servo

void setup() {
  Serial.begin(9600); // Inicia la comunicación serie a 9600 baudios
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(foquito1, OUTPUT); // Establece foquito1 como salida
  pinMode(foquito2, OUTPUT);
  myServo.attach(8); // Asigna el pin del microservo SG90 (pin 8)
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  
  Serial.print("Distance: ");
  Serial.print(distanceInch);
  Serial.println(" inch");

  // Mapea la distancia medida al rango de grados del servo (0 a 180)
  int angle = map(distanceCm, 0, 200, 0, 180);
  myServo.write(angle); // Mueve el servo a la posición correspondiente
  delay(500); // Añade un pequeño retardo para evitar sobrecargar el monitor serie

  if(distanceCm > 200){
    digitalWrite(foquito1, HIGH);
    digitalWrite(foquito2, LOW);
  }else{
    digitalWrite(foquito1,LOW);
    digitalWrite(foquito2, HIGH);
  }
}