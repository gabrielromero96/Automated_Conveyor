int EncA2 = 2; //These are the pins for the encoder in the horizontal motor for end deffector
int EncA3 = 3; //These are the pins for the encoder in the horizontal motor for end deffector

int Pin4 = 4; //This is the pin to rotate the conveyor motor 

int Pin9 = 9; // Trigger signal for first ultrasonic sensor
int Pin10 = 10; //Echo signal for first ultrasonic sensor

int Pin11 = 11; // Trigger signal for second ultrasonic sensor
int Pin12 = 12; // Echo signal for second ultrasonic sensor

int Pin13 = 13; //Pin to turn on vacuum motor on end effector

int Pin6 = 6; // These are the pins to rotate the horizontal motor for end deffector
int Pin7 = 7; // These are the pins to rotate the horizontal motor for end deffector

int Pin5 = 5; // These are the pins to rotate the vertical motor for end deffector
int Pin8 = 8; // These are the pins to rotate the vertical motor for end deffector

float ObjectDistance; // To detect position of object in cm

// End effector variables
float PulleyRadius = 5; //Pulley radius in mm to calculate end effector linear displacement
float HorizontalEndEffectorDisplacement; //Conveyor linear displacement in cm

volatile float CountInterrupts; //To count the encoder interrupts

int PreviousCount = 0;

int ConveyorProcess = 0; //The variable that will go through the switch case

void setup() {

attachInterrupt(digitalPinToInterrupt(EncA2), ChannellMotor1, CHANGE); //Interrupt function
attachInterrupt(digitalPinToInterrupt(EncA3), Channel2Motor1, CHANGE); //Interrupt function

Serial.begin(9600);
}

void loop() {

switch (ConveyorProcess){
  case 0: // Everything is stopped until an object is placed in a conveyor
  UltrasonicSensor1();
  case 1: // Activate conveyor and sense object under the end effector
  ConveyorOn(); 
  UltrasonicSensor2();  
  case 2: // To stop conveyor and activate horizontal end effector movement
  ConveyorStop(); 
  HorizontalEndEffectorMotor();
  case 3: // To activate vertical end effector movement
  VerticalEndEffectorMotorDownwards();
  case 4: // To activate vacuum and retract vertical end effector
  Vacuum();
  GoodDelay1000();
  case 5:
  Vacuum();
  VerticalEndEffectorMotorUpwards();
  GoodDelay200();
  case 6:
  Vacuum();
  HorizontalEndEffectorMotorRetract();
}
}
