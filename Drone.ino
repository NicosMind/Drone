*
#include <SoftwareSerial.h>
#include <Servo.h>

#define rxPin 10
#define txPin 11
#define Moteur_A 2
#define Moteur_B 4
#define ENA 5

SoftwareSerial BlueT(rxPin, txPin);
Servo ServoDir;

char message;
int PWM = 0;
int MoteurSpeed = 0;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    BlueT.begin(38400);
    Serial.println("ENTER AT Commands:");
    pinMode(Moteur_A, OUTPUT);
    pinMode(Moteur_B, OUTPUT);
    pinMode(ENA, OUTPUT);
    ServoDir.attach(9);
    ServoDir.write(90);
}

void loop() {

    if (BlueT.available()) {
        message = BlueT.read();
        Serial.print(message);
        switch (message) {

        case 'X':
            PWM = BlueT.parseInt();
            if (PWM > 131) {
                MoteurSpeed = map(PWM, 128, 255, 0, 255);
                Serial.println(PWM);
                Serial.println(MoteurSpeed);
                digitalWrite(Moteur_A, LOW);
                digitalWrite(Moteur_B, HIGH);
                analogWrite(ENA, MoteurSpeed);
            }
            else if (PWM < 125) {
                MoteurSpeed = map(PWM, 128, 0, 0, 255);
                Serial.println(PWM);
                Serial.println(MoteurSpeed);
                digitalWrite(Moteur_A, HIGH);
                digitalWrite(Moteur_B, LOW);
                analogWrite(ENA, MoteurSpeed);
            }
            else if (125 < PWM < 131) {
                MoteurSpeed = 0;
                digitalWrite(Moteur_A, LOW);
                digitalWrite(Moteur_B, LOW);
                analogWrite(ENA, MoteurSpeed);
            }
            break;


        case 'Y':
            PWM = BlueT.parseInt();
            PWM = map(PWM, 0, 255, 0, 180);
            PWM = constrain(PWM, 30, 150);
            ServoDir.write(PWM);
            delay(15);
            break;

        }
    }
}