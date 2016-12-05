#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
 IRsend irsend(4);
const char* ssid = "BigPond0293_2GEXT";
const char* password = "0364241723";
 
WiFiServer server(80);
IPAddress ip(192, 168, 0, 31); // where xx is the desired IP Address
IPAddress gateway(192, 168, 0, 1); // set gateway to match your network
 
void setup() {
  irsend.begin();
  Serial.begin(115200);
  delay(10);
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
 
  if (request.indexOf("/POWER_ON") != -1) 
  {
    for(int i=0; i<4; i++)
    {
      irsend.sendSAMSUNG(0xE0E040BF, 32);
      delay(40);
    }
  } 
  if (request.indexOf("/CHAN_UP") != -1)
  {
   for(int i=0; i<4; i++)
   { 
    irsend.sendSAMSUNG(0xE0E048B7, 32);
    delay(40);
   }
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 

  client.println("<br><br>");
  client.println("Click <a href=\"/POWER_ON\">here</a> turn the power ON<br>");
  client.println("<br><br>");
  client.println("Click <a href=\"/CHAN_UP\">here</a> change the channel<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
 
