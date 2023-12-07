#include <Servo.h>
#include <Stepper.h>
#include <IRremote.h>
#define pin 2

Servo servomotor4; // Servomotor pinza
Servo servomotor3; // Servomotor giro
Servo servomotor2; // Servomotor enmedio
Servo servomotor1; // Servomotor abajo
Stepper motor(2048, 4, 6, 5, 7);

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(pin); 
  pinMode(pin, INPUT);
  servomotor4.attach(8);
  servomotor3.attach(11);
  servomotor2.attach(10);
  servomotor1.attach(9);   
  motor.setSpeed(5);
}

void loop() {
  if (IrReceiver.decode() != 0) {
    Serial.println(IrReceiver.decodedIRData.command); // Imprime el valor del código infrarrojo
    // Verifica el código infrarrojo recibido
    switch (IrReceiver.decodedIRData.command) {
      //motor paso a paso
      case 27: //27
        // Gira a la derecha
        motor.step(512);
        break;
      case 31: //31
        // Gira a la izquierda
        motor.step(-512);
        break;
       //servomotor 1
      case 26: //26
        // Mueve el servomotor1 arriba
        moveServo1Up();
        break;
      case 30: //30
        // Mueve el servomotor1 abajo
        moveServo1Down();
        break;
      //servomotor 2
      case 1: //1
        // Presionado el botón 1, mueve el servomotor2 hacia arriba
        moveServo2up();
        break;
      case 2: //2
        // Presionado el botón 2, mueve el servomotor2 hacia abajo
        moveServo2down();
        break;
      //servomotor 3
      case 3: //3
        // Presionado el botón 1, mueve el servomotor2 hacia arriba
        moveServo3izq();
        break;
      case 4: //4
        // Presionado el botón 2, mueve el servomotor2 hacia abajo
        moveServo3der();
        break;
      //servomotor 4 (pinza)
      case 5: // presionar 5 para abrir la pinza
        moveServo4open();
        break;
      case 6: // presionar 6 para cerrar la pinza
        moveServo4close();
        break;
      
      default:
        // Manejo por defecto, no hacer nada
        break;
    }
    delay(500);
    IrReceiver.resume(); // Continúa recibiendo datos infrarrojos
  }
}
//movimiento servomotor arriba-abajo (servomotor 1)
void moveServo1Up() {
  for (int i = 0; i <= 90; i++) {
    servomotor1.write(i);
    delay(25);
  }
  delay(1000);
}
void moveServo1Down() {
  for (int i = 90; i >= 0; i--) {
    servomotor1.write(i);
    delay(25);
  }
  delay(1000);
}
//movimiento servomotor2
void moveServo2down(){
  for (int i = 0; i <= 90; i++) {
    servomotor2.write(i);
    delay(25);
  }
  delay(1000);
}
void moveServo2up(){
  for (int i = 90; i >= 0; i--) {
    servomotor2.write(i);
    delay(25);
  }
  delay(1000);
}

//movimiento servomotor3
void moveServo3izq(){
  for (int i = 0; i <= 100; i++) {
    servomotor3.write(i);
    delay(25);
  }
  delay(1000);
}
void moveServo3der(){
  for (int i = 100; i >= 0; i--) {
    servomotor3.write(i);
    delay(25);
  }
  delay(1000);
}
// movimiento servomotor4 pinza
void moveServo4open() {
  servomotor4.write(50);  // ajusta el ángulo según sea necesario para abrir la pinza
  delay(1000);  // ajusta el tiempo de espera según sea necesario
}

void moveServo4close() {
  servomotor4.write(0);  // ajusta el ángulo según sea necesario para cerrar la pinza
  delay(1000);  // ajusta el tiempo de espera según sea necesario
}
