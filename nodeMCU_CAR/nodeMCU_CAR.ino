#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>
#define rxPin 5
#define txPin 4
int value = 0;

const char* ssid = "B-LINK_9f1bf2"; //here we define our network credentials
const char* password = "";

SoftwareSerial serialToMega (rxPin, txPin);
WiFiServer server(80);

void setup() {
  serialToMega.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //   Serial.print(".");
  }
  // Serial.println("");
  //  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  //  Serial.println("Server started");
  // Print the IP address
  //  Serial.print("Use this URL to connect: ");
  //  Serial.print("http://");
  // Serial.print(WiFi.localIP());
  // Serial.println("/");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  //Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  //client.flush();

  // Match the request
  if (request.indexOf("/RIGHT") != -1)  { //here we have two options => 0 or -1. Boolean
    value = 1;
  }
  if (request.indexOf("/LEFT") != -1)  {
    value = 2;
  }
  if (request.indexOf("/FORWARD") != -1)  {
    value = 3;
  }
  if (request.indexOf("/BACKWARD") != -1)  {
    value = 4;
  }
  if (request.indexOf("/STOP") != -1)  {
    value = 0;
  }
  //  Serial.print(value);
  serialToMega.write(value);

  // Set ledPin according to the request
  //digitalWrite(ledPin, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Your car is moving ");

  if (value == 1) {
    client.print("RIGHT");
  } else if (value == 2) {
    client.print("LEFT");
  }
  else if (value == 3)
  {
    client.print("FORWARD");
  }
  else if (value == 4)
  {
    client.print("BACKWARD");
  }
  else if (value == 0)
  {
    client.print("STOP");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RIGHT\"\"><button>RIGHT </button></a>");
  client.println("<a href=\"/LEFT\"\"><button>LEFT </button></a><br />");
  client.println("<a href=\"/FORWARD\"\"><button>FORWARD </button></a><br />");
  client.println("<a href=\"/BACKWARD\"\"><button>BACKWARD </button></a><br />");
  client.println("<a href=\"/STOP\"\"><button>STOP </button></a><br />");
  client.println("</html>");
  delay(1);
}
