//
//
const char* ssid = "Noth";
const char* password = "11111111";
WiFiServer server(80);
String header;
String lastDirection = "None";
String actionMessage = "Ready";
String dpadStatus = "STOPPED";  // New variable to track D-pad status
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void Wireless() {
  Serial.print("Connecting to Wi-Fi network: ");
  Serial.println(ssid);
  // Set the Wi-Fi mode to Station (client)
  WiFi.disconnect();        // Clear any old connection attempts
  delay(1000);
  WiFi.mode(WIFI_STA);      // Explicitly set as a "Station" (client)
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("Attempting to connect...");
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 1) {
    delay(1000);
    int s = WiFi.status();
    Serial.print("Attempt ");
    Serial.print(attempt);
    Serial.print(" - Status: ");
    Serial.println(s);
    attempt++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nCONNECTED!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } 
  else {
    Serial.println("\nFAILED. Check if your router is blocking WPA2 devices.");
  }
  server.begin();
  }

void blank() {
  WiFiClient client = server.accept();
  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    //Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // --- Directional & Action Logic ---
            if (header.indexOf("GET /up") >= 0) {
              Serial.println("Direction: UP - CONTINUOUS");
              Motor_Lift(2);
              lastDirection = "UP (\u25B2)";
              dpadStatus = "MOVING";
            }
            else if (header.indexOf("GET /down") >= 0) {
              Serial.println("Direction: DOWN - CONTINUOUS");
              Motor_Lift(1);
              lastDirection = "DOWN (\u25BC)";
              dpadStatus = "MOVING";
            }
            else if (header.indexOf("GET /left") >= 0) {
              Serial.println("Direction: LEFT - CONTINUOUS");
              Motor_Platform(1);
              lastDirection = "LEFT (\u25C0)";
              dpadStatus = "MOVING";
            }
            else if (header.indexOf("GET /right") >= 0) {
              Serial.println("Direction: RIGHT - CONTINUOUS");
              Motor_Platform(2);
              lastDirection = "RIGHT (\u25B6)";
              dpadStatus = "MOVING";
            }
            else if (header.indexOf("GET /stop") >= 0) {
              // *** ACTION TO PERFORM ON BUTTON RELEASE ***
              Serial.println("Final Action: STOP/CENTERING");
              lastDirection = "None";
              dpadStatus = "STOPPED";
              // Add your motor/servo finalization code here!
              // Example: servo.write(90); or motor.stop();
              Disable_ALL();
            }
            else if (header.indexOf("GET /action1") >= 0) {
              Serial.println("Action 1 Pressed");
              actionMessage = "ACTION 1 ENGAGED";
            }
            else if (header.indexOf("GET /action2") >= 0) {
              Serial.println("Action 2 Pressed");
              actionMessage = "ACTION 2 ENGAGED";
            }
            else if (header.indexOf("GET /action3") >= 0) {
              Serial.println("Action 3 Pressed");
              actionMessage = "ACTION 3 ENGAGED";
            }
            else if (header.indexOf("GET /action4") >= 0) {
              Serial.println("Action 4 Pressed");
              actionMessage = "ACTION 4 ENGAGED";
            }
            // --- HTML Response ---
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".action-button { background-color: #4CAF50; border: none; color: white; padding: 16px 20px; text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer; width: 100px; display: inline-block;}");
            client.println(".dir-button { background-color: #3f51b5; border: none; color: white; padding: 10px 20px; text-decoration: none; font-size: 24px; margin: 2px; cursor: pointer; width: 70px; height: 70px; line-height: 50px;}");
            client.println(".dpad-container { display: flex; flex-direction: column; align-items: center; }");
            client.println(".dpad-row { display: flex; justify-content: center; }");
            client.println(".status-stopped { color: #F23A3A; }");
            client.println(".status-moving { color: #4CAF50; }");
            client.println(".numpad-table { border-collapse: collapse; width: 150px; text-align: center; margin: 20px auto; border: none !important; background-color: #e9ecef;}");
            client.println(".numpad-table td, .numpad-table th { border: 1px solid #777 !important; padding: 5px; color: #333; font-weight: normal;}");
            client.println(".numpad-separator { background-color: #ff8c00 !important; color: white !important; font-size: 10px;}");
            client.println(".numpad-number-cell { font-weight: bold; background-color: #f8f9fa;}");
            client.println("</style>");
            client.println("<script>");
            client.println("var intervalId;");
            client.println("function sendCmd(cmd) {");
            client.println("  fetch(cmd);");
            client.println("}");
            client.println("function startAction(cmd) {");
            client.println("  sendCmd(cmd);");
            client.println("  intervalId = setInterval(() => sendCmd(cmd), 100);");
            client.println("}");
            client.println("function stopAction() {");
            client.println("  clearInterval(intervalId);");
            client.println("  sendCmd('/stop');");  // SEND /stop COMMAND HERE
            client.println("}");
            client.println("</script>");
            client.println("</head>");
            client.println("<p>Last Action: <strong>" + actionMessage + "</strong></p>");
            client.println("<div class=\"action-row\">");
            client.println("<a href=\"/action1\"><button class=\"action-button\">Action 1</button></a>");
            client.println("<a href=\"/action2\"><button class=\"action-button\">Action 2</button></a>");
            client.println("<a href=\"/action3\"><button class=\"action-button\">Action 3</button></a>");
            client.println("<a href=\"/action4\"><button class=\"action-button\">Action 4</button></a>");
            client.println("</div>");
            //client.println("<h2>Directional Control</h2>");
            client.print("<p>Status: <strong class=\"status-");
            client.print((dpadStatus == "STOPPED" ? "stopped" : "moving"));
            client.print("\">");
            client.print(dpadStatus);
            client.println("</strong> | Last Direction: <strong>" + lastDirection + "</strong></p>");

            client.println("<div class=\"dpad-container\">");

            client.println("<div class=\"dpad-row\">");
            client.println("<button class=\"dir-button\" onmousedown=\"startAction('/up')\" onmouseup=\"stopAction()\" ontouchstart=\"startAction('/up')\" ontouchend=\"stopAction()\">&#x25B2;</button>");
            client.println("</div>");

            client.println("<div class=\"dpad-row\">");
            client.println("<button class=\"dir-button\" onmousedown=\"startAction('/left')\" onmouseup=\"stopAction()\" ontouchstart=\"startAction('/left')\" ontouchend=\"stopAction()\">&#x25C0;</button>");
            client.println("<div style='width: 74px;'></div>");
            client.println("<button class=\"dir-button\" onmousedown=\"startAction('/right')\" onmouseup=\"stopAction()\" ontouchstart=\"startAction('/right')\" ontouchend=\"stopAction()\">&#x25B6;</button>");
            client.println("</div>");

            client.println("<div class=\"dpad-row\">");
            client.println("<button class=\"dir-button\" onmousedown=\"startAction('/down')\" onmouseup=\"stopAction()\" ontouchstart=\"startAction('/down')\" ontouchend=\"stopAction()\">&#x25BC;</button>");
            client.println("</div>");

            client.println("</div>");
            client.println("<table class=\"numpad-table\">");
            client.println("<thead><tr><th colspan=\"3\" class=\"numpad-separator\">|||||||||||||||||||</th></tr></thead>");
            client.println("<tbody>");
            client.println("<tr><td class=\"numpad-number-cell\">7</td><td class=\"numpad-number-cell\">8</td><td class=\"numpad-number-cell\">9</td></tr>");
            client.println("<tr><td colspan=\"3\" class=\"numpad-separator\">|||||||||||||||||||</td></tr>");
            client.println("<tr><td class=\"numpad-number-cell\">4</td><td class=\"numpad-number-cell\">5</td><td class=\"numpad-number-cell\">6</td></tr>");
            client.println("<tr><td colspan=\"3\" class=\"numpad-separator\">|||||||||||||||||||</td></tr>");
            client.println("<tr><td class=\"numpad-number-cell\">1</td><td class=\"numpad-number-cell\">2</td><td class=\"numpad-number-cell\">3</td></tr>");
            client.println("<tr><td colspan=\"3\" class=\"numpad-separator\">|||||||||||||||||||</td></tr>");
            client.println("<tr><td class=\"numpad-number-cell\">|   |</td><td class=\"numpad-number-cell\">|   |</td><td class=\"numpad-number-cell\">|   |</td></tr>");
            client.println("</tbody>");
            client.println("</table>");
            client.println("</body></html>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}