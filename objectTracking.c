#include <Servo.h> 

#define MIN_ANGLE 30U
#define MAX_ANGLE 150U

#define Up_Port 32U
#define Right_Port 33U
#define Down_Port 34U
#define Left_Port 35U
#define Light_Port 38U
#define HorizontalServo_Port 6U
#define VerticalServo_Port 7U

Servo horizontalServo;
Servo verticalServo;

unsigned int angle = 2U;
unsigned int x = 90U;
unsigned int y = 90U;
unsigned int isFirstIteration = 1U;

void setup()
{
  pinMode(Up_Port,INPUT);
  pinMode(Right_Port,INPUT);
  pinMode(Down_Port,INPUT);
  pinMode(Left_Port,INPUT);
  pinMode(Light_Port,OUTPUT);

  horizontalServo.attach(HorizontalServo_Port);
  verticalServo.attach(VerticalServo_Port);

  Serial.begin(9600U);
}

void loop()
{
  if (1U == isFirstIteration)
  {
    horizontalServo.write(x);
    verticalServo.write(y);
    delay(500U);
    isFirstIteration = 0U; 
  }

  Serial.print(digitalRead(Up_Port));
  Serial.print(digitalRead(Right_Port));
  Serial.print(digitalRead(Down_Port));
  Serial.print(digitalRead(Left_Port));
  
  digitalWrite(Light_Port, HIGH);
  
  if ((digitalRead(Up_Port) == 1U) && (digitalRead(Right_Port) == 0U) && (digitalRead(Down_Port) == 0U) && (digitalRead(Left_Port) == 0U) && (y < MAX_ANGLE))
  {
    y += angle;
    verticalServo.write(y); 
    delay(40U);
  }

  if ((digitalRead(Up_Port) == 0U) && (digitalRead(Right_Port) == 0U) && (digitalRead(Down_Port) == 1U) && (digitalRead(Left_Port) == 0U) && (y > MIN_ANGLE))
  {
    y -= angle ;
    verticalServo.write(y);
    delay(40U);
  }

  if ((digitalRead(Up_Port) == 0U) && (digitalRead(Right_Port) == 0U) && (digitalRead(Down_Port) == 0U) && (digitalRead(Left_Port) == 1U) && (x < MAX_ANGLE))
  {
    x += angle;
    horizontalServo.write(x); 
    delay(40U);
  }
  
  if ((digitalRead(Up_Port) == 0U) && (digitalRead(Right_Port) == 1U) && (digitalRead(Down_Port) == 0U) && (digitalRead(Left_Port) == 0U) && (x > MIN_ANGLE))
  {
    x -= angle;
    horizontalServo.write(x);
    delay(40U);
  }
}
