#define BALANCING_COEFF1 15
#define BALANCING_COEFF2 25

unsigned int LeftFrontWheel_Port1 = 22U;
unsigned int LeftFrontWheel_Port2 = 23U;
unsigned int LeftRearWheel_Port1 = 24U;
unsigned int LeftRearWheel_Port2 = 25U;
unsigned int RightFrontWheel_Port1 = 26U; 
unsigned int RightFrontWheel_Port2 = 27U;
unsigned int RightRearWheel_Port1 = 28U;
unsigned int RightRearWheel_Port2 = 29U;
unsigned int LeftFrontWheelSpeed_Port = 2U;
unsigned int LeftRearWheelSpeed_Port = 3U;
unsigned int RightFrontWheelSpeed_Port = 4U;
unsigned int RightRearWheelSpeed_Port = 5U;

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

  Serial.begin(9600);
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
  delay(30);
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
  delay(30);
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
  delay(30);
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
  delay(30);
}

void loop()
{
  moveLeftFrontWheel(230,1);
  moveLeftRearWheel(230,1);
  moveRightFrontWheel(230,1);
  moveRightRearWheel(230,1);
  delay (2000);
  
  moveLeftFrontWheel(0,1);
  moveLeftRearWheel(0,1);
  moveRightFrontWheel(0,1);
  moveRightRearWheel(0,1);
  delay (2000);
  
  moveLeftFrontWheel(230,0);
  moveLeftRearWheel(230,0);
  moveRightFrontWheel(230,0);
  moveRightRearWheel(230,0);
  delay (2000);
  
  moveLeftFrontWheel(0,0);
  moveLeftRearWheel(0,0);
  moveRightFrontWheel(0,0);
  moveRightRearWheel(0,0);
  delay (2000);
}
