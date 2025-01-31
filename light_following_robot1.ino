// C++ code

#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd_1(32, 16, 2); 

int turnSpeed=50; //adjusted practically

void back(int speed) //speed is a variable ranging from 0-255
{
  analogWrite(5, speed);
  analogWrite(6, speed);
  digitalWrite(1,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
}

void front(int speed) //speed is a variable ranging from 0-255
{
  analogWrite(5, speed);
  analogWrite(6, speed);
  digitalWrite(1,HIGH);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
}

void stop() 
{
  analogWrite(6,0);
  analogWrite(5,0);
}

void turnRight()
{
  analogWrite(5, turnSpeed);
  analogWrite(6, turnSpeed);
  digitalWrite(1,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
}

void turnLeft()
{
  analogWrite(5, turnSpeed);
  analogWrite(6, turnSpeed);
  digitalWrite(1,HIGH);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  //next 4 lines are for setting up the I2C LCD
  lcd_1.init(); 
  lcd_1.setCursor(0, 0); 
  lcd_1.backlight(); 
  lcd_1.display();
}

void loop()
{
  int left=analogRead(A1); //6 when 0, 70-679 when used
  int right=analogRead(A2);
  float vfactor=0.0;
  int velocity=9999999; //junk value 
   
  if(left==right)
  {
    if(left==6 and right==6)
      stop();
    else
    {
      vfactor= 1-(left-69)/610;
      velocity=(vfactor*255); //finds a factor for velocity so that velocity increases 
      front(velocity);        //when intensity increases and vice versa 
    }
  }
  else if(left>right)
    turnLeft();
  else
    turnRight();
    
  Serial.println(left);
  Serial.println(right);
  Serial.println(velocity);
}