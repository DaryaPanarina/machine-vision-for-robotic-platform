#define BALANCING_COEFF1 15
#define BALANCING_COEFF2 25

#define LeftFrontWheel_Port1 22U
#define LeftFrontWheel_Port2 23U
#define LeftRearWheel_Port1 24U
#define LeftRearWheel_Port2 25U
#define RightFrontWheel_Port1 26U
#define RightFrontWheel_Port2 27U
#define RightRearWheel_Port1 28U
#define RightRearWheel_Port2 29U
#define LeftFrontWheelSpeed_Port 2U
#define LeftRearWheelSpeed_Port 3U
#define RightFrontWheelSpeed_Port 4U
#define RightRearWheelSpeed_Port 5U

void setup()
{
  pinMode(LeftFrontWheel_Port1, OUTPUT);
  pinMode(LeftFrontWheel_Port2, OUTPUT);
  pinMode(LeftRearWheel_Port1, OUTPUT);
  pinMode(LeftRearWheel_Port2, OUTPUT);
  pinMode(RightFrontWheel_Port1, OUTPUT);
  pinMode(RightFrontWheel_Port2, OUTPUT);
  pinMode(RightRearWheel_Port1, OUTPUT);
  pinMode(RightRearWheel_Port2, OUTPUT);
  pinMode(LeftFrontWheelSpeed_Port, OUTPUT);
  pinMode(LeftRearWheelSpeed_Port, OUTPUT);
  pinMode(RightFrontWheelSpeed_Port, OUTPUT);
  pinMode(RightRearWheelSpeed_Port, OUTPUT);

  Serial.begin(9600U);
}

void moveLeftFrontWheel(const unsigned int newSpeed, const unsigned int newDirection)
{
  if (0U == newDirection) 
  {
    digitalWrite(LeftFrontWheel_Port1, HIGH);
    digitalWrite(LeftFrontWheel_Port2, LOW); 
    analogWrite(LeftFrontWheelSpeed_Port, newSpeed + BALANCING_COEFF1);   
  }
  else
  {
    digitalWrite(LeftFrontWheel_Port1, LOW);
    digitalWrite(LeftFrontWheel_Port2, HIGH); 
    analogWrite(LeftFrontWheelSpeed_Port, newSpeed);   
  }
  delay(30U);
}

void moveLeftRearWheel(const unsigned int newSpeed, const unsigned int newDirection)
{
  if (0U == newDirection)
  {
    digitalWrite(LeftRearWheel_Port1, HIGH);
    digitalWrite(LeftRearWheel_Port2, LOW); 
    analogWrite(LeftRearWheelSpeed_Port, newSpeed + BALANCING_COEFF1);   
  }
  else
  {
    digitalWrite(LeftRearWheel_Port1, LOW);
    digitalWrite(LeftRearWheel_Port2, HIGH); 
    analogWrite(LeftRearWheelSpeed_Port, newSpeed + BALANCING_COEFF2);   
  }
  delay(30U);
}

void moveRightFrontWheel(const unsigned int newSpeed, const unsigned int newDirection)
{
  if (0U == newDirection) 
  {
    digitalWrite (RightFrontWheel_Port1, HIGH);
    digitalWrite (RightFrontWheel_Port2, LOW); 
    analogWrite(RightFrontWheelSpeed_Port, newSpeed + BALANCING_COEFF2);   
  }
  else
  {
    digitalWrite (RightFrontWheel_Port1, LOW);
    digitalWrite (RightFrontWheel_Port2, HIGH); 
    analogWrite(RightFrontWheelSpeed_Port, newSpeed + BALANCING_COEFF1);   
  }
  delay(30U);
}

void moveRightRearWheel(const unsigned int newSpeed, const unsigned int newDirection)
{
  if (0U == newDirection) 
  {
    digitalWrite (RightRearWheel_Port1, HIGH);
    digitalWrite (RightRearWheel_Port2, LOW); 
    analogWrite(RightRearWheelSpeed_Port, newSpeed);
  }
  else
  {
    digitalWrite (RightRearWheel_Port1, LOW);
    digitalWrite (RightRearWheel_Port2, HIGH); 
    analogWrite(RightRearWheelSpeed_Port, newSpeed + BALANCING_COEFF1);   
  }
  delay(30U);
}

void loop()
{
  // For example
  moveLeftFrontWheel(230U, 1U);
  moveLeftRearWheel(230U, 1U);
  moveRightFrontWheel(230U, 1U);
  moveRightRearWheel(230U, 1U);
  delay (2000U);
  
  moveLeftFrontWheel(0U, 1U);
  moveLeftRearWheel(0U, 1U);
  moveRightFrontWheel(0U, 1U);
  moveRightRearWheel(0U, 1U);
  delay (2000U);
  
  moveLeftFrontWheel(230U, 0U);
  moveLeftRearWheel(230U, 0U);
  moveRightFrontWheel(230U, 0U);
  moveRightRearWheel(230U, 0U);
  delay (2000U);
  
  moveLeftFrontWheel(0U, 0U);
  moveLeftRearWheel(0U, 0U);
  moveRightFrontWheel(0U, 0U);
  moveRightRearWheel(0U, 0U);
  delay (2000U);

}
