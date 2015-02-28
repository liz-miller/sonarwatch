/* SonarWatch: Wearable Technology for the Visually Impaired
   Falcon Technology
   ME 2300 - Engineering Design
   Written By Liz Miller, eamiller@wpi.edu
   --------
   
V1.3: Fine tuning and adjustments made to cutoff limits and vibration delays |    
  
V1.2: Added compatibility with two sonar sensors | 
  * Introduced sonar1 and sonar2
  * Left/right side object detection with left/right side vib motor output

V1.1: Increased sonar accuracy in inches | 2/23/2015
  * Simulaneous output pulses to Vib1 and Vib2
  * Pulses are based on distance readings: refer to readSonar()

V1.0: First-release | 2/22/2015
  * Initial Maxbotix PWM LV-EZ4 Code (Open-Source) Written by Bruce Allen, 7/23/2009 
  * Provides basic framework support for Vib1 and Vib2 and Sonar1
  * Pinout Configuration based on Lilypad Arduino USB board 
*/ 

//Digital pin 7 for reading in the pulse width from the MaxSonar device.
//This variable is a constant because the pin will not change throughout execution of this code.
const int sonar1 = 9; 
const int sonar2 = 10;
const int vib1 = 2;
const int vib2 = 3;

//variables needed to store values
long inches, pulse1, pulse2, left, right;

//set ranges for reactions
int minReading = 9;
int middleReading = 12;
int maxReading = 15;
int setDelay = 0;

 /*setup
 * Input: none
 * Output: void
 * Description: configures pins to initial conditions (input/output or high/low)
 */
void setup() {

  //This opens up a serial connection to shoot the results back to the PC console
  Serial.begin(9600);
  pinMode(sonar1, INPUT);
  pinMode(sonar2, INPUT);
  pinMode(vib1, OUTPUT);
  pinMode(vib2, OUTPUT);
}

/*singleVibration
 * Input: motor name, delay amount(ms)
 * Output: void
 * Description: turns on and off the given vibration motor for a given duration
 */
void singleVibration(const int motor, int setDelay){
  digitalWrite(motor, HIGH);
  delay(setDelay);
  digitalWrite(motor, LOW);
  delay(setDelay);
}

/*dualVibration
 * Input: motor1 name, motor2 name, delay amount(ms)
 * Output: void
 * Description: turns on and off the given vibration motors simultaneously for a given duration
 */
void dualVibration(const int motor1, const int motor2, int setDelay){
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  delay(setDelay);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  delay(setDelay);
}

/*runDevice
 * Input: sonar1 name, sonar2 name
 * Output: void
 * Description: reads the pulse from both of the sonar sensors and determines which side the object is on. Output to left/right/both sides depending on sensor reading.
 */
 void runDevice(const int sonarPin1, const int sonarPin2){
  int setVib=500;
  //read the pulse from the sonar
  pulse1 = pulseIn(sonarPin1, HIGH);//left
  pulse2 = pulseIn(sonarPin2, HIGH);//right
  //conversion factor 147uS per inch
  left = pulse1/147;
  right = pulse2/147;
  delay(500);  
  
  if(left>right){//obj is closer to left
    singleVibration(vib1,setVib);
    Serial.print(left);
    Serial.print(" ");
    Serial.print(right);
    Serial.print(" inches ");
    Serial.print(setVib);
    Serial.println(" msec");
  }
  if(left<right){//obj is closer to right
    singleVibration(vib2,setVib);
    Serial.print(left);
    Serial.print(" ");
    Serial.print(right);
    Serial.print(" inches ");
    Serial.print(setVib);
    Serial.println(" msec");
  }
  if(left==right || left==right+1 || right==left+1){//obj is straight ahead
    dualVibration(vib1,vib2,setVib);
    Serial.print(left);
    Serial.print(" ");
    Serial.print(right);
    Serial.print(" inches ");
    Serial.print(setVib);
    Serial.println(" msec");
  }
}

//Continuous loop function. Required for Arduino functionality.
void loop() {
  //read the sonar sensor (and react accordingly)
  runDevice(sonar1,sonar2);
}
