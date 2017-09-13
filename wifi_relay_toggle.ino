#include <ESP8266WiFi.h>

const char* ssid = "OPTUS_4E8088";
const char* password = "xylicniffs94001";
 
int ledPin = D6;
int ledPin2 = D5;

WiFiServer server(80);
IPAddress ip(192, 168, 0, 80); // where xx is the desired IP Address
IPAddress gateway(192, 168, 0, 1); // set gateway to match your network
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
 
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
 
   if (request.indexOf("/BUTTON1ON") != -1) {
    digitalWrite(ledPin, HIGH);
   }
   if (request.indexOf("/BUTTON1OFF") != -1) {
    digitalWrite(ledPin, LOW);
   } 
    
    if (request.indexOf("/BUTTON2ON") != -1) {
    digitalWrite(ledPin2, HIGH);
   } 
   if (request.indexOf("/BUTTON2OFF") != -1) {
    digitalWrite(ledPin, LOW);
   } 
   
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  
  //client.println("Refresh: 5");  
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  //client.println("<br><br>");
  client.println("Switch 1: ");
  client.println("<a href=\"/BUTTON1ON\">On</a> ");
  client.println("<a href=\"/BUTTON1OFF\">Off</a><br>");
  client.println("Switch 2: ");
  client.println("<a href=\"/BUTTON2ON\">On</a> ");
  client.println("<a href=\"/BUTTON2OFF\">Off</a><br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
