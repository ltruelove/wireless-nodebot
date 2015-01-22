/* Reads input from a DSM2 reciever to drive two servos
 * ------------------ 
 */
 
 #include <Servo.h>
 #include <math.h>
Servo leftWheel;
Servo rightWheel;

//int potPin = 2;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 90;       // variable to store the value coming from the sensor
int newVal = 0;
int turnVal = 0;
int inverseVal = 0;
int mid = 90;
int pulsePin = 8;
int turnPin = 7;

int servoMax = 180;
int throttleDifference = 805;
int throttleMin = 1100;

double leftAlt = 0;
double rightAlt = 0;
double leftVal = 0;
double rightVal = 0;
int origLeftAlt = 0;
int rightThreshold = 1465;
int rightMin = 1110;
int rightDiff = rightThreshold - rightMin;
float rightAltPercentage = 0;

int leftThreshold = 1520;
int leftMax = 1906;
int leftDiff = leftMax - leftThreshold;
float leftAltPercentage = 0;

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  leftWheel.attach(9);  
  rightWheel.attach(10);
  Serial.begin(9600);
  pinMode(pulsePin, INPUT);
  pinMode(turnPin, INPUT);
}

void loop() {
  //reset the alts
  rightAlt = 0;
  rightAltPercentage = 0;
  leftAlt = 0;
  
  // get the values from the receiver
  val = pulseIn(pulsePin, HIGH);
  turnVal = pulseIn(turnPin, HIGH);
  
  newVal = val - throttleMin;
  val = map(newVal, 0, throttleDifference, mid, servoMax);
  
  if (val <= 100 ){
    val = mid;
  }
  
  inverseVal = val;
  if(val < mid){
    inverseVal = (mid - val) + mid;
  }else if(val > 90) {
    inverseVal = mid - (val -mid);
  }
  rightVal = val;
  leftVal = inverseVal;
  
  if(turnVal < rightThreshold){ //turning right
    rightAlt = rightDiff - (turnVal - rightMin);
    if(rightAlt < 0){
      rightAlt = 1;
    }
    rightAltPercentage = (rightAlt / rightDiff);
    rightAlt = floor((rightVal - mid) * rightAltPercentage);
  }else if(turnVal > leftThreshold){ //turning left
    leftAlt = leftDiff - (leftMax - turnVal);
    if(leftAlt < 1){
      leftAlt = 1;
    }
    
    leftAltPercentage = (leftAlt / leftDiff);
    leftAlt = floor((mid -leftVal) * leftAltPercentage);
  }
  
  if(val != 90){
    if(rightAlt != 0 && rightAlt > 0){
      rightVal = rightVal - rightAlt;
    }
    if(leftAlt != 0 && leftAlt > 0){
      leftVal = leftVal + leftAlt;
    } 
  }
  
  rightWheel.write(rightVal);
  leftWheel.write(leftVal);
  
  
  /*
  digitalWrite(ledPin, HIGH);  // turn the ledPin on
  delay(val);                  // stop the program for some time
  digitalWrite(ledPin, LOW);   // turn the ledPin off
  delay(val);                  // stop the program for some time
  Serial.println(val);
  */
  
    /*
    Serial.println(turnVal);
    Serial.println(val);
    Serial.println(rightVal);
    Serial.println(rightAlt);
    Serial.println(rightAltPercentage);
    Serial.println("");
    delay(500);
    */
  
    /*
    rightAlt = rightVal / rightAltPercentage;
    rightAlt = 30 - rightAlt;
    
    if(rightVal > 150){
      rightAlt = rightAlt + 50;
    }else if(rightVal < 120){
      rightAlt = rightAlt - 20;
    }
    
    if (rightAlt < 0){
      rightAlt = 0;
    }
    */
    /*
    Serial.println(inverseVal);
    Serial.println(leftVal);
    Serial.println(leftAlt);
    Serial.println(leftAltPercentage);
    Serial.println("");
    delay(500);
    */
    
    /*
    origLeftAlt = leftAlt;
    leftAlt = map(leftAlt, 0, 409,0,30);
    
    leftAlt = 30 - leftAlt;
    
    if(leftVal < 30){
      leftAlt = leftAlt + 50;
    }else if(leftVal > 50){
      leftAlt = leftAlt - 20;
    }
    */
}
