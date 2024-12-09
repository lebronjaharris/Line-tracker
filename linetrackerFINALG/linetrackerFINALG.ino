// Pin Definitions for Motor Control

const int pinA = 5;  // Motor A speed (PWM)

const int pinB = 6;  // Motor B speed (PWM)

const int pinC = 7;  // Motor A direction

const int pinD = 8;  // Motor B direction

const int pinE = 3;  // Standby pin to stop the whole car

int carState = 1;    // Start with the car on (motors enabled)

int carSpeed = 65;   // Initial speed of the car (range: 0 to 255)

unsigned long pTime = 0;

unsigned long pDetectionTime = 0;



const int IR_RECEIVE_PIN = 9;  // IR receiver pin



// Global sensor variables

int right = A0;

int middle = A1;

int left = A2;



void setup() {

  Serial.begin(9600);

}



void loop() {



  // Output sensor readings to serial monitor for debugging

  Serial.print("Right Sensor = ");

  Serial.println(analogRead(right));

  Serial.print("Middle Sensor = ");

  Serial.println(analogRead(middle));

  Serial.print("Left Sensor = ");

  Serial.println(analogRead(left));





  // If middle sensor detects the line, move forward

  if (analogRead(middle) > 600 && analogRead(middle) < 1000) {

    forward();

  } else if (analogRead(right) > 650 && analogRead(right) < 1000 && analogRead(middle) > 600 && analogRead(middle) < 1000) {

    forward();

  } else if (analogRead(left) > 650 && analogRead(left) < 1000 && analogRead(middle) > 600 && analogRead(middle) < 1000) {

    forward();

  }

  // If the right sensor detects the line, move right

  else if (analogRead(right) > 650 && analogRead(right) < 1000 && analogRead(middle) < 600) {

    rightTurn();

  }

  // If the left sensor detects the line, move left

  else if (analogRead(left) > 650 && analogRead(left) < 1000 && analogRead(middle) < 600) {

    leftTurn();

  }

  // Car is in the air (no line detected on all sensors)

  else if (analogRead(middle) > 1000 && analogRead(left) > 1000 && analogRead(right) > 1000) {

    stopMotors();

    //car searches for tracking line



  } else if (analogRead(left) < 600 && analogRead(right) < 600 && analogRead(middle) < 600) {





    unsigned long DetectionTime = millis();



    Serial.println(DetectionTime);



    if (DetectionTime - pDetectionTime <= 600) {

      rightTurn();

    }

    else if (DetectionTime - pDetectionTime >= 600 && DetectionTime - pDetectionTime <= 3600) {

      leftTurn();

    }

    else if (DetectionTime - pDetectionTime >= 3600 && DetectionTime - pDetectionTime <= 6600) {

      rightTurn();

    }

    else if (DetectionTime - pDetectionTime >= 6600 && DetectionTime - pDetectionTime <= 7000) {

      stopMotors();

    } else if (DetectionTime - pDetectionTime >= 7000) {

      pDetectionTime = DetectionTime;

    }

  }

}





// Move forward

void forward() {

  digitalWrite(pinC, HIGH);     // Motor A direction (forward)

  analogWrite(pinA, carSpeed);  // Motor A speed (set speed)

  digitalWrite(pinD, HIGH);     // Motor B direction (forward)

  analogWrite(pinB, carSpeed);  // Motor B speed (set speed)



  digitalWrite(pinE, carState);  // Enable car (turn on motors if carState is 1)

}



// Function to turn the car to the right

void rightTurn() {

  digitalWrite(pinC, LOW);            // Motor A direction (backward)

  analogWrite(pinA, carSpeed);  // Motor A speed (set speed)

  digitalWrite(pinD, HIGH);           // Motor B direction (forward)

  analogWrite(pinB, carSpeed);  // Motor B speed (set speed)

  digitalWrite(pinE, carState);       // Enable car (turn on motors if carState is 1)

}



// Move left

void leftTurn() {

  digitalWrite(pinC, HIGH);           // Motor A direction (forward)

  analogWrite(pinA, carSpeed);  // Motor A speed (set speed)

  digitalWrite(pinD, LOW);            // Motor B direction (backward)

  analogWrite(pinB, carSpeed);  // Motor B speed (set speed)

  digitalWrite(pinE, carState);       // Enable car (turn on motors if carState is 1)

}



// Stop motors when the car is off

void stopMotors() {

  digitalWrite(pinC, LOW);  // Motor A direction (stop)

  analogWrite(pinA, 0);     // Motor A speed (stop)

  digitalWrite(pinD, LOW);  // Motor B direction (stop)

  analogWrite(pinB, 0);     // Motor B speed (stop)

}

