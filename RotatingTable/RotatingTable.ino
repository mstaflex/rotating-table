// ---- Includes  --------------------
#include <AccelStepper.h>

// ---- Pin Definitions --------------
#define POTENTIOMETER_POWER_PIN A2
#define POTENTIOMETER_GROUND_PIN A0
#define POTENTIOMETER_SENSE_PIN A1

#define SWITCH_PIN_1 8
#define SWITCH_PIN_2 9

// ---- Defined Variables ------------
#define STEPPER_MAX_SPEED 600.0

// ---- Variables --------------------
AccelStepper stepper;
int analogVal = 0;
bool reverse = false;
bool reverseButtonHoldoff = false;


void setup() {  
   stepper.setMaxSpeed(STEPPER_MAX_SPEED);
   stepper.setSpeed(STEPPER_MAX_SPEED / 2.0);

   pinMode(SWITCH_PIN_1, OUTPUT);
   pinMode(SWITCH_PIN_2, INPUT);
   digitalWrite(SWITCH_PIN_1, HIGH);

   pinMode(POTENTIOMETER_GROUND_PIN, OUTPUT);
   pinMode(POTENTIOMETER_SENSE_PIN, INPUT);
   pinMode(POTENTIOMETER_POWER_PIN, OUTPUT);
   digitalWrite(POTENTIOMETER_GROUND_PIN, LOW);
   digitalWrite(POTENTIOMETER_POWER_PIN, HIGH);
}

void loop() {  
   // execute stepper lib runtime
   stepper.runSpeed();

   // read potentiometer and set speed accordingly
   analogVal = analogRead(POTENTIOMETER_SENSE_PIN);
   if (reverse) {
      stepper.setSpeed((int)((float)(val / 1023.0) * STEPPER_MAX_SPEED));
   } else {
      stepper.setSpeed((int)((float)(-val / 1023.0) * STEPPER_MAX_SPEED));
   }
   
   // read switch and toggle rotational direction
   if (!reverseButtonHoldoff && digitalRead(SWITCH_PIN_2)) {
      reverseButtonHoldoff = true;
      if (reverse) {
         reverse = false;
      } else {
         reverse = true;
      }
   } else {
      reverseButtonHoldoff = false;
   }
}
