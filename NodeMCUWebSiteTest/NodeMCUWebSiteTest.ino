#include <ESP8266WiFi.h>

WiFiServer espServer(80);

int RightMotor;
int LeftMotor;

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin("YONKOVI", "0887694113");  //WiFi name and password
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  espServer.begin();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());  //writes the ip to witch to connect
}
void loop() {
  WiFiClient client = espServer.available();
  if (!client) {
    return;
  }
  String request = client.readStringUntil('\r'); /* Read the first line of the request from client */
  Serial.println(request);                       /* Print the request on the Serial monitor */
  /* The request is in the form of HTTP GET Method */
  client.flush();

  if (request.indexOf("/forward") != -1) {
    Serial.println("Moving forward");
  }
  if (request.indexOf("/left") != -1) {
    Serial.println("Moving left");
  }
  if (request.indexOf("/right") != -1) {
    Serial.println("Moving right");
  }
  if (request.indexOf("/backward") != -1) {
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
  client.println("<title>NODE MCU Controller</title>");
  client.println("<style>");
  client.println(".holdButton {");
  client.println("padding:0px;");
  client.println("margin: 0px;");
  client.println("font-size: 100px;");
  client.println("width:  170px;");
  client.println("height: 170px;");
  client.println("}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<center>");
  client.println("<h4>Контролер на количка с ESP8266</h4>");
  client.println("<hr>");
  client.println("<br>");


  client.println("<a href=\"/left\" onmousedown=\"startHold('/left')\" onmouseup=\"endHold()\" ontouchstart=\"startHold('/left')\" ontouchend=\"endHold()\"> <button class=\"holdButton\" id=\"leftButton\"> &lArr; </button> </a>");
  client.println("<a href=\"/forward\" onmousedown=\"startHold('/forward')\" onmouseup=\"endHold()\" ontouchstart=\"startHold('/forward')\" ontouchend=\"endHold()\"> <button class=\"holdButton\" id=\"forwardButton\"> &uArr; </button> </a>");
  client.println("<a href=\"/backward\" onmousedown=\"startHold('/backward')\" onmouseup=\"endHold()\" ontouchstart=\"startHold('/backward')\" ontouchend=\"endHold()\"> <button class=\"holdButton\" id=\"backwardButton\"> &dArr; </button> </a>");
  client.println("<a href=\"/right\" onmousedown=\"startHold('/right')\" onmouseup=\"endHold()\" ontouchstart=\"startHold('/right')\" ontouchend=\"endHold()\"> <button class=\"holdButton\" id=\"rightButton\"> &rArr; </button> </a>");

  client.println("</center>");
  client.println("<script>");
  client.println("");
  // Map to store button state and interval ID for each button
  client.println("const buttonStates = {};");

  // Function to be called when a button is pressed
  client.println("function startHold(url) {");
  client.println(" const buttonId = url;");  // Use the URL as the buttonId for simplicity");
  client.println("  buttonStates[buttonId] = {");
  client.println("    isHolding: true,");
  client.println("    intervalId: setInterval(function() {");
  client.println("     if (buttonStates[buttonId].isHolding) {");
  client.println("       console.log(`Holding ${buttonId}...`);");

  // Send an HTTP request to the specified URL using fetch API");
  client.println("        fetch(url, {");
  client.println("          method: 'GET'");
  client.println("       })");
  client.println("       .then(response => {");
  client.println("        if (!response.ok) {");
  client.println("          throw new Error('Network response was not ok');");
  client.println("        }");
  client.println("        return response.json();");
  client.println("      })");
  client.println("      .then(data => {");
  client.println("       console.log(`HTTP request for ${buttonId} successful!`);");
  // You can process the response data if needed
  client.println("      })");
  client.println("     .catch(error => {");
  client.println("       console.error(`Error for ${buttonId}:`, error);");
  client.println("     });");
  client.println("   }");
  client.println("  }, 500)");  // Adjust the interval as needed
  client.println("}");
  client.println("}");

  // Function to be called when a button is released
  client.println("function endHold() {");
  // Since we're using URLs as button IDs, we don't need to handle endHold individually for each button
  client.println(" for (const buttonId in buttonStates) {");
  client.println("   if (buttonStates.hasOwnProperty(buttonId)) {");
  client.println("    buttonStates[buttonId].isHolding = false;");
  client.println("    clearInterval(buttonStates[buttonId].intervalId);");
  client.println("  }");
  client.println(" }");
  client.println(" }");
  client.println("</script>");
  
  client.println("</body>");
  client.println("</html>");
  client.println("<hr>");

  client.stop();
  Serial.println("Client disconnected");
  Serial.print("\n");
}
