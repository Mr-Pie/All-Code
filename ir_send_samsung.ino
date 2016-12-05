#include <IRremote.h>

IRsend irsend;


/*
  char volup    = 0xE0E0E01F;
  char voldown  = 0xE0E0D02F;
  char chanup   = 0xE0E048B7;
  char chandown = 0xE0E008F7;
  char poweron  = 0xE0E040BF;
  char source   = 0xE0E0807F;
  char enter    = 0xE0E016E9;
  char right    = 0xE0E046B9;
  char left     = 0xE0E046B9;
  char mute     = 0xE0E0F00F;
  char select;
  */
int button1 = 12;
int button2 = 11;
int button3 = 10;
int state1  = 0;
int state2  = 0;
int state3  = 0;
  String select= " "; 
void setup()
{

  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  //digitalWrite(button1, LOW);
  //digitalWrite(button3, LOW);
  //digitalWrite(button2, LOW);
  
}

void loop() 
{
  
  state1 = digitalRead(button1);
  state2 = digitalRead(button2);
  state3 = digitalRead(button3);
  
  if(state1==LOW)
  {
     select="0xE0E040BF";
    for (int i = 0; i < 3; i++) 
    {
      irsend.sendSAMSUNG(0xE0E040BF, 32);
      delay(40);
    }
  };
   if(state2==LOW)
    {
    select="0xE0E0807F";
    for (int i = 0; i < 3; i++) 
    {
      irsend.sendSAMSUNG(0xE0E0807F, 32);
      delay(40);
    }
  };
  if(state3==LOW)
  {
    select="0xE0E0F00F";
    for (int i = 0; i < 3; i++) 
    {
      irsend.sendSAMSUNG(0xE0E0F00F, 32);
      delay(40);
    }
  };
  
  Serial.println(select);
 select='.';
  delay(1000);

}
  


