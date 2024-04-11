#include <Servo.h>

#define TRIGGER_PIN 11
#define ECHO_PIN 10
#define LDR_PIN A0
#define SERVO_PIN 12

Servo servo_12;

/** Setup function ***********************/
void setup() {
  // Attach the pin selected from blockly
  servo_12.attach(12);

  pinMode(11, OUTPUT);
  pinMode(10, INPUT);

  // Servomotor write angle and delay code
  servo_12.write(0);
  delay(1000);
}

/**** Función para medir distancia con ultrasonido**/
double fnc_ultrasonic_distance(int _t, int _e, String _u) {
  unsigned long dur=0;
  digitalWrite(_t, LOW);
  delayMicroseconds(5);
  digitalWrite(_t, HIGH);
  delayMicroseconds(10);
  digitalWrite(_t, LOW);
  dur = pulseIn(_e, HIGH, 18000);
  if (dur == 0)
    return 999.0;
  if (_u == "cm")
    return (dur/57);
  else if (_u == "in")
    return (dur/57) * (1 / 2.54);
}

void loop() {
  long distance = fnc_ultrasonic_distance(TRIGGER_PIN,ECHO_PIN,"cm");
  //Serial.println("Distancia: " ,distance);

  int intensidadLuz = analogRead(LDR_PIN);
  //Serial.println(intensidadLuz);

  if(distance >= 80 && intensidadLuz > 1000){
    servo_12.write(180);
    delay(100);
  }
  else if (distance <= 30 && intensidadLuz > 500){
    servo_12.write(60);
    delay(100);
  }
  else if (distance <= 2 && intensidadLuz < 200){
    servo_12.write(90);
    delay(100);
  }