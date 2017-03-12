// Declare Servos
#include <Servo.h>
Servo clawServo;
Servo armServo;

// Declare cmdString
String cmdString;

// Initial set-up
void setup() {
  // Set Serial baud
  Serial.begin(9600);

  // Attach Servos to Arduino pins
  clawServo.attach(5);
  armServo.attach(6);

  // Set inital servo positions
  openClaw();
  armServo.write(6);
}

// Proccess code
void loop() {
  // Compile cmdString from user input
  while ( Serial.available() ) {
    char c = Serial.read();
    cmdString += c;
    delay(2);
  }

  // Process cmdString
  if ( cmdString.length() > 0 ) {
    // set node and action strings
    String node = getValue(cmdString, ':', 0);
    String action = getValue(cmdString, ':', 1);

    // Process commands
    if ( node == "claw" ) {
      if ( action == "open" ) {
        openClaw();
      } else if ( action == "close" ) {
        closeClaw();
      } else {
        Serial.println( "Moving clawServo " + action + " degrees" );
        clawServo.write( action.toInt() );
      }
    } else if ( node == "arm" ) {
      if ( action == "raise" ) {
        raiseArm();
      } else if ( action == "lower" ) {
        lowerArm();
      } else {
        Serial.println( "Moving armServo " + action + " degrees" );
        armServo.write( action.toInt() );
      }
    }

    cmdString="";
  }
}

// Split cmdString into node and action
String getValue( String data, char separator, int index ) {
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// Set clawServo to open position
void openClaw() {
    Serial.println( "Open clawServo" );
    clawServo.write( 108 );
}

// Set clawServo to close position
void closeClaw() {
    Serial.println( "Close clawServo" );
    clawServo.write( 80 );
}

// Set armServo to up position
void raiseArm() {
    Serial.println( "Raise armServo" );
    for(int x = 6; x < 186; x = x + 6){
      armServo.write( x );
      delay(60);
    }
}

// Set armServo to down position
void lowerArm() {
    Serial.println( "Lower armServo" );
    for(int x = 180; x > 0; x = x - 6){
      armServo.write( x );
      delay(60);
    }
}
