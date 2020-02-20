#include <TimerOne.h>
#include <IRremote.h>
#include <Servo.h>

#define Up_Port 32U
#define Right_Port 33U
#define Down_Port 34U
#define Left_Port 35U
#define Light_Port 38U

#define HorizontalServo_Port 6U
#define VerticalServo_Port 7U
#define foldingRightSide_Port 9U
#define foldingLeftSide_Port 10U
#define ServoPowerSource_Port 41U

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

#define NoProgramLED_Port 37U
#define Program1LED_Port 39U
#define Program2LED_Port 40U

#define MIN_ANGLE 30U
#define MAX_ANGLE 150U

#define BALANCING_COEFF1 15U
#define BALANCING_COEFF2 25U

#define SERVO_MIN_IMP 920U
#define SERVO_MAX_IMP 2080U

#define MAX_ERROR 5U

#define BUTTON_MAIN_MENU 16743045UL
#define BUTTON_PROGRAM1 16724175UL
#define BUTTON_PROGRAM2 16718055UL
#define BUTTON_4 16716015UL
#define BUTTON_5 16726215UL
#define BUTTON_6 16734885UL
#define BUTTON_7 16728765UL
#define BUTTON_8 16730805UL
#define BUTTON_9 16732845UL

unsigned long fromRemote;

Servo horizontalServo, verticalServo;
Servo foldingRightSide, foldingLeftSide;

IRrecv irrecv(30U);
decode_results whichButton;

void setup()
{
  //For output variables during debugging
  //Serial.begin(9600U);

  //Wheels initialization
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

  //LEDs initialization
  pinMode (NoProgramLED_Port, OUTPUT);
  pinMode (Program1LED_Port, OUTPUT);
  pinMode (Program2LED_Port, OUTPUT);
  pinMode (ServoPowerSource_Port, OUTPUT);

  //Sensors tracking initialization
  pinMode(Up_Port,INPUT);
  pinMode(Right_Port,INPUT);
  pinMode(Down_Port,INPUT);
  pinMode(Left_Port,INPUT);
  pinMode(Light_Port,OUTPUT);

  horizontalServo.attach(HorizontalServo_Port);
  verticalServo.attach(VerticalServo_Port);
  foldingRightSide.attach(foldingRightSide_Port, SERVO_MIN_IMP, SERVO_MAX_IMP);
  foldingLeftSide.attach(foldingLeftSide_Port, SERVO_MIN_IMP, SERVO_MAX_IMP);

  //Remote initialization
  irrecv.enableIRIn();
  Timer1.initialize(500000);
  Timer1.start();
  Timer1.attachInterrupt(checkIsButtonPressed);
}

//The input parameter for the function:
//  0 - from the bottom to the middle
//  1 - from the middle to the bottom
//  2 - from the middle to the high
//  3 - from the high to the middle
//  4 - from any to the middle
void foldFrame(const unsigned int foldingType)
{
  unsigned int cnt;
 
  if (0U == foldingType)  
  {
    for (cnt = 1U; cnt < 500U; cnt++)
    {
      foldingLeftSide.writeMicroseconds(2000U - cnt);
      foldingRightSide.writeMicroseconds(1000U + cnt);
      delay(10U);
    }
    foldingLeftSide.writeMicroseconds(1300U);
    foldingRightSide.writeMicroseconds(1700U);
    delay(500U);
    foldingLeftSide.writeMicroseconds(1500U);
    foldingRightSide.writeMicroseconds(1500U);
    delay(500U);
  }

  if (1U == foldingType) 
    for (cnt = 1U; cnt < 630U; cnt++)
    {
      foldingLeftSide.writeMicroseconds(1420U + cnt);
      foldingRightSide.writeMicroseconds(1580U - cnt);
      delay(20U);
    }

  if (2U == foldingType) 
    for (cnt = 1U; cnt < 400U; cnt += 2U)
    {
      foldingLeftSide.writeMicroseconds(1420U - cnt);
      foldingRightSide.writeMicroseconds(1580U + cnt);
      delay(20U);
    }
  
  if (3U == foldingType) 
    for (cnt = 1U; cnt < 500U; cnt++)
    {
      foldingLeftSide.writeMicroseconds(920U + cnt);
      foldingRightSide.writeMicroseconds(2080U - cnt);
      delay(20U);
    }
  
  if (4U == foldingType)  
  {
    foldingLeftSide.writeMicroseconds(1300U);
    foldingRightSide.writeMicroseconds(1700U);
    delay(500U);
    foldingLeftSide.writeMicroseconds(1500U);
    foldingRightSide.writeMicroseconds(1500U);
    delay(500U);
  }
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
    digitalWrite(RightFrontWheel_Port1, HIGH);
    digitalWrite(RightFrontWheel_Port2, LOW); 
    analogWrite(RightFrontWheelSpeed_Port, newSpeed + BALANCING_COEFF2);   
  }
  else
  {
    digitalWrite(RightFrontWheel_Port1, LOW);
    digitalWrite(RightFrontWheel_Port2, HIGH); 
    analogWrite(RightFrontWheelSpeed_Port, newSpeed + BALANCING_COEFF1);   
  }
  delay(30U);
}

void moveRightRearWheel(const unsigned int newSpeed, const unsigned int newDirection)
{
  if (0U == newDirection) 
  {
    digitalWrite(RightRearWheel_Port1, HIGH);
    digitalWrite(RightRearWheel_Port2, LOW); 
    analogWrite(RightRearWheelSpeed_Port, newSpeed);
  }
  else
  {
    digitalWrite(RightRearWheel_Port1, LOW);
    digitalWrite(RightRearWheel_Port2, HIGH); 
    analogWrite(RightRearWheelSpeed_Port, newSpeed + BALANCING_COEFF1);   
  }
  delay(30U);
}

void checkIsButtonPressed()
{
  if (irrecv.decode(&whichButton))
  {
    fromRemote = whichButton.value, DEC;
    irrecv.resume();
    //Serial.println(f);
  }
}

void trackObject()
{
  unsigned int isFirstIteration = 1U;
  unsigned int angle = 2U;
  unsigned int x = 90U;
  unsigned int y = 90U;
  while (true)
  {
    checkIsButtonPressed();
  
    if  (BUTTON_MAIN_MENU == fromRemote)
      break; 
    digitalWrite(ServoPowerSource_Port, LOW);
    if (isFirstIteration)
    {
      horizontalServo.write(x);
      verticalServo.write(y);
      delay(500U);
      isFirstIteration = 0U; 
    }

    //Serial.print(digitalRead(Up_Port));
    //Serial.print(digitalRead(Right_Port));
    //Serial.print(digitalRead(Down_Port));
    //Serial.print(digitalRead(Left_Port));
  
    // Turn in the direction of departure of the object horizontally and vertically
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
  
    // Turn in the direction of departure of the object diagonally
    if ((digitalRead(Up_Port) == 1U) && (digitalRead(Right_Port) == 1U) && (digitalRead(Down_Port) == 0U) && (digitalRead(Left_Port) == 0U) && (y < MAX_ANGLE) && (x > MIN_ANGLE))
    {
      x -= angle;
      y += angle;
      horizontalServo.write(x);
      verticalServo.write(y);
      delay(40U);
    }
  
    if ((digitalRead(Up_Port) == 0U) && (digitalRead(Right_Port) == 1U) && (digitalRead(Down_Port) == 1U) && (digitalRead(Left_Port) == 0U) && (y > MIN_ANGLE) && (x > MIN_ANGLE))
    {
      x -= angle;
      y -= angle;
      horizontalServo.write(x);
      verticalServo.write(y);
      delay(40U);
    }
  
    if ((digitalRead(Up_Port) == 0U) && (digitalRead(Right_Port) == 0U) && (digitalRead(Down_Port) == 1U) && (digitalRead(Left_Port) == 1U) && (y > MIN_ANGLE) && (x < MAX_ANGLE))
    {
      x += angle;
      y -= angle;
      horizontalServo.write(x);
      verticalServo.write(y);
      delay(40U);
    }
    
    if ((digitalRead(Up_Port) == 1U) && (digitalRead(Right_Port) == 0U) && (digitalRead(Down_Port) == 0U) && (digitalRead(Left_Port) == 1U) && (y < MAX_ANGLE) && (x < MAX_ANGLE))
    {
      x += angle;
      y += angle;
      horizontalServo.write(x);
      verticalServo.write(y);
      delay(40U);
    }
  
    // Turn in the direction of appearance of the object horizontally and vertically
    if ((digitalRead(Up_Port) == 0U) && (digitalRead(Right_Port) == 1U) && (digitalRead(Down_Port) == 1U) && (digitalRead(Left_Port) == 1U) && (y > MIN_ANGLE))
    {
      y -= angle;
      verticalServo.write(y); 
      delay(40U);
    }
  
    if ((digitalRead(Up_Port) == 1U) && (digitalRead(Right_Port) == 1U) && (digitalRead(Down_Port) == 0U) && (digitalRead(Left_Port) == 1U) && (y < MAX_ANGLE))
    {
      y += angle;
      verticalServo.write(y);
      delay(40U);
    }
  
    if ((digitalRead(Up_Port) == 1U) && (digitalRead(Right_Port) == 1U) && (digitalRead(Down_Port) == 1U) && (digitalRead(Left_Port) == 0U) && (x > MIN_ANGLE))
    {
      x -= angle;
      horizontalServo.write(x); 
      delay(40U);
    }
  
    if ((digitalRead(Up_Port) == 1U) && (digitalRead(Right_Port) == 0U) && (digitalRead(Down_Port) == 1U) && (digitalRead(Left_Port) == 1U) && (x < MAX_ANGLE))
    {
      x += angle;
      horizontalServo.write(x);
      delay(40U);
    }
  }
}

void stopPlatform()
{
  moveLeftFrontWheel(0U, 1U);
  moveLeftRearWheel(0U, 1U);
  moveRightFrontWheel(0U, 0U);
  moveRightRearWheel(0U, 0U);
}

void moveToLight()
{
  unsigned int i;
  foldFrame(4U);
  digitalWrite(ServoPowerSource_Port, LOW);
  delay(100U);
  verticalServo.write(90U);
  delay(500U); 
  digitalWrite(ServoPowerSource_Port, HIGH);
  delay(2000U);
   
  for (i = 1U; i < 230U; i += 5U)
  {
    moveLeftFrontWheel(i, 1U);
    moveLeftRearWheel(i, 1U);
    moveRightFrontWheel(i, 1U);
    moveRightRearWheel(i, 1U); 
  }
  delay(1000U);
  stopPlatform();
  delay(3000U);
}

void findAndMoveToLight()
{
  static unsigned int isBeginning = 1U;
  unsigned int sector = 0U;
  unsigned int maxLuminance = 0U;
  unsigned int angleMaxLuminance = 0U;
  unsigned int turnToFoundLight_Speed = 0U;
  unsigned int i, turnToNewSector_Speed, lightDifference;
  unsigned int finish = 0U;
  unsigned int isLightFound = 0U;
    
  foldFrame(4U);
  digitalWrite(ServoPowerSource_Port, LOW);
    
  if (isBeginning)
  {
    verticalServo.write(110U);
    horizontalServo.write(92U);
    delay(1000U);
    isBeginning = 0U;
  }

  //Find the light source
  maxLuminance = 0U;
  while ((maxLuminance < 100U) && (!finish))
  { 
    if (BUTTON_MAIN_MENU == fromRemote)
    {
      finish = 1U;
      break;
    } 
    verticalServo.write(110U);
    horizontalServo.write(6U);
    delay(500U);

    stopPlatform();
    digitalWrite(ServoPowerSource_Port, LOW);
    delay(1000U);
    foldFrame(4U);
    delay(2000U);
    sector = 10U;
    maxLuminance = 0U;
    angleMaxLuminance = 0U;
    delay(1000U);

    for (i = 0U; i <= 85U; i += 1U)
    {
      if (BUTTON_MAIN_MENU == fromRemote)
      {
        finish = 1U;
        break;
      }
      //Serial.println(maxLuminance);
      if (sector <= 180U)
      {
        if (maxLuminance < analogRead(A0))
        {
          maxLuminance = analogRead(A0);
          angleMaxLuminance = sector;
        }
        Serial.println(analogRead(A0));
        horizontalServo.write(sector);
        delay(200U);
        sector += 2U;
      }
    }
      
    if ((maxLuminance < 100U) && (!finish))
    {
      digitalWrite(ServoPowerSource_Port, HIGH);
      foldFrame(2U);
      delay(3000U);
      for (turnToNewSector_Speed = 200U; turnToNewSector_Speed < 220U; turnToNewSector_Speed += 2U)
      { 
        moveLeftFrontWheel(turnToNewSector_Speed, 1U);
        moveLeftRearWheel(turnToNewSector_Speed, 1U);
        moveRightFrontWheel(turnToNewSector_Speed, 0U);
        moveRightRearWheel(turnToNewSector_Speed, 0U); 
        delay(30U);
      }
    }
  }

  if (!finish)
  {
    //Move to the light
    digitalWrite(ServoPowerSource_Port, LOW);
    horizontalServo.write(angleMaxLuminance);
    delay(3000U);
    verticalServo.write(90U);
    horizontalServo.write(90U);
    delay(1000U);
    foldFrame(2U); 
    delay(3000U);
    
    //Serial.print(abs(maxLuminance - analogRead(A0)));
    //Serial.print(' ');
    //Serial.println(angleMaxLuminance);
    
    lightDifference = abs(maxLuminance-analogRead(A0));
    isLightFound = 0U;
    turnToFoundLight_Speed = 170U;
    if (lightDifference <= MAX_ERROR)
    {
      moveToLight();
      finish = 1U;
    } 

    if (BUTTON_MAIN_MENU == fromRemote)
      finish = 1U;
    
    if ((angleMaxLuminance < 90U) && (lightDifference > MAX_ERROR) && (!finish))
    {    
      turnToFoundLight_Speed = 210U;
      digitalWrite(ServoPowerSource_Port, HIGH);
      moveLeftFrontWheel(turnToFoundLight_Speed, 1U);
      moveLeftRearWheel(turnToFoundLight_Speed, 1U);
      moveRightFrontWheel(turnToFoundLight_Speed, 0U);
      moveRightRearWheel(turnToFoundLight_Speed, 0U); 
      
      while (lightDifference > MAX_ERROR)
      {
        lightDifference = abs(maxLuminance - analogRead(A0));
        //Serial.print(maxLuminance);
        //Serial.print(" ");
        //Serial.println(analogRead(A0));
        if (lightDifference < MAX_ERROR)
        {
          stopPlatform();
          isLightFound = 1U;
          break; 
        }
      }
    }
    stopPlatform();
    delay(1000U);
    if ((isLightFound) && (!finish))
    {
      moveToLight();
      finish = 1U;
    }

    if (BUTTON_MAIN_MENU == fromRemote)
      finish = 1U;
      
    if ((angleMaxLuminance > 90U) && (lightDifference > MAX_ERROR) && (!finish))
    {
      turnToFoundLight_Speed = 210U;
      digitalWrite(ServoPowerSource_Port, HIGH);
      moveLeftFrontWheel(turnToFoundLight_Speed, 0U);
      moveLeftRearWheel(turnToFoundLight_Speed, 0U);
      moveRightFrontWheel(turnToFoundLight_Speed, 1U);
      moveRightRearWheel(turnToFoundLight_Speed, 1U);

      while (lightDifference > MAX_ERROR)
      {
        lightDifference = abs(maxLuminance - analogRead(A0)); 
        //Serial.print(maxLuminance);
        //Serial.print(" ");
        //Serial.println(analogRead(A0));
        if (lightDifference < MAX_ERROR)
        {
          stopPlatform();
          isLightFound = 1U;
          break; 
        }
      }
    }
    if ((isLightFound) && (!finish))
    {
      moveToLight();
      finish = 1U;
    }
  }
}

void demonstration()
{
  unsigned int i;

  digitalWrite(ServoPowerSource_Port, HIGH);
  foldFrame(1U);
  delay (1000U);
  foldFrame(0U);
  delay (1000U);
  foldFrame(2U);
  delay (1000U);
  foldFrame(3U);
  delay (1000U);

  if (fromRemote != BUTTON_MAIN_MENU)
  {
    for (i = 0U; i < 200U; i += 5U)
    {
      moveLeftFrontWheel(i, 1U);
      moveLeftRearWheel(i, 1U);
      moveRightFrontWheel(i, 1U);
      moveRightRearWheel(i, 1U);
    }
    delay (500U);
    stopPlatform();
    delay (2000U);
    
    for (i = 0U; i < 200U; i += 5U)
    {
      moveLeftFrontWheel(i, 0U);
      moveLeftRearWheel(i, 0U);
      moveRightFrontWheel(i, 0U);
      moveRightRearWheel(i, 0U);
    }
    delay (500U);
    stopPlatform();
    foldFrame(2U);
    delay(1000U);
    
    for (i = 0U; i < 200U; i += 5U)
    {
      moveLeftFrontWheel(i, 1U);
      moveLeftRearWheel(i, 1U);
      moveRightFrontWheel(i, 1U);
      moveRightRearWheel(i, 1U);
    }
    delay (500U);
    stopPlatform();
    delay(1000U);
  
    for (i = 0U; i < 200U; i += 5U)
    {
      moveLeftFrontWheel(i, 0U);
      moveLeftRearWheel(i, 0U);
      moveRightFrontWheel(i, 0U);
      moveRightRearWheel(i, 0U);
    }
    delay (500U);
    stopPlatform();
    delay(1000U);
  
    for (i = 200U; i < 230U; i += 5U)
    {
      moveLeftFrontWheel(i, 0U);
      moveLeftRearWheel(i, 0U);
      moveRightFrontWheel(i, 1U);
      moveRightRearWheel(i, 1U);
    }
    delay (2000U);
    stopPlatform();
    delay(2000U);
  
    for (i = 200U; i < 230U; i += 5U)
    {
      moveLeftFrontWheel(i, 1U);
      moveLeftRearWheel(i, 1U);
      moveRightFrontWheel(i, 0U);
      moveRightRearWheel(i, 0U);
    }
    delay (2000U);
    stopPlatform();
    delay(2000U);
    
    foldFrame(4U);
    for (i = 200U; i < 230U; i += 5U)
    {
      moveLeftFrontWheel(i, 0U);
      moveLeftRearWheel(i, 0U);
      moveRightFrontWheel(i, 1U);
      moveRightRearWheel(i, 1U);
    }
    delay (2000U);
    stopPlatform();
    delay(2000U);
  
    for (i = 200U; i < 230U; i += 5U)
    {
      moveLeftFrontWheel(i, 1U);
      moveLeftRearWheel(i, 1U);
      moveRightFrontWheel(i, 0U);
      moveRightRearWheel(i, 0U);
    }
    delay (2000U);
    stopPlatform();
    delay(2000U); 
  }
}

void loop()
{
  digitalWrite(Program1LED_Port, LOW); 
  digitalWrite(Program2LED_Port, LOW); 
  digitalWrite(NoProgramLED_Port, HIGH);
  digitalWrite(Light_Port, HIGH);
  checkIsButtonPressed();

  if (BUTTON_PROGRAM1 == fromRemote)
  { 
    digitalWrite(Program1LED_Port, HIGH); 
    digitalWrite(Program2LED_Port, LOW); 
    digitalWrite(NoProgramLED_Port, LOW);
    findAndMoveToLight();
  }
  
  if (BUTTON_PROGRAM2 == fromRemote)
  {
    digitalWrite(Program1LED_Port, LOW); 
    digitalWrite(Program2LED_Port, HIGH); 
    digitalWrite(NoProgramLED_Port, LOW);
    digitalWrite(Light_Port, LOW);
    trackObject();
  }

  if (BUTTON_4 == fromRemote)
  {
    digitalWrite(Program1LED_Port, LOW); 
    digitalWrite(Program2LED_Port, HIGH); 
    digitalWrite(NoProgramLED_Port, HIGH);
    demonstration();
  }
}
