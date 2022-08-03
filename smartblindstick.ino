// C++ code
#define button1 2 // this button use for only Alarm mode
#define button2 3 // this button use for Alarm & Vibrator mode
#define button3 4 // this button use for only Vibrator mode
#define buzzer 5 // this pin use for Alarm
#define motor 9 // this pin use for Vibrator Motor
#define echopin 7 // echo pin
#define trigpin 8 // Trigger pin
int Alarm=1, Vibrator=1;
int cm; // Duration used to calculate distance
void setup(){ // put your setup code here, to run once
Serial.begin(9600);// initialize serial communication at 9600 bits per second:
pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(button3, INPUT_PULLUP);
pinMode(buzzer, OUTPUT); //declare buzzer as output
pinMode(motor, OUTPUT); //declare vibrator Motor as output
pinMode(trigpin, OUTPUT); // declare ultrasonic sensor Echo pin as input
pinMode(echopin, INPUT); // declare ultrasonic sensor Trigger pin as Output
delay(100);
}
void loop(){

long duration;
if(digitalRead(button1)==0) Alarm=1, Vibrator=0; //only Alarm mode
if(digitalRead(button2)==0) Alarm=1, Vibrator=1; //Alarm & Vibrator mode
if(digitalRead(button3)==0) Alarm=0, Vibrator=1; //only Vibrator mode
// Write a pulse to the HC-SR04 Trigger Pin
digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin, LOW);

// Measure the response from the HC-SR04 Echo Pin
duration = pulseIn (echopin, HIGH);
 // Determine distance from duration
 // Use 343 metres per second as speed of sound
cm = microsecondsToCentimeters(duration);
Serial.print("cm:");Serial.println(cm);
if(cm<=100 && cm>0){
int d = map(cm, 1, 300, 10, 1000);
if(Alarm==1)digitalWrite(buzzer, HIGH); // Turn on Buzzer
if(Vibrator==1)digitalWrite(motor, HIGH); // Turn on Vibrator
delay(50);
digitalWrite(buzzer, LOW); // Turn off Buzzer
digitalWrite(motor, LOW); // Turn off Vibrator
delay(d);
}
}
long microsecondsToCentimeters(long microseconds) {
return microseconds / 29 / 2;
}
