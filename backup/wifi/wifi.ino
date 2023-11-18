//esp 8266 bord download
//https://arduino.esp8266.com/stable/package_esp8266com_index.json
//html to c/c++ 
//https://tomeko.net/online_tools/cpp_text_escape.php?lang=en



//included Lib files
#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//initing liquid crystal i2c lcd config
LiquidCrystal_I2C lcd(0x27, 16, 2);


// local network name and password
const char* ssid = "Home";
const char* password = "home1111";

//globla variables
int bklightvar = 1 ;


//initing esp web server at port 80;
ESP8266WebServer server(80);


// Requested web server for debug
const char debugTxt[] PROGMEM={"<!DOCTYPE html>\n"
"    <html>\n"
"    <head>\n"
"        <meta http-equiv = 'refresh' content = '0; url =/' />\n"
"    </head>\n"
"    <body>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <p>Welcome Shourav How Are You Doing</p>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"        <br>\n"
"   </body>\n"
"  </html>"};




//Request web page for root
const char temp[] PROGMEM={"<!DOCTYPE html>\n"
"<html>\n"
"   <head>\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"      <style>\n"
"@import url('https://fonts.googleapis.com/css?family=Source+Code+Pro:200,900');\n"
"\n"
":root {\n"
"  --text-color: hsla(210, 50%, 85%, 1);\n"
"  --shadow-color: hsla(210, 40%, 52%, .4);\n"
"  --btn-color: hsl(210, 80%, 42%);\n"
"  --bg-color: #141218;\n"
"}\n"
"\n"
"* {\n"
"  box-sizing: border-box;\n"
"}\n"
"\n"
"html, body {\n"
"  width: 70%;\n"
"  height: 70%;\n"
"  display: flex;\n"
"  align-items: center;\n"
"  justify-content: center;\n"
"  background-color: var(--bg-color);\n"
"}\n"
"\n"
"button {\n"
"  position:relative;\n"
"  padding: 10px 20px;  \n"
"  border: none;\n"
"  background: none;\n"
"  cursor: pointer;\n"
"  \n"
"  font-family: \"Source Code Pro\";\n"
"  font-weight: 900;\n"
"  text-transform: uppercase;\n"
"  font-size: 30px;  \n"
"  color: var(--text-color);\n"
"  \n"
"  background-color: var(--btn-color);\n"
"  box-shadow: var(--shadow-color) 2px 2px 22px;\n"
"  border-radius: 4px; \n"
"  z-index: 0;  \n"
"  overflow: hidden;   \n"
"}\n"
"\n"
"button:focus {\n"
"  outline-color: transparent;\n"
"  box-shadow: var(--btn-color) 2px 2px 22px;\n"
"}\n"
"\n"
".right::after, button::after {\n"
"  content: var(--content);\n"
"  display: block;\n"
"  position: absolute;\n"
"  white-space: nowrap;\n"
"  padding: 40px 40px;\n"
"  pointer-events:none;\n"
"}\n"
"\n"
"button::after{\n"
"  font-weight: 200;\n"
"  top: -30px;\n"
"  left: -20px;\n"
"} \n"
"\n"
".right, .left {\n"
"  position: absolute;\n"
"  width: 100%;\n"
"  height: 100%;\n"
"  top: 0;\n"
"}\n"
".right {\n"
"  left: 66%;\n"
"}\n"
".left {\n"
"  right: 66%;\n"
"}\n"
".right::after {\n"
"  top: -30px;\n"
"  left: calc(-66% - 20px);\n"
"  \n"
"  background-color: var(--bg-color);\n"
"  color:transparent;\n"
"  transition: transform .4s ease-out;\n"
"  transform: translate(0, -90%) rotate(0deg)\n"
"}\n"
"\n"
"button:hover .right::after {\n"
"  transform: translate(0, -47%) rotate(0deg)\n"
"}\n"
"\n"
"button .right:hover::after {\n"
"  transform: translate(0, -50%) rotate(-7deg)\n"
"}\n"
"\n"
"button .left:hover ~ .right::after {\n"
"  transform: translate(0, -50%) rotate(7deg)\n"
"}\n"
"\n"
"/* bubbles */\n"
"button::before {\n"
"  content: '';\n"
"  pointer-events: none;\n"
"  opacity: .6;\n"
"  background:\n"
"    radial-gradient(circle at 20% 35%,  transparent 0,  transparent 2px, var(--text-color) 3px, var(--text-color) 4px, transparent 4px),\n"
"    radial-gradient(circle at 75% 44%, transparent 0,  transparent 2px, var(--text-color) 3px, var(--text-color) 4px, transparent 4px),\n"
"    radial-gradient(circle at 46% 52%, transparent 0, transparent 4px, var(--text-color) 5px, var(--text-color) 6px, transparent 6px);\n"
"\n"
"  width: 100%;\n"
"  height: 300%;\n"
"  top: 0;\n"
"  left: 0;\n"
"  position: absolute;\n"
"  animation: bubbles 5s linear infinite both;\n"
"}\n"
"\n"
"@keyframes bubbles {\n"
"  from {\n"
"    transform: translate();\n"
"  }\n"
"  to {\n"
"    transform: translate(0, -66.666%);\n"
"  }\n"
"}\n"
".change-color {\n"
"  fill: #fafffc;\n"
"}\n"
"</style>\n"
"   </head>\n"
"   <body>\n"
"      <a href=\"/light\"><button style=\"--content: 'LIGHT !';></a>\n"
"  <div class=\"left\"></div>\n"
"    LIGHT !\n"
"  <div class=\"right\"></div>\n"
"    \n"
"</button>\n"
"<a target=\"_blank\" href=\"/bklight\"><svg class=\"change-color\" style=\"width:100px;height:100px;position:fixed;top:5%;left:1em;opacity:.8;\" viewBox=\"0 0 24 24\"> <path fill-rule=\"evenodd\" d=\"M1 3.5a.5.5 0 0 1 .5-.5h13a.5.5 0 0 1 0 1h-13a.5.5 0 0 1-.5-.5zM8 6a.5.5 0 0 1 .5.5v5.793l2.146-2.147a.5.5 0 0 1 .708.708l-3 3a.5.5 0 0 1-.708 0l-3-3a.5.5 0 0 1 .708-.708L7.5 12.293V6.5A.5.5 0 0 1 8 6z\"/></svg></a>\n"
"\n"
"\n"
"\n"
"<a target=\"_blank\" href=\"https://id1o1.github.io/rhs\"><svg class=\"change-color\"; style=\"width:100px;height:100px;position:fixed;bottom:10%;left:1em;opacity:.8;\" viewBox=\"0 0 24 24\"><path fill-rule=\"evenodd\" d=\"M14.763.075A.5.5 0 0 1 15 .5v15a.5.5 0 0 1-.5.5h-3a.5.5 0 0 1-.5-.5V14h-1v1.5a.5.5 0 0 1-.5.5h-9a.5.5 0 0 1-.5-.5V10a.5.5 0 0 1 .342-.474L6 7.64V4.5a.5.5 0 0 1 .276-.447l8-4a.5.5 0 0 1 .487.022zM6 8.694 1 10.36V15h5V8.694zM7 15h2v-1.5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5V15h2V1.309l-7 3.5V15z\"/>\n"
"  <path d=\"M2 11h1v1H2v-1zm2 0h1v1H4v-1zm-2 2h1v1H2v-1zm2 0h1v1H4v-1zm4-4h1v1H8V9zm2 0h1v1h-1V9zm-2 2h1v1H8v-1zm2 0h1v1h-1v-1zm2-2h1v1h-1V9zm0 2h1v1h-1v-1zM8 7h1v1H8V7zm2 0h1v1h-1V7zm2 0h1v1h-1V7zM8 5h1v1H8V5zm2 0h1v1h-1V5zm2 0h1v1h-1V5zm0-2h1v1h-1V3z\"/></svg></a>\n"
"   </body>\n"
"</html>"};


/*
void handleRoot() 
{
  char temp[400];

  snprintf(temp, 400,
    "<html>\
  <head>\
  </head>\
    <body>\
    <h1>How to html page really good</h1>\
    <a href =\"/on\"> <button> Turn ON</button> </a>\
    <a href =\"/off\"> <button> Turn OFF</button> </a>\
  </body>\
</html>");
  server.send(200, "text/html", temp);
//  server.send(200, "text/plain", "I'm an awasome webServer!!!");

}
*/
// on bord led blinking code
void blinkLed()
{
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(10);
  digitalWrite(16, HIGH);
  delay(10);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(20);
  digitalWrite(16, HIGH);
  delay(20);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(30);
  digitalWrite(16, HIGH);
  delay(30);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(40);
  digitalWrite(16, HIGH);
  delay(40);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(50);
  digitalWrite(16, HIGH);
  delay(50);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(60);
  digitalWrite(16, HIGH);
  delay(60);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(70);
  digitalWrite(16, HIGH);
  delay(70);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(80);
  digitalWrite(16, HIGH);
  delay(80);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(90);
  digitalWrite(16, HIGH);
  delay(90);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(100);
  digitalWrite(16, HIGH);
  delay(100);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(200);
  digitalWrite(16, HIGH);
  delay(200);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(300);
  digitalWrite(16, HIGH);
  delay(300);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(400);
  digitalWrite(16, HIGH);
  delay(400);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(500);
  digitalWrite(16, HIGH);
  delay(500);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(600);
  digitalWrite(16, HIGH);
  delay(600);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(700);
  digitalWrite(16, HIGH);
  delay(700);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(800);
  digitalWrite(16, HIGH);
  delay(800);


  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(900);
  digitalWrite(16, HIGH);
  delay(900);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(1000);
  digitalWrite(16, HIGH);
  delay(200);

  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(200);
  digitalWrite(16, HIGH);
  delay(100);
};



// fanction to inite root 
void handleRoot() 
{
  server.send(200, "text/html", temp);
//  server.send(200, "text/plain", "I'm an awasome webServer!!!");

}



//debug function
void deBug()
{
  server.send(200, "text/html", debugTxt);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Going In to");
  lcd.setCursor(0,4);
  lcd.print("Debug MODE....");
  delay(1500);
  pinMode(13, OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Turning ON Light");
  delay(1000);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Doing System ");
  lcd.setCursor(0,4);
  lcd.print("Checkup..");
  delay(200);
  blinkLed();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Doing System ");
  lcd.setCursor(0,4);
  lcd.print("Checkup....");
  delay(200);
  blinkLed();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Doing System ");
  lcd.setCursor(0,4);
  lcd.print("Checkup......");
  lcd.setBacklight(0);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(100);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(100);
  delay(200);
  blinkLed();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Doing System ");
  lcd.setCursor(0,4);
  lcd.print("Checkup........");
  lcd.setBacklight(1);
   pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(100);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(100);
  delay(200);
  blinkLed();
  pinMode(13, OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Turning OFF");
  lcd.setCursor(0,4);
  lcd.print("Light (-_-)");
  delay(1000);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("No Problem Found");
  lcd.setCursor(0,4);
  lcd.print("Shourav...");
  delay(2000);
  
  
} ;




//back to function let's you move back to root after dowing some work
void backTo()
{
  char temp[400];

  snprintf(temp, 400,
    """<!DOCTYPE html>"
    "<html>"
    "<head>"
        "<meta http-equiv = 'refresh' content = '0; url =/' />"
   " </head>"
    "<body>"
   "</body>"
  "</html>""");
  server.send(200, "text/html", temp);
}

 


//control display's backlight and send signal to nano
void bkLight() {
  //server.send(200, "text/html", temp);
   pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(100);
  digitalWrite(12, LOW);
  Serial.println(bklightvar);
  bklightvar =! bklightvar;
  Serial.println(bklightvar);
  delay(500);
  digitalWrite(16, HIGH);
  backTo();
}



//send signal to nano for controling light 
void lightMode() {
  //server.send(200, "text/html", temp);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(16, HIGH);
  backTo();
  
}


//main setup
void setup(void) {


  
  // Serial port for debugging purposes
  Serial.begin(115200);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selected SSID....");
  lcd.setCursor(0,4);
  lcd.print(ssid);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(0,4);
  lcd.print("Shourav");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);

  Serial.begin(115200);
  Serial.print("Connecting to network");
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);   // Connect to WiFi network

  while (WiFi.status() != WL_CONNECTED) {    // Wait for connection
    delay(500);
    Serial.print(".");
    Serial.println("Connecting to WiFi..");
    lcd.print("Connecting ");
    lcd.setCursor(0,4);
    lcd.print("To WiFi....");
    delay(1000);
    lcd.clear();
  }

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0,0);
  lcd.print("YOUR IP ADDRESS-");
  lcd.setCursor(0,4);
  lcd.print(WiFi.localIP());

  
  // handleing server request
  server.on("/", handleRoot);
  server.on("/light", lightMode);
  server.on("/bklight", bkLight);
  server.on("/test", deBug);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{

  // doing Main loop
  server.handleClient();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("YOUR IP ADDRESS-");
  lcd.setCursor(0,4);
  lcd.print(WiFi.localIP());
  delay(100);


  //backlight logic
  if ( bklightvar == LOW ){
      lcd.setBacklight(0);
  }
  else {
    lcd.setBacklight(1);
  }
}