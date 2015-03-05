/* SonarWatch: Wearable Technology for the Visually Impaired
   Falcon Technology
   ME 2300 - Engineering Design
   Written By Liz Miller, eamiller@wpi.edu
   --------
V1.4: SonarWatch 1/2 sensor functionality added | 3/4/2015
  * Supports demonstration of left sensor/vib motor
  
V1.3: Fine tuning and adjustments made to cutoff limits and vibration delays | 2/26/2015    
  * Set values for minReading, maxReading, middleReading
  
V1.2: Added compatibility with two sonar sensors | 2/25/2015
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
//const int sonar2 = 10;
const int vib1 = 2;
//const int vib2 = 3;

//variables needed to store values
long inches, pulse;

//set ranges for reactions
int minReading = 6;
int middleReading = 12;
int maxReading = 18;
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
  //pinMode(sonar2, INPUT);
  pinMode(vib1, OUTPUT);
  //pinMode(vib2, OUTPUT);
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

/*printDist
 *Input: none
 *Output: none
 *Description: used to print data to serial monitor
 */ 
 void printDist(){
    Serial.print(inches);
    Serial.print(" inches ");
    Serial.print(setDelay);
    Serial.println(" msec");
 }
 
/*readSonar
 * Input: sonar name
 * Output: none
 * Description: reads the pulse from the sonar sensor 
 */
 void readSonar(const int sonarPin){
  //read the pulse from the sonar
  pulse = pulseIn(sonarPin, HIGH);
  //conversion factor 147uS per inch
  inches = pulse/147;
  delay(500);
 
  if(inches <= minReading){
    setDelay = 250;
    singleVibration(vib1, setDelay);
    printDist();
  }
  if(inches > minReading && inches <= middleReading){
     setDelay = 750;
     singleVibration(vib1, setDelay);
     printDist();
  }
  if(inches > middleReading && inches <= maxReading){
     setDelay = 1000;
     singleVibration(vib1, setDelay);
     printDist();
  }
  //if inches is > maxReading, do nothing
 }
 
 //Continuous loop function. Required for Arduino functionality.
void loop() {
  //read the sonar sensor (and react accordingly)
  readSonar(sonar1);  
}
