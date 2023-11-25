#include <ESP8266WiFi.h>

WiFiServer espServer(80);

int RightMotorForwardVal; 
int LeftMotorForwardVal;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin("YONKOVI", "0887694113"); //WiFi name and password
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  espServer.begin();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP()); //writes the ip to witch to connect
}
void loop()
{
  WiFiClient client = espServer.available();
  if(!client)
  {
    return;
  }
  String request = client.readStringUntil('\r'); /* Read the first line of the request from client */
  Serial.println(request); /* Print the request on the Serial monitor */
  /* The request is in the form of HTTP GET Method */ 
  client.flush();

  if (request.indexOf("/forward") != -1) 
  {
      Serial.println("Moving forward");
  } 
  if (request.indexOf("/left") != -1) 
  {
      Serial.println("Moving left");
  } 
  if (request.indexOf("/right") != -1) 
  {
      Serial.println("Moving right");
  } 
  if (request.indexOf("/backward") != -1) 
  {
      Serial.println("Moving backwards");
  } 

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en'>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width', initial-scale='1.0'>");
  client.println("<title>Document</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h4>Контрол на количка с ESP8266</h4>");
  client.println("<hr>");
  client.println("<br>");
  client.println("<a id='LeftButton' href=\"/left\"><button>Left</button></a>");
  client.println("<a href=\"/forward\"><button>Forward</button></a>");
  client.println("<a id='BackwardButton' href=\"/backward\"><button>Backwards</button></a>");
  client.println("<a id='RightButton' href=\"/right\"><button>Right</button></a>");
  client.println("</body>");
  client.println("</html>");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  


  client.stop();
  Serial.println("Client disconnected");
  Serial.print("\n");
}
