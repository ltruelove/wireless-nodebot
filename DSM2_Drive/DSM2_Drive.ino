/* Reads input from a DSM2 reciever to drive two servos
 * ------------------ 
 */
 
 #include <Servo.h>
 #include <math.h>

Servo leftWheel;
Servo rightWheel;

int val = 90;
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
  leftWheel.attach(9);  
  rightWheel.attach(10);
  //Serial.begin(9600);
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
  
}
