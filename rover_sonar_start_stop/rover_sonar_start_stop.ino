// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 4;
int in3 = 6;
int in4 = 5;

const int distance_threshold = 10; // needs change

// Sonar connections
const int trigPin = 2;
const int echoPin = 3;

// Variable for storing distance
long distance;

enum States {
  idle,
  moving,
  turn_right,
  turn_left,
  stop
};

States current_state;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set sonar pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  current_state = moving;

  Serial.begin(9600);  // Initialize Serial Monitor for debugging
}

void loop() {
  // Read distance from sonar
  // distance = getDistance();

  // If distance is greater than a threshold, run motors
  // if (distance > 10) {  // Adjust threshold distance as needed
  //   directionControl();
  //   Serial.print("motors running \n");
  // } else {
  //   stopMotors();  // Stop motors if an object is detected within threshold distance
  //   Serial.print("motors stoped \n");
  // }

  change_state();
  execute_state();


  //directionControl();
  delay(50);  // Small delay to avoid rapid switching
}

void change_state() {
  distance = getDistance();
Serial.print("Distance = ");
Serial.println(distance);
  if (distance > distance_threshold) {
    Serial.println("current_state = moving");
    current_state = moving;
  } else {
    Serial.println("current_state = turn_right");
    current_state = turn_right;
  }

  // execute_state();
}

void execute_state() {
  switch (current_state) {
    case moving:
      directionControl();
      break;

    case turn_right:
      motor_turn_right();
      break;

    default:
      stopMotors();
  }
}

long getDistance() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigger pin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echo pin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  long distance = duration * 0.034 / 2;

  return distance;
}

void directionControl() {
  // Set motors to maximum speed
  Serial.print("Setting motors to max speed");
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B in forward direction
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(200); // needs change

  // Serial.print("Setting motors to max speed");
  // // Stop motors briefly
  // stopMotors();
}

void motor_turn_right() {
  // Set motors to maximum speed

Serial.println("turn right");
  // Serial.print("Setting motors to max speed");
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A clockwise
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);

  delay(200); // needs change
}

void stopMotors() {
  // Turn off all motor pins
  Serial.println("Stop moving");
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(500);
}