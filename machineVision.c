#define BALANCING_COEFF1 15
#define BALANCING_COEFF2 25

unsigned int LeftFrontWheel_Port1 = 22U;
unsigned int LeftFrontWheel_Port2 = 23U;
unsigned int LeftRearWheel_Port1 = 24U;
unsigned int LeftRearWheel_Port2 = 25U;
unsigned int LeftFrontWheelSpeed_Port = 2U;
unsigned int LeftRearWheelSpeed_Port = 3U;

void setup()
{
  pinMode(LeftFrontWheel_Port1, OUTPUT);
  pinMode(LeftFrontWheel_Port2, OUTPUT);
  pinMode(LeftRearWheel_Port1, OUTPUT);
  pinMode(LeftRearWheel_Port2, OUTPUT);
  pinMode(LeftFrontWheelSpeed_Port, OUTPUT);
  pinMode(LeftRearWheelSpeed_Port, OUTPUT);

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

void loop()
{

  moveLeftFrontWheel(230,1);
  moveLeftRearWheel(230,1);
  delay (2000);
  
  moveLeftFrontWheel(0,1);
  moveLeftRearWheel(0,1);
  delay (2000);
  
  moveLeftFrontWheel(230,0);
  moveLeftRearWheel(230,0);
  delay (2000);
  
  moveLeftFrontWheel(0,0);
  moveLeftRearWheel(0,0);
  delay (2000);

}
