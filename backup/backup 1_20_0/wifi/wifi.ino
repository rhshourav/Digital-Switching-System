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
int bklightvar = 0 ;


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
const char temp[] PROGMEM={"\n"
"<!DOCTYPE html>\n"
"<html>\n"
"   <head>\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"      <style>\n"
"@import url('https://fonts.googleapis.com/css?family=Source+Code+Pro:200,900');\n"
"@import url('https://fonts.googleapis.com/css2?family=Cookie&display=swap');\n"
"\n"
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
"  height: 100%;\n"
"  background: radial-gradient(ellipse at bottom, #293355 0%, #0f0909 100%);\n"
"  overflow: hidden;\n"
"  width: 100%;\n"
"  display: flex;\n"
"  align-items: center;\n"
"  justify-content: center;\n"
"  background-color: var(--bg-color);\n"
"  margin: 0px;\n"
"  padding: 0px;\n"
"  font-family: 'Cookie', cursive;\n"
"  background-color: #fdfdfe;\n"
"}\n"
"\n"
"\n"
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
"\n"
"*{\n"
"  box-sizing: border-box;\n"
"}\n"
"header {\n"
"  width: 10p;\n"
"}\n"
"header h1 {\n"
"  position: fixed;\n"
"  top: 0%;\n"
"  left: 50%;\n"
"  right: 50%;\n"
"  width: 40%;\n"
"  font-size: 30px;\n"
"  font-weight: 500;\n"
"  color: transparent;\n"
"  -webkit-background-clip: text;\n"
"  background-clip: text;   \n"
"}\n"
"header .header-1{\n"
"  background-image: repeating-radial-gradient(farthest-side at 5px 5px,#553c9a, #ee4b2b, #553c9a);\n"
"}\n"
"header .header-2{\n"
"  background-image: repeating-radial-gradient(farthest-corner at 20px 40px,#553c9a, #ee4b2b, #553c9a);\n"
"}\n"
"header .header-3{\n"
"  background-image: repeating-radial-gradient(circle farthest-side at 5px 10px,#553c9a 10%, #ee4b2b 30%, #553c9a);\n"
"}\n"
"</style>\n"
" \n"
"   <body>\n"
"     \n"
"    <header>\n"
"      <h1 class=\"header-1\"> Home Solution <br> Welcome Shourav.!</h1>\n"
"    </header>\n"
"\n"
"\n"
"\n"
"      <a href=\"/light\"><button style=\"--content: 'LIGHT !';></a>\n"
"  <div class=\"left\" ></div>\n"
"    LIGHT !\n"
"  <div class=\"right\"></div>\n"
"</button>\n"
"\n"
"<a href=\"/bklight\">\n"
"  <svg class=\"change-color\" style=\"width:100px;height:100px;position:fixed;top:5%;left:1em;opacity:.8;\" ersion=\"1.1\" viewBox=\"0 0 700 700\" xmlns=\"http://www.w3.org/2000/svg\">\n"
"    <g>\n"
"     <path d=\"m186.67 268.33c0 40.227 15.977 78.805 44.422 107.25 28.441 28.441 67.02 44.422 107.24 44.422 40.227 0 78.805-15.98 107.25-44.422s44.422-67.02 44.422-107.25c0-40.223-15.98-78.801-44.422-107.24-28.441-28.445-67.02-44.422-107.25-44.422-40.207 0.046875-78.758 16.039-107.19 44.473s-44.426 66.984-44.473 107.19zm280 0c-0.050781 31.996-12.035 62.824-33.613 86.449-21.578 23.629-51.195 38.352-83.055 41.293v-255.48c31.859 2.9453 61.477 17.668 83.055 41.293 21.578 23.629 33.562 54.453 33.613 86.449zm-140-127.74v255.48c-42.895-3.8945-80.969-29.055-101.37-66.988-20.402-37.934-20.402-83.57 0-121.5 20.398-37.934 58.473-63.094 101.37-66.992z\"/>\n"
"     <path d=\"m350 81.668v-46.668c0-6.4414-5.2227-11.668-11.668-11.668-6.4414 0-11.664 5.2266-11.664 11.668v46.668c0 6.4414 5.2227 11.664 11.664 11.664 6.4453 0 11.668-5.2227 11.668-11.664z\"/>\n"
"     <path d=\"m326.67 455v46.668c0 6.4414 5.2227 11.664 11.664 11.664 6.4453 0 11.668-5.2227 11.668-11.664v-46.668c0-6.4414-5.2227-11.668-11.668-11.668-6.4414 0-11.664 5.2266-11.664 11.668z\"/>\n"
"     <path d=\"m571.67 256.67h-46.668c-6.4414 0-11.668 5.2227-11.668 11.664 0 6.4453 5.2266 11.668 11.668 11.668h46.668c6.4414 0 11.664-5.2227 11.664-11.668 0-6.4414-5.2227-11.664-11.664-11.664z\"/>\n"
"     <path d=\"m163.33 268.33c0.003907-3.0938-1.2266-6.0625-3.4141-8.25s-5.1562-3.418-8.25-3.4141h-46.668c-6.4414 0-11.668 5.2227-11.668 11.664 0 6.4453 5.2266 11.668 11.668 11.668h46.668c3.0938 0 6.0625-1.2266 8.25-3.4141s3.418-5.1562 3.4141-8.2539z\"/>\n"
"     <path d=\"m165.09 95.09c-2.1914 2.1836-3.418 5.1523-3.418 8.2461s1.2266 6.0625 3.418 8.25l33.004 32.996c2.1836 2.2031 5.1562 3.4492 8.2617 3.457 3.1016 0.007813 6.082-1.2227 8.2773-3.418 2.1953-2.1953 3.4219-5.1758 3.4141-8.2812-0.011719-3.1016-1.2578-6.0742-3.4648-8.2578l-32.996-32.992c-2.1875-2.1914-5.1562-3.4219-8.25-3.4219s-6.0625 1.2305-8.2461 3.4219z\"/>\n"
"     <path d=\"m478.58 392.09c-2.1797-2.2227-5.1562-3.4844-8.2695-3.5-3.1172-0.015626-6.1055 1.2148-8.3086 3.418-2.2031 2.1992-3.4336 5.1914-3.418 8.3047 0.015624 3.1172 1.2773 6.0938 3.5 8.2734l32.996 32.996c2.1797 2.2227 5.1602 3.4844 8.2734 3.5s6.1055-1.2148 8.3086-3.418c2.1992-2.1992 3.4297-5.1914 3.4141-8.3047-0.015625-3.1172-1.2734-6.0938-3.5-8.2734z\"/>\n"
"     <path d=\"m511.58 95.09c-2.1875-2.1914-5.1523-3.418-8.2461-3.418s-6.0625 1.2266-8.25 3.418l-32.996 32.992c-2.2227 2.1797-3.4844 5.1602-3.5 8.2734-0.015626 3.1133 1.2148 6.1055 3.418 8.3086 2.1992 2.2031 5.1914 3.4297 8.3047 3.4141 3.1172-0.015625 6.0938-1.2734 8.2734-3.5l32.996-32.992c2.1875-2.1875 3.418-5.1562 3.418-8.25s-1.2305-6.0625-3.418-8.2461z\"/>\n"
"     <path d=\"m165.09 441.58c2.1836 2.1875 5.1523 3.418 8.2461 3.418s6.0625-1.2305 8.25-3.418l32.996-32.996h-0.003906c2.2109-2.1797 3.457-5.1523 3.4648-8.2578 0.011719-3.1016-1.2148-6.082-3.4102-8.2773-2.1953-2.1953-5.1758-3.4258-8.2773-3.418-3.1055 0.007813-6.0781 1.25-8.2617 3.457l-33.004 32.996c-2.1914 2.1875-3.4219 5.1523-3.4219 8.2461 0 3.0977 1.2305 6.0625 3.4219 8.25z\"/>\n"
"    </g>\n"
"   </svg>\n"
"</a>\n"
"\n"
"<a href=\"/fan\"><svg class=\"change-color\" style=\"width:100px;height:100px;position:fixed;bottom:35%;right:38%;opacity:.8;\"  x=\"0px\" y=\"0px\" viewBox=\"0 0 122.88 66.29\" style=\"enable-background:new 0 0 122.88 66.29\" xml:space=\"preserve\"><g><path d=\"M45.39,41.96c0.02-0.3,0.06-0.6,0.12-0.9c0.1-0.46,0.25-0.91,0.45-1.36c0.21-0.47,0.48-0.92,0.81-1.36 c0.22-0.3,0.47-0.59,0.75-0.88c-7.09-3.64-24.28-11.3-29.76-15.29c-0.69-0.46-1.37-0.84-2.06-1.14c-0.69-0.3-1.39-0.52-2.08-0.65 c-0.69-0.13-1.37-0.18-2.06-0.16c-0.69,0.03-1.39,0.14-2.09,0.32c-0.76,0.2-1.58,0.54-2.38,0.97c-0.77,0.42-1.53,0.93-2.21,1.51 c-0.6,0.52-1.14,1.09-1.56,1.69c-0.38,0.55-0.67,1.12-0.83,1.71c-0.11,0.4-0.13,0.78-0.05,1.16c0.08,0.38,0.25,0.75,0.52,1.12 c0.32,0.43,0.78,0.86,1.38,1.29c0.6,0.43,1.35,0.85,2.25,1.26L45.39,41.96L45.39,41.96z M112.49,34.39l-18.78,5.17 C100.37,37.91,107.2,36.13,112.49,34.39L112.49,34.39z M28.91,39.49l-18.13-5C16.03,36.2,22.53,37.89,28.91,39.49L28.91,39.49z M59.75,0h3.69c0.21,0,0.37,0.17,0.37,0.37v23.81c0.47,0.12,0.93,0.29,1.39,0.5c0.53,0.25,1.06,0.56,1.57,0.95 c0.35,0.26,0.68,0.55,1,0.87c0.32,0.31,0.63,0.66,0.92,1.02c0.41,0.52,0.78,1.1,1.1,1.74c0.32,0.64,0.59,1.34,0.81,2.12 c0.19,0.67,0.34,1.39,0.44,2.17c0.09,0.69,0.15,1.42,0.18,2.2c0.25,0.04,0.49,0.09,0.73,0.15c0.28,0.06,0.55,0.14,0.82,0.22 l31.06-15.94c0.82-0.55,1.64-1,2.47-1.35c0.84-0.36,1.68-0.62,2.53-0.78c0.86-0.17,1.73-0.23,2.6-0.2c0.87,0.03,1.74,0.17,2.62,0.4 c0.93,0.25,1.92,0.65,2.88,1.17c0.93,0.5,1.83,1.11,2.64,1.81c0.77,0.66,1.46,1.4,2.01,2.2c0.51,0.75,0.91,1.55,1.13,2.39 c0.2,0.76,0.24,1.5,0.1,2.22l0,0.02c-0.14,0.72-0.46,1.41-0.96,2.08c-0.45,0.6-1.06,1.19-1.84,1.75c-0.76,0.55-1.69,1.07-2.78,1.58 c-8.78,3.74-29.55,8.16-39.87,11c-0.19,0.59-0.46,1.19-0.79,1.79c-0.36,0.65-0.81,1.32-1.35,1.98c-0.43,0.53-0.89,1-1.4,1.43 c-0.5,0.43-1.05,0.81-1.62,1.15c-0.43,0.25-0.88,0.49-1.36,0.7c-0.37,0.16-0.75,0.31-1.13,0.45l0.79,3.35 c0.1,0.41,0.23,0.96,0.36,1.64c0.13,0.66,0.26,1.39,0.35,2.1c0.09,0.79,0.14,1.58,0.08,2.31c-0.05,0.75-0.21,1.43-0.52,1.96 c-0.1,0.17-0.22,0.34-0.34,0.49c-0.13,0.15-0.27,0.29-0.42,0.41l-0.08,0.06c-0.14,0.11-0.29,0.21-0.44,0.29 c-0.17,0.09-0.34,0.17-0.53,0.24l-0.05,0.02c-0.99,0.39-1.99,0.7-3.01,0.94c-1.02,0.24-2.05,0.39-3.09,0.46 c-1.05,0.07-2.11,0.05-3.19-0.05c-1.07-0.11-2.16-0.31-3.25-0.6l-0.39-0.1c-0.79-0.21-1.58-0.41-2.27-0.81 c-0.73-0.42-1.33-1.03-1.69-2.04c-0.35-0.98-0.17-3.1,0.18-5.32c0.32-2.04,0.77-4.15,1.07-5.53c-0.31-0.13-0.62-0.26-0.91-0.4 c-0.37-0.18-0.75-0.37-1.12-0.59c-0.48-0.28-0.93-0.57-1.36-0.89c-0.43-0.32-0.83-0.65-1.21-1.01c-0.15-0.14-0.3-0.3-0.45-0.45 c-0.15-0.15-0.28-0.31-0.42-0.46c-0.14-0.16-0.27-0.32-0.4-0.49l-0.02-0.02c-0.13-0.17-0.25-0.33-0.35-0.49 c-0.27-0.4-0.51-0.81-0.71-1.22c-0.21-0.41-0.37-0.82-0.51-1.23l0-0.01c-9.41-2.59-32.67-7.67-40.15-11.08 c-1.1-0.5-2.02-1.03-2.78-1.58c-0.78-0.56-1.39-1.14-1.84-1.75c-0.5-0.68-0.82-1.38-0.96-2.1c-0.14-0.72-0.1-1.47,0.1-2.22 c0.23-0.84,0.62-1.64,1.13-2.39c0.55-0.8,1.24-1.54,2.01-2.2c0.81-0.7,1.72-1.31,2.64-1.81c0.96-0.52,1.95-0.92,2.88-1.17 c0.87-0.23,1.75-0.37,2.62-0.4c0.87-0.03,1.74,0.03,2.6,0.2c0.85,0.16,1.69,0.42,2.53,0.78c0.83,0.35,1.65,0.8,2.47,1.35 l31.08,15.95c0.06,0.03,0.11,0.06,0.16,0.09l0.39-0.13c0.23-0.07,0.47-0.14,0.73-0.2c0.17-0.04,0.35-0.08,0.54-0.12 c0.01-0.55,0.05-1.09,0.1-1.62c0.07-0.63,0.17-1.25,0.31-1.84c0.17-0.74,0.41-1.45,0.71-2.13c0.31-0.69,0.69-1.34,1.15-1.95 l0.02-0.02c0.32-0.43,0.66-0.83,1.01-1.19c0.36-0.38,0.74-0.72,1.13-1.03c0.51-0.4,1.03-0.75,1.58-1.04 c0.46-0.24,0.93-0.44,1.41-0.6V0.37C59.37,0.17,59.54,0,59.75,0L59.75,0z M56.41,50.32c0.85,0.2,1.69,0.34,2.54,0.43 c0.85,0.09,1.69,0.13,2.53,0.12c1.08-0.01,2.16-0.1,3.25-0.25c1.08-0.15,2.17-0.37,3.26-0.64c0.07-0.02,0.14-0.03,0.22-0.03 c0.5-0.15,0.98-0.32,1.43-0.51c0.46-0.2,0.91-0.42,1.33-0.67c0.46-0.27,0.89-0.57,1.28-0.91c0.4-0.34,0.77-0.71,1.1-1.12 c0.46-0.56,0.83-1.12,1.13-1.65c0.29-0.52,0.51-1.03,0.65-1.52c0-0.06,0-0.11,0-0.17c0.01-0.07,0.02-0.15,0.04-0.21 c0.02-0.1,0.06-0.2,0.09-0.3l0.06-0.23c0.02-0.14,0.02-0.26,0.03-0.38c0.01-0.29-0.02-0.57-0.07-0.84 c-0.05-0.26-0.13-0.52-0.24-0.76c-0.11-0.24-0.25-0.47-0.42-0.68c-0.17-0.22-0.37-0.42-0.6-0.6c-0.54-0.44-1.24-0.79-2.09-1.05 c-0.84-0.25-1.81-0.4-2.92-0.43l-0.09,0c-1.53-0.1-3.7-0.22-6.02-0.27c-1.7-0.04-3.49-0.06-5.18-0.01c-0.5,0.01-1,0.03-1.49,0.06 c-0.44,0.02-0.89,0.05-1.33,0.09l-0.77,0.11l-0.78,0.12c-0.08,0.01-0.17,0.02-0.25,0.02c-0.06,0-0.11-0.01-0.17-0.02 c-0.28,0.05-0.54,0.09-0.78,0.15c-0.25,0.06-0.49,0.12-0.71,0.19c-0.35,0.11-0.67,0.24-0.97,0.38c-0.3,0.14-0.57,0.3-0.83,0.47 l-0.03,0.02c-0.4,0.27-0.73,0.58-0.99,0.91c-0.27,0.34-0.47,0.7-0.59,1.09c-0.1,0.31-0.16,0.64-0.17,0.98 c-0.01,0.34,0.02,0.7,0.1,1.07l0.07,0.27l0.08,0.28c0.1,0.3,0.23,0.61,0.38,0.92c0.15,0.31,0.34,0.62,0.55,0.94 c0.1,0.15,0.2,0.29,0.29,0.41c0.1,0.13,0.21,0.26,0.31,0.39c0.11,0.13,0.22,0.25,0.33,0.37c0.11,0.12,0.23,0.24,0.35,0.35 c0.31,0.29,0.64,0.57,0.98,0.83c0.36,0.26,0.73,0.51,1.12,0.73c0.4,0.23,0.83,0.45,1.27,0.64c0.45,0.2,0.91,0.38,1.39,0.55 c0.21,0.07,0.43,0.13,0.67,0.2C55.96,50.21,56.19,50.27,56.41,50.32L56.41,50.32z M61.55,34.95c1.29,0,2.57,0.04,3.85,0.12 c1.13,0.07,2.27,0.18,3.42,0.32c-0.03-0.57-0.08-1.1-0.16-1.61c-0.09-0.63-0.21-1.21-0.36-1.75c-0.17-0.62-0.39-1.18-0.64-1.68 c-0.25-0.5-0.53-0.94-0.84-1.34c-0.23-0.29-0.47-0.56-0.72-0.81l-0.02-0.02c-0.24-0.24-0.49-0.45-0.74-0.64 c-0.58-0.43-1.18-0.75-1.8-0.95c-0.63-0.2-1.28-0.29-1.92-0.25c-0.64,0.03-1.28,0.18-1.91,0.43c-0.63,0.26-1.25,0.62-1.85,1.09 c-0.31,0.25-0.62,0.52-0.91,0.82c-0.29,0.3-0.57,0.63-0.83,0.97c-0.35,0.47-0.65,0.97-0.88,1.51c-0.24,0.53-0.42,1.1-0.56,1.69 c-0.11,0.47-0.19,0.96-0.25,1.46c-0.04,0.37-0.07,0.75-0.09,1.13l0.23-0.02c1.16-0.16,2.32-0.27,3.48-0.35 C59.2,34.99,60.37,34.95,61.55,34.95L61.55,34.95z M77.19,39.47c0.23,0.45,0.39,0.92,0.49,1.4c0.06,0.33,0.1,0.66,0.1,1 l38.53-10.62c0.89-0.41,1.64-0.83,2.24-1.26c0.59-0.42,1.05-0.85,1.37-1.28c0.28-0.37,0.45-0.74,0.52-1.12 c0.08-0.38,0.06-0.76-0.05-1.16c-0.16-0.59-0.45-1.16-0.83-1.71c-0.42-0.6-0.96-1.17-1.56-1.69c-0.68-0.58-1.44-1.1-2.21-1.51 c-0.8-0.43-1.62-0.76-2.38-0.97c-0.7-0.19-1.4-0.3-2.09-0.32c-0.69-0.03-1.38,0.02-2.06,0.16c-0.69,0.13-1.39,0.35-2.08,0.65 c-0.7,0.3-1.4,0.69-2.09,1.15c-8.84,5.24-20.24,10.39-29.58,15.19c0.29,0.25,0.55,0.51,0.79,0.78c0.36,0.41,0.65,0.84,0.88,1.29 L77.19,39.47L77.19,39.47z M67.4,52.61c-1.05,0.24-2.08,0.42-3.08,0.53c-1.12,0.13-2.21,0.18-3.28,0.16 c-0.87-0.02-1.72-0.08-2.56-0.18c-0.83-0.11-1.65-0.26-2.45-0.45l-0.49-0.12c-0.29,1.35-0.7,3.27-0.99,5.04 c-0.32,1.91-0.51,3.64-0.29,4.24c0.14,0.4,0.45,0.67,0.83,0.86c0.43,0.22,0.97,0.36,1.51,0.5c0.13,0.04,0.26,0.06,0.39,0.1 c0.97,0.26,1.93,0.43,2.87,0.53c0.94,0.09,1.88,0.11,2.8,0.05c0.91-0.06,1.82-0.2,2.72-0.4c0.9-0.21,1.79-0.49,2.67-0.83l0.08-0.03 c0.07-0.02,0.13-0.05,0.19-0.08l0.02-0.01c0.05-0.03,0.09-0.05,0.13-0.08l0.03-0.03c0.04-0.03,0.08-0.07,0.12-0.12 c0.04-0.04,0.07-0.09,0.1-0.14c0.14-0.24,0.2-0.63,0.22-1.1c0.02-0.5-0.02-1.1-0.09-1.7c-0.08-0.67-0.2-1.34-0.32-1.94 c-0.12-0.57-0.25-1.13-0.34-1.55L67.4,52.61L67.4,52.61z\"/></g></svg></a>\n"
"\n"
"<a target=\"_blank\" href=\"https://id1o1.github.io/rhs\"><svg class=\"change-color\"; style=\"width:100px;height:100px;position:fixed;bottom:10%;left:1em;opacity:.8;\" viewBox=\"0 0 24 24\"><path fill-rule=\"evenodd\" d=\"M14.763.075A.5.5 0 0 1 15 .5v15a.5.5 0 0 1-.5.5h-3a.5.5 0 0 1-.5-.5V14h-1v1.5a.5.5 0 0 1-.5.5h-9a.5.5 0 0 1-.5-.5V10a.5.5 0 0 1 .342-.474L6 7.64V4.5a.5.5 0 0 1 .276-.447l8-4a.5.5 0 0 1 .487.022zM6 8.694 1 10.36V15h5V8.694zM7 15h2v-1.5a.5.5 0 0 1 .5-.5h2a.5.5 0 0 1 .5.5V15h2V1.309l-7 3.5V15z\"/>\n"
"  <path d=\"M2 11h1v1H2v-1zm2 0h1v1H4v-1zm-2 2h1v1H2v-1zm2 0h1v1H4v-1zm4-4h1v1H8V9zm2 0h1v1h-1V9zm-2 2h1v1H8v-1zm2 0h1v1h-1v-1zm2-2h1v1h-1V9zm0 2h1v1h-1v-1zM8 7h1v1H8V7zm2 0h1v1h-1V7zm2 0h1v1h-1V7zM8 5h1v1H8V5zm2 0h1v1h-1V5zm2 0h1v1h-1V5zm0-2h1v1h-1V3z\"/></svg></a>\n"
"\n"
"\n"
"  \n"
"   </body>\n"
"</html>\n"
""};


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

//Send Signal to nano for controling Fan
void fanMode() {
  //server.send(200, "text/html", temp);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  pinMode(14, OUTPUT);
  digitalWrite(14, HIGH);
  delay(100);
  digitalWrite(14, LOW);
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
  server.on("/fan", fanMode);

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
