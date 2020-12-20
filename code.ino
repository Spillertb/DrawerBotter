// Define pin connections & motor's steps per revolution
const int LEFT_DIR_PIN = 2;
const int LEFT_STEP_PIN = 3;

const int LEFT_HALF_STEP_PIN = 4;

const int RIGHT_DIR_PIN = 5;
const int RIGHT_STEP_PIN = 6;

const int RIGHT_HALF_STEP_PIN = 7;

const int STEPS_PER_REVOLUTION = 400;
const int STEPS_PER_MM = 10;

const int wait = 1700; //(speed)

float current_x;

float current_y;

float max_y;
float max_x;

float a_length; //(mm)=
float b_length; //(mm)

float initial_x; //(mm)


float soft_x_limit; //(mm)
float soft_y_limit; //(mm)



void setup()
{
  initial_x = 317.5;
  
  current_x = initial_x; //x pox (mm) // starting value (NOT inkscape home)
  current_y = 0; //y pos (mm)

  soft_x_limit = 304.5; //(mm)
  soft_y_limit = 304.5; //(mm)

//  a_length = 520.7; //mm
//  b_length = 673.1; //mm

  max_y = 412.75; //mm
  max_x = 901.7; //mm
  
  pinMode(RIGHT_STEP_PIN, OUTPUT); // set as output
  pinMode(LEFT_STEP_PIN, OUTPUT);// set as output
  
  digitalWrite(RIGHT_STEP_PIN, LOW); // instead of pull down resistor
  digitalWrite(LEFT_STEP_PIN, LOW);  // instead of pull down resistor 
  
  // Declare pins as Outputs
  pinMode(LEFT_DIR_PIN, OUTPUT);


  pinMode(RIGHT_DIR_PIN, OUTPUT);
  
  //set half stepping for left
  pinMode(LEFT_HALF_STEP_PIN, OUTPUT);
  digitalWrite(LEFT_HALF_STEP_PIN, HIGH);

  //set half stepping for right
  pinMode(RIGHT_HALF_STEP_PIN, OUTPUT);
  digitalWrite(RIGHT_HALF_STEP_PIN, HIGH);

  //Enterhere the coordinates
}
void loop() {

  //moveTo(200, 100);

}

void moveTo(float x, float y) {
  x+=initial_x;
/*
  x*=(float).5;
  y*=(float).5;

  x+= (float)150.0;
  y+= (float)150.0;

  Serial.print("x:");
  Serial.println(x);
  Serial.print("y:");
  Serial.println(y);
  */


  
  float a1 = sqrt(pow(current_x,2) + pow((max_y - current_y), 2));
  float a2 = sqrt(pow(x,2) + pow((max_y - y),2));
  /*
  Serial.print("a1: ");
  Serial.println(a1);
    Serial.print("a2: ");
  Serial.println(a2);
  */


  float b1 = sqrt(pow((max_x - current_x),2) + pow((max_y - current_y),2));
  float b2 = sqrt(pow((max_x - x),2) + pow((max_y - y),2));
  /*
  Serial.print("b1: ");
  Serial.println(b1);
    Serial.print("b2: ");
  Serial.println(b2);
*/

  float motor1_change = a1-a2; //mm 
  
  Serial.print("motor1_change: ");
  Serial.println(motor1_change);
  
  boolean motor1_direction = false;
  if (motor1_change < 0) { // if negative distance change, counter-clockwise
    motor1_change *= -1; // make valuep ositive
    motor1_direction = true; // motor1 counter-clockwise
  }


  float motor2_change =  b1-b2; //mm
  Serial.print("motor2_change: ");
  Serial.println(motor2_change);
  boolean motor2_direction = true;
  if (motor2_change < 0) {
    motor2_change *= -1;
    motor2_direction = false;
  }
  
  int motor1_steps = motor1_change * STEPS_PER_MM;
  int motor2_steps = motor2_change * STEPS_PER_MM;
  
  /*
  Serial.print("motor1_steps: ");
  Serial.println(motor1_steps);
  Serial.print("motor2_steps: ");
  Serial.println(motor2_steps);

  Serial.print("motor1_dir: ");
  Serial.println(motor1_direction);
  Serial.print("motor2_dir: ");
  Serial.println(motor2_direction);
  */

  if (motor1_steps > motor2_steps){
    float slope = (float)motor1_steps/(float)motor2_steps;
 //   Serial.print("slope: ");
  //  Serial.println(slope);
    int motor1_count = 0;
    int motor2_count = 0;

    for (int i = 0; i < motor1_steps; i++) {
      leftMotorStep(motor1_direction);
    //  Serial.print("motor1_step: ");
     // Serial.println(motor1_count);
      motor1_count++;
      if (motor2_count < (float)motor1_count/slope) {
        rightMotorStep(motor2_direction);
       // Serial.print("motor2_step: ");
       // Serial.println(motor2_count);
        motor2_count++;
      }
    }
  }

  
  if (motor2_steps > motor1_steps){
    float slope = (float)motor2_steps/(float)motor1_steps;
    //Serial.print("slope: ");
    //Serial.println(slope);
    int motor2_count = 0;
    int motor1_count = 0;

    for (int i = 0; i < motor2_steps; i++) {
      rightMotorStep(motor2_direction);
      //Serial.print("motor2_step: ");
      //Serial.println(motor2_count);
      motor2_count++;
      if (motor1_count < (float)motor2_count/slope) {
        leftMotorStep(motor1_direction);
        //Serial.print("motor1_step: ");
        //Serial.println(motor1_count);
        motor1_count++;
      }
    }
  }
  
  current_x = x;
  current_y = y;
    
}
  



//positive dir = clockwise
void leftMotorStep(boolean dir) {
  if (dir) {
    digitalWrite(LEFT_DIR_PIN, HIGH);
  } else {
    digitalWrite(LEFT_DIR_PIN, LOW);
  }
  
  digitalWrite(LEFT_STEP_PIN, HIGH);
     
  delayMicroseconds(wait);

  digitalWrite(LEFT_STEP_PIN, LOW);
  
  delayMicroseconds(wait);
}


void rightMotorStep(boolean dir) {
  if (dir) {
    digitalWrite(RIGHT_DIR_PIN, HIGH);
  } else {
    digitalWrite(RIGHT_DIR_PIN, LOW);
  }
  
  digitalWrite(RIGHT_STEP_PIN, HIGH);
     
  delayMicroseconds(wait);

  digitalWrite(RIGHT_STEP_PIN, LOW);
  
  delayMicroseconds(wait);
}
