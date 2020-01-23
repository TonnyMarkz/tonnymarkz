

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "LAESE";
const char* password = "Laesewifi";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output26State2 = "off";
String output26State3 = "off";
String output26State4 = "off";
String output26State5 = "off";
String output26State6 = "off";
String output26State7 = "off";
String output26State8 = "off";

// Assign output variables to GPIO pins
//const int output26 = 26;
const int Analog_channel_pin= 34;
const int Analog_channel_pin2= 35;
const int Analog_channel_pin3= 32;

int ADC_VALUE = 0;
int ADC_VALUE2 = 0;
int ADC_VALUE3 = 0;
int voltage_value = 0;
int voltage_value2 = 0; 
int voltage_value3 = 0; 

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  // Set outputs to LOW
  pinMode(23, OUTPUT);//Definimos o pino 23 como saída.
  pinMode(22, OUTPUT);//Definimos o pino 22 como saída.

  ledcAttachPin(23, 0);//Atribuimos o pino 23 ao canal 0.
  ledcSetup(0, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  ledcAttachPin(22, 1);//Atribuimos o pino 22 ao canal 1.
  ledcSetup(1, 1000, 10);//Atribuimos ao canal 1 a frequencia de 1000Hz com resolucao de 10bits.

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            //1
            ADC_VALUE = analogRead(Analog_channel_pin);           
            delay(10);
            ledcWrite(0, 594);//Escrevemos um duty cycle de 25% no canal 0.

            voltage_value = (ADC_VALUE * 3.3 ) / (4095);
                                 
            // turns the GPIOs on and off
            if (voltage_value >= 1) {
              output26State = "on";
            } else if (voltage_value < 1) {
              output26State = "off";
            }
            //ADC_VALUE=0;
            //voltage_value=0;
            
            //2
            ADC_VALUE2 = analogRead(Analog_channel_pin2);           
            delay(10);
            //ledcWrite(1, 594);//Escrevemos um duty cycle de 25% no canal 0.

            voltage_value2 = (ADC_VALUE2 * 3.3 ) / (4095);
                                 
            // turns the GPIOs on and off
            if (voltage_value2 >= 1) {
              output26State2 = "on";
            } else if (voltage_value2 < 1) {
              output26State2 = "off";
            }
            //ADC_VALUE2=0;
            //voltage_value2=0;
            
            /*//3
            ADC_VALUE3 = analogRead(Analog_channel_pin3);
            //Serial.print("ADC VALUE = ");
            //Serial.println(ADC_VALUE);
            delay(1000);
            voltage_value3 = (ADC_VALUE3 * 3.3 ) / (4095);
            //Serial.print("Voltage = ");
            Serial.print(voltage_value3 );
            //Serial.print(" volts ");
            
            // turns the GPIOs on and off
            if (voltage_value3 >= 1) {
              Serial.println("Porta on");
              output26State3 = "on";
            } else if (voltage_value3 < 1) {
              Serial.println("Porta off");
              output26State3 = "off";
            }*/
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("body { background-color: #3D518C;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 20px;");
            client.println("text-decoration: none; font-size: 20px; font-weight: bold; margin: 2px; cursor: pointer; border-radius: 3px;}");
            client.println(".button2 {background-color: #ff0000;} h1 {padding: 2%; margin-bottom: 6%; border: 2px solid black;");
            client.println("outline: #7692FF solid 10px; background-color: white; margin-top: 1%;} span {border-style: solid; border-width: 5px;");
            client.println("margin: auto; padding-top: 5%; padding-bottom: 5%; padding-left: 10%; padding-right: 10%;");
            client.println("outline: #1B2CC1 solid 10px; background-color: #091540;} form { padding-top: 10%;}");
            client.println(".refresh{ background-color: #4CAF50;border: none; color: white; padding: 20px; text-align: center; text-decoration: none;");
            client.println("display: inline-block;font-size: 16px; margin: 4px 2px; cursor: pointer; border-radius: 16px; box-shadow: 0 9px #5f5f5f; font-weight: bold;}");
            client.println("}</style></head>"); 
            
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server - Monitor para Portas de Rede</h1><span>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            // If the output26State is off, it displays the ON button  1     
            if (output26State=="off") {
              client.println("<button class=\"button button2\">P1 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P1 - ON</button>");              
            }
            
            
            // If the output26State2 is off, it displays the ON button  2     
            if (output26State2=="off") {
              client.println("<button class=\"button button2\">P2 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P2 - ON</button>");              
            }

            
            // If the output26State3 is off, it displays the ON button  3     
            if (output26State3=="off") {
              client.println("<button class=\"button button2\">P3 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P3 - ON</button>");              
            }

            
            // If the output26State is off, it displays the ON button 4      
            if (output26State4=="off") {
              client.println("<button class=\"button button2\">P4 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P4 - ON</button>");              
            }

            
            // If the output26State is off, it displays the ON button  5     
            if (output26State5=="off") {
              client.println("<button class=\"button button2\">P5 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P5 - ON</button>");              
            }

            // If the output26State is off, it displays the ON button   6    
            if (output26State6=="off") {
              client.println("<button class=\"button button2\">P6 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P6 - ON</button>");              
            }

            // If the output26State is off, it displays the ON button   7    
            if (output26State7=="off") {
              client.println("<button class=\"button button2\">P7 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P7 - ON</button>");              
            }

            // If the output26State is off, it displays the ON button 8      
            if (output26State8=="off") {
              client.println("<button class=\"button button2\">P8 - OFF</button>");
            } else {
              client.println("<button class=\"button\">P8 - ON</button>");              
            }
            
            client.println("</span><form><button class=\"refresh\" value=\"Atualizar\" onClick=\"history.go(0)\">ATUALIZAR</button>");
            client.println("</form></body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            ADC_VALUE = 0;
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    delay(5000);
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
