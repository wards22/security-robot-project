// Main code for secruity robot project
// Included files from Elegoo kit
// Code for line tracking from Elegoo
// Code for servo sweep from Arduino forums
// Modified and Adapted by Scott Ward
// Makes the Robot Car follow a 'patrol route'
// And perform a sweep with its camera

#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.h"
#include <Servo.h>

// Pin Constants
const int servoPin = 10;

// Limits the servos movements
const int servoMinDegrees = 90;
const int servoMaxDegrees = 180;

//------Variables to control servo-------------//
Servo myservo;  // Create servo object to control a servo 

int servoPosition = 180;    // The current angle of the servo - starting at 90.
int servoInterval = 80;     // Millisecs between servo moves
int servoDegrees = 2;       // Amount servo moves at each step 
                            //    Will be changed to negative value for movement in the other direction
unsigned long currentMillis = 0;       // Stores the value of millis() in each iteration of loop()
unsigned long previousServoMillis = 0; // The time when the servo was last moved
//--------------------------------------------//

void setup()
{
  // Initiate the servo and point it straight ahead:
  myservo.write(servoPosition); // Sets the initial position of the servo
  myservo.attach(servoPin);

  // Initiates line tracking mode
  Application_FunctionSet.ApplicationFunctionSet_Init();
}

void loop()
{
  currentMillis = millis();
  servoSweep();

  delay(10);

  // These functions are in separate drives and header files from Elegoo
  Application_FunctionSet.ApplicationFunctionSet_Tracking(); 
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
}

void servoSweep() {

      // Nothing happens unless the interval has expired
      // The value of currentMillis was set in loop()
  
  if (currentMillis - previousServoMillis >= servoInterval) {
        // time for the servo to move again
    previousServoMillis += servoInterval;
    
    servoPosition = servoPosition + servoDegrees; // servoDegrees might be negative

    if ((servoPosition >= servoMaxDegrees) || (servoPosition <= servoMinDegrees))  {
          // If the servo is at either extreme change the sign of the degrees to make it move the other way
      servoDegrees = - servoDegrees; // reverse direction
          // And update the position to ensure it is within range
      servoPosition = servoPosition + servoDegrees; 
    }
    
        // Make the servo move to the next position
    myservo.write(servoPosition);
        // And record the time when the move happened

  } 
}
