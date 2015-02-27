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
long pulse, inches, cm;

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
  pinMode(sonar, INPUT);
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

/*readSonar
 * Input: sonar name
 * Output: distance measure in inches
 * Description: reads the pulse from the sonar sensor 
 */
 long readSonar(const int sonarPin){
  //read the pulse from the sonar
  pulse = pulseIn(sonarPin, HIGH);
  //conversion factor 147uS per inch
  inches = pulse/147;
  delay(500);
  return inches;
 }
   
 /*setReaction
  * Input: reading number, motor1 name, motor2 name
  * Ouput: Determines the reaction based on a given sonar reading, number of output vibration motors and the names of motor1 and motor2.
  * i.e. farther objects -> slow pulse; closer objects -> fast pulse.
  * Note: number of vibration motors to output to (1 = 1 vib motor, 2 = 2 vib motors)
  */
 void setReaction(long reading, const int motor1, const int motor2){ 
  char numOutput = 0;
  
  if(numOutput == 1){
    //conditionals: output the speed of the vib sensors based on the sonar readings
    if(reading <= minReading){
      setDelay = 250;
      singleVibration(motor1, setDelay);
      Serial.print(inches);
      Serial.print(" inches ");
      Serial.print(setDelay);
      Serial.println(" msec");
    }
    
    if(reading > minReading && inches <= middleReading){
      setDelay = 1000;
      singleVibration(motor1, setDelay);
      Serial.print(inches);
      Serial.print(" inches ");
      Serial.print(setDelay);
      Serial.println(" msec");
    }
    
    if(reading > middleReading && inches <= maxReading){
      setDelay = 2500;
      singleVibration(motor1, setDelay);
      Serial.print(inches);
      Serial.print(" inches ");
      Serial.print(setDelay);
      Serial.println(" msec");
    }}
  if(numOutput == 2){
    //conditionals: output the speed of the vib sensors based on the sonar readings
    if(reading <= minReading){
      setDelay = 250;
      dualVibration(motor1, motor2, setDelay);
      Serial.print(inches);
      Serial.print(" inches ");
      Serial.print(setDelay);
      Serial.println(" msec");
    }
    
    if(reading > minReading && inches <= middleReading){
      setDelay = 1000;
      dualVibration(motor1, motor2, setDelay);
      Serial.print(inches);
      Serial.print(" inches ");
      Serial.print(setDelay);
      Serial.println(" msec");
    }
    
    if(reading > middleReading && inches <= maxReading){
      setDelay = 2500;
      dualVibration(motor1, motor2, setDelay);
      Serial.print(inches);
      Serial.print(" inches ");
      Serial.print(setDelay);
      Serial.println(" msec");
    }}
  
  //anything greater than maxReading should do nothing. 
}


void objectSide(

 /*main
 * Input: sonar1 name, sonar2 name
 * Output: void
 * Description: reads the pulse from both of the sonar sensors and outputs vibration to vib1 and vib2 based on the distance from a detected object. Acts as "main method"
 */
void main(const int sonar1, const int sonar2){
  long reading1, reading2;
  
  reading1=readSonar(sonar1); //left sonar
  reading2=readSonar(sonar2); //right sonar
  
  setReaction(long reading, char numOutput, const int motor1, const int motor2)

//Continuous loop function. Required for Arduino functionality.
void loop() {
  //read the sonar sensor (and react accordingly)
  readSonar(sonar);  
}
