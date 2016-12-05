//This example will set up a static IP - in this case 192.168.0.31
 
#include <ESP8266WiFi.h>
#include <Servo.h>
Servo myservo; 

const char* ssid = "BigPond0293_2GEXT";
const char* password = "0364241723";
 
int ledPin = D5;
WiFiServer server(80);
IPAddress ip(192, 168, 0, 31); // where xx is the desired IP Address
IPAddress gateway(192, 168, 0, 1); // set gateway to match your network
 
void setup() {
  Serial.begin(115200);
  delay(10);
 myservo.attach(4);  // attaches the servo on GIO2 to the servo object 
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  int servo = LOW;
  if (request.indexOf("/TURN_SERVO_ON") != -1)
  {
   servo=HIGH; 
  }
  if (request.indexOf("/TURN_SERVO_OFF") != -1)
  {
    servo=LOW;
  }

  switch(servo)
  {
    case HIGH:
    {
      int pos;

      for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      } 
      for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
      {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
      }
     break;
    }
    case LOW:
    {
     break; 
    }
    
  }
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.print("\n");
  client.print("servo is now: ");
 
  if(servo == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 5 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 5 OFF<br>");
  client.println("Click <a href=\"/TURN_SERVO_ON\">here</a> to power on the servo<br>");
  client.println("Click <a href=\"/TURN_SERVO_OFF\">here</a> to stop the servo<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
