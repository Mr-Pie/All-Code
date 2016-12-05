int inbyte;

#include <IRremote.h>

IRsend irsend;

void setup()
{
   Serial.begin(9600);  
   inbyte = 0; 
}

void loop() 
{
    for (int i = 0; i < 3; i++) 
    {
      irsend.sendNEC(0x4EBB708F, 32);
      delay(40);      
      Serial.println("power on\n");
    }
    delay(5000);
    //irsend.sendNEC(0x4EBB926D, 32); //vol up
    //irsend.sendNEC(0x4EBBC23D, 32); //vol down
    //irsend.sendNEC(0x4EBB58A7, 32); //mute
    //irsend.sendNEC(0x4EBB8A75, 32); //chan up
    //irsend.sendNEC(0x4EBBB24D, 32); //chan down
    //irsend.sendNEC(0x4EBB7887, 32); //source
    //irsend.sendNEC(0x4EBB3AC5, 32); //enter
 }
	
