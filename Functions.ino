//To sense object nad further activate conveyor
void UltrasonicSensor1(){
 pinMode(Pin9, OUTPUT); // This pin will trigger the ultrasonic signal
 pinMode(Pin10, INPUT); // This pin will receive the ultrasonic dignal
 long duration; // A small delay should be given when using ultrasonic sensor
 digitalWrite(Pin9, HIGH); // To send ultrasonic signals
 //We all know delays aren't the best option, but because this function runs alone
 // in step 0, isn't interrupting any other function so we can simplify the code
 // by using delay withot worrying about affecting the rest of the script.
 // Also we need microseconds to use the ultrasonic sensor properly
 delayMicroseconds(1000); 
 digitalWrite(Pin9, LOW); // The trigger pin will be off after the set delay
 duration = pulseIn(Pin10, HIGH); // The receiving pin will be on to sense the signal
 ObjectDistance = (duration/2)/29.1; 
 // Conveyor will remain off until an object is placed into it, until an object
 //is place into the designated range, equivalent to the conveyor width (5cm).
 if (ObjectDistance >= 5){
  Serial.println("No object detected"); // Conveyor won't start
  }else{
  Serial.print("Object detected in ");
  Serial.print(ObjectDistance);
  Serial.println("cm. Activating conveyor"); 
  ConveyorProcess = 1; // Moving to next case, which activates the conveyor  
 }
}

//To rotate conveyor motor in a specified provided speed in any direction from 0 to 150
void ConveyorOn() {
  pinMode(Pin4, OUTPUT);
  digitalWrite(Pin4, HIGH);
  ConveyorProcess = 2; // Moving to next case, which activates stops the conveyor 
}

//To sense object and further stop conveyor
void UltrasonicSensor2(){
 pinMode(Pin11, OUTPUT); // This pin will trigger the ultrasonic signal
 pinMode(Pin12, INPUT); // This pin will receive the ultrasonic dignal
 long duration; // A small delay should be given when using ultrasonic sensor
 digitalWrite(Pin11, HIGH); // To send ultrasonic signals
 //We all know delays aren't the best option, but because this function runs only
 // with the conveyor on, is not interrupting any other function
 delayMicroseconds(1000); 
 digitalWrite(Pin11, LOW); // The trigger pin will be off after the set delay
 duration = pulseIn(Pin12, HIGH); // The receiving pin will be on to sense the signal
 ObjectDistance = (duration/2)/29.1; 
 // Conveyor will remain off until an object is placed into it, until an object
 //is place into the designated range, equivalent to the conveyor width (5cm).
 if (ObjectDistance >= 5){
  Serial.println("No object detected"); // Conveyor won't stop
  }else{
  Serial.print("Object detected in ");
  Serial.print(ObjectDistance);
  Serial.println("cm. Stopping conveyor"); 
  ConveyorProcess = 2; // Moving stops the conveyor and activates the grip
 }
}

//To stop conveyor motor
void ConveyorStop() {
  digitalWrite(Pin4, LOW);
}

//Function to move the end effector horizontally
void HorizontalEndEffectorMotor(){
 //Pimoroni motor uses 50:1 gearbox. This means the encoder has 50 interrupts per revolution
 //However, for the shaft to have a full revolution, the encoder must have 600 interrupts,
 // which is 12 full encoder revolutions
 float EncoderFullRevolution = 600;
 // To convert from encoder value to radians and to linear displacement in mm
 HorizontalEndEffectorDisplacement = PulleyRadius*
 (2*3.1415*CountInterrupts/ EncoderFullRevolution)/10;
 if (HorizontalEndEffectorDisplacement < ObjectDistance){ 
  analogWrite(Pin6, 50); // Moving grip horizontally
  digitalWrite(Pin7, LOW);
 }else{ 
  analogWrite(Pin6, LOW); // Stoping grip movement
  digitalWrite(Pin7, LOW);
  ConveyorProcess = 3; //To go through the next step in the switch case
  }
}

//Function to move the end effector approximately 50mm downwards
 void VerticalEndEffectorMotorDownwards(){
  analogWrite(Pin5, 50); // Moving grip downwards
  digitalWrite(Pin8, LOW);
  ConveyorProcess = 4; //To go through the next step in the switch case
}

//Function to activate vacuum
 void Vacuum(){
 digitalWrite(Pin13, HIGH);
}

// To delay end effector retracting for one second (1000 ms)
 void GoodDelay1000(){
  static unsigned long previousMillis = 0;  
  unsigned long currentMillis = millis();
  int interval = 1000;
  if (currentMillis - previousMillis >= interval){
   previousMillis = currentMillis;
   ConveyorProcess = 5; //To go through the next step in the switch case
  }
}

//Function to retract the end effector upwards
 void VerticalEndEffectorMotorUpwards(){
  analogWrite(Pin5, LOW); // Moving grip upwards
  digitalWrite(Pin8, HIGH);
  ConveyorProcess = 4; //To go through the next step in the switch case
}

// To delay end effector retracting for 0.2 second2 (200 ms)
 void GoodDelay200(){
  static unsigned long previousMillis = 0;  
  unsigned long currentMillis = millis();
  int interval = 200;
  if (currentMillis - previousMillis >= interval){
   previousMillis = currentMillis;
   ConveyorProcess = 6; //To go through the next step in the switch case
  }
}

//Function to move the end effector horizontally
void HorizontalEndEffectorMotorRetract(){
 if (CountInterrupts > 0){ 
  analogWrite(Pin6, LOW); // Retracting end effector 
  digitalWrite(Pin7, HIGH);
 }else{ 
  analogWrite(Pin6, LOW); // Stoping grip movement
  digitalWrite(Pin7, LOW);
  ConveyorProcess = 1; // Restart process
  }
}


//This function to be called only by the attachInterrupt function
void ChannellMotor1() {
  if (digitalRead(EncA2) == digitalRead(EncA3)) {
    CountInterrupts++;
  } else {
    CountInterrupts--;
  }
}

//This function to be called only by the attachInterrupt function
void Channel2Motor1() {
  if (digitalRead(EncA2) == digitalRead(EncA3)) {
    CountInterrupts--;
  } else {
    CountInterrupts++;
  }
}

/* Backup functions
void ConveyorMoving(){

//Pimoroni motor uses 50:1 gearbox. This means the encoder has 50 interrupts per revolution
//However, for the shaft to have a full revolution, the encoder must have 600 interrupts,
// which is 12 full encoder revolutions
float EncoderFullRevolution = 600;

  ConveyorDisplacement = ConveyorRadius*(2*3.1415*Count/ EncoderFullRevolution);

  if (ConveyorDisplacement >= 50) {
   ConveyorProcess = 1; //To go through the next step in the switch case
  }
}
*/
