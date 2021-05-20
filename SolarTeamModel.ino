///DO MODYFIKACJI-----------------------------------------------------------------
#define LEFT_SERVO_PIN 7
#define LEFT_SERVO_MAX 50
#define LEFT_SERVO_MIN 20

#define RIGHT_SERVO_PIN 8
#define RIGHT_SERVO_MAX 100
#define RIGHT_SERVO_MIN 20

#define SWORD_SERVO_PIN 12
#define SWORD_SERVO_MAX 180
#define SWORD_SERVO_MIN 0

#define POTENTIOMETER_PIN A1

#define THREAD_DELAY 5
#define SERWO_MOVE_DELAY 10
#define DEBUG

//-----------------------KOD-----------------------------------------------------
#define ANALOG POTENTIOMETER_PIN

#ifdef DEBUG
  #define DebugStart(x)   Serial.begin(x)
  #define DebugPrint(x)   Serial.print(x)
  #define DebugPrintln(x) Serial.println(x)
#else
  #define DebugStart(x)
  #define DebugPrint(x)   
  #define DebugPrintln(x) 
#endif


#include <Servo.h>
Servo simple, left, right;
short simplePos = ((SWORD_SERVO_MAX + SWORD_SERVO_MIN) / 2);
short leftPos = ((LEFT_SERVO_MAX + LEFT_SERVO_MIN) / 2);
short rightPos = ((RIGHT_SERVO_MAX + RIGHT_SERVO_MIN) / 2);
short pos = 512;

void Move();
void ServoMove(Servo&,short&, short);
bool Check(short);

void setup() 
{
  simple.attach(SWORD_SERVO_PIN);
  right.attach(RIGHT_SERVO_PIN);
  left.attach(LEFT_SERVO_PIN);

  simple.write(simplePos);
  left.write(leftPos);
  right.write(rightPos);
  
  pinMode(ANALOG, INPUT);

  DebugStart(9600);
}

void loop() {
  if(Check(analogRead(ANALOG) - pos))
    Move(); 

  delay(THREAD_DELAY);
}

bool Check(short x)
{
  if(abs(x) < 4)
    return false;
    
  return true;
}

void Move()
{  
  pos = analogRead(ANALOG);
  short robocza;
  DebugPrint("Polozenie potencjometru: "); DebugPrintln(pos);

  ServoMove(simple, simplePos, robocza =  map(pos,0,1023,SWORD_SERVO_MIN,SWORD_SERVO_MAX) );
  DebugPrint("Sword: "); DebugPrint(robocza);

  ServoMove(left, leftPos, robocza =   map(pos,0,1023,LEFT_SERVO_MIN,LEFT_SERVO_MAX) );
  DebugPrint("\tLeft: "); DebugPrint(robocza);

  ServoMove(right, rightPos, robocza =  map(pos,0,1023,RIGHT_SERVO_MIN,RIGHT_SERVO_MAX) );  
  DebugPrint("\tRight: "); DebugPrintln(robocza);
}

void ServoMove(Servo& serwo, short& actPos, short newPos)
{
  if (actPos > newPos)
    for (int i = actPos; i >= newPos; i--)
    {
      serwo.write(i);
      delay(SERWO_MOVE_DELAY);
    }

  else if (actPos < newPos)
    for (int i = actPos; i <= newPos; i++)
    {
      serwo.write(i);
      delay(SERWO_MOVE_DELAY);
    }

  actPos = newPos;
}
