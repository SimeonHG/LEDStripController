#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Adafruit_NeoPixel.h>
#define LED_PIN   4

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 120

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#ifndef STASSID
#define STASSID "simko"
#define STAPSK  "asdfnetasdf"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
bool flag = 0;

bool cont = false;
ESP8266WebServer server(80);

const int led = 13;

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


void breathe(byte red, byte green, byte blue, int wait){
  float r, g, b;
  cont = true;
  
  while(true){  
    flag = 0;
    for(int k = 0; k < 256; k=k+1) {
      r = (k/256.0)*red;
      g = (k/256.0)*green;
      b = (k/256.0)*blue;
      strip.fill(strip.Color(r,   g,   b));      
      strip.show(); 
      delay(wait);   
      server.handleClient();
      if(!cont){
        return;
      }      
    }
    
       
    for(int k = 255; k >= 0; k=k-2) {
      r = (k/256.0)*red;
      g = (k/256.0)*green;
      b = (k/256.0)*blue;
      strip.fill(strip.Color(r,   g,   b));      
      strip.show(); 
      delay(wait); 
      
      server.handleClient();
      if(!cont){
        return;
      }           
    }
    
    

  }
  cont = false;
  
}



void meteor(uint32_t color, int mSize, int mDecay, int wait) {
  cont = true;
  for(int i = 0; i < strip.numPixels()*2; i++) {
    for(int j=0; j < strip.numPixels(); j++){
      if(random(10)>5){
        fadeToBlack(i, mDecay);
      }
    }
    for(int j=0; j < strip.numPixels(); j++){
      if( ( i-j < strip.numPixels()) && (i-j>=0) ) {
           strip.setPixelColor(i-j, color);
        }
      
    }
    strip.show();
    delay(wait);
    
    server.handleClient();
    if(!cont){
      break;
    }
  }
  cont = false;
  
}


void fadeToBlack(int ledNo, int fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}



void CylonBounce(int red, int green, int blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  cont = true;
  while(true){  
    for(int i = 0; i < strip.numPixels()-EyeSize-2; i++) {
      strip.fill(); 
        strip.setPixelColor(i, strip.Color(red/10, green/10, blue/10));
      for(int j = 1; j <= EyeSize; j++) {
        strip.setPixelColor(i+j, strip.Color(red, green, blue));
      }
      strip.setPixelColor(i+EyeSize+1, red/10, green/10, blue/10);
      strip.show();
      delay(SpeedDelay);

      server.handleClient();
      if(!cont){
        return;
      } 
    }
   
    delay(ReturnDelay);
  
    for(int i = strip.numPixels()-EyeSize-2; i > 0; i--) {
      strip.fill(); ;
       strip.setPixelColor(i, strip.Color(red/10, green/10, blue/10));
      for(int j = 1; j <= EyeSize; j++) {
         strip.setPixelColor(i+j, red, green, blue);
      }
       strip.setPixelColor(i+EyeSize+1, strip.Color(red/10, green/10, blue/10));
      strip.show();
      delay(SpeedDelay);

      server.handleClient();
      if(!cont){
        return;
      } 
    }
    
   
    delay(ReturnDelay);
  }
  cont = false;
}


void TwinkleRandom(int SpeedDelay) {
  strip.fill();
  cont = true; 
  for (int i=0; i<strip.numPixels()/2; i++) {
    
    for (int i=0; i<strip.numPixels(); i++) {
       strip.setPixelColor(random(strip.numPixels()), strip.Color(random(0,255),random(0,255),random(0,255)));
       strip.show();
       delay(SpeedDelay);
  
  
       server.handleClient();
       if(!cont){
         break;
       }
  
     }
   
    delay(SpeedDelay);
    cont = false;
  }
}


void Sparkle(int red, int green, int blue, int SpeedDelay) {
   cont = true;
   for (int i=0; i<strip.numPixels()/2; i++) {
      int Pixel = random(strip.numPixels());
      strip.setPixelColor(Pixel,strip.Color(red,green,blue));
      strip.show();
      delay(SpeedDelay);
      strip.setPixelColor(Pixel,strip.Color(0,0,0));


      server.handleClient();
      if(!cont){
        break;
      }
   }
   cont = false;
}




void rainbow(int wait) {
  cont = true;
  while(true){   
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
     
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        
      }
      
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
      server.handleClient();
      if(!cont){
        return;
      }
    }
  }
  server.handleClient();
    if(!cont){
      return;
    }
  cont = false;
}


// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  cont = true;
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
    server.handleClient();
    if(!cont){
      break;
    }
  }
}

void handleRoot() {
  
  server.send(200, "text/plain", "hello from esp8266! working\n /rainbow\n /wipe?r=X&g=X&b=X \n /red \n /blue \n /green");
  
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}



void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/meteor", [](){
    cont = false;
    server.send(200, "text/plain", "meteor");
    //uint32_t color, int mSize, int mDecay, int wait
    meteor(strip.Color(server.arg(0).toInt(),  server.arg(1).toInt(),   server.arg(2).toInt()), 10, 64, 30);
  });

  server.on("/rainbow", []() {
    cont = false;
    server.send(200, "text/plain", "rainbow");
    rainbow(20);
  });

  server.on("/wipe", []() {
    cont = false;
    server.send(200, "text/plain", "wipe");
    colorWipe(strip.Color(server.arg(0).toInt(),  server.arg(1).toInt(),   server.arg(2).toInt()),20);
    
  });

  server.on("/breathe", []() {
    cont = false;
    server.send(200, "text/plain", "breathe");
    breathe(server.arg(0).toInt(),  server.arg(1).toInt(),   server.arg(2).toInt(),2);
    
  });

  server.on("/bounce", []() {
    cont = false;
    server.send(200, "text/plain", "bounce");
//    int red, int green, int blue, int EyeSize, int SpeedDelay, int ReturnDelay
    CylonBounce(server.arg(0).toInt(),  server.arg(1).toInt(),   server.arg(2).toInt(),4, 10, 50);
    
  });
  
  server.on("/twinkle", []() {
    cont = false;
    server.send(200, "text/plain", "twinkle");
    TwinkleRandom(25);
    
  });

  server.on("/sparkle", []() {
    cont = false;
    server.send(200, "text/plain", "sparkle");
    Sparkle(random(255), random(255), random(255), 35);
    
  });

  server.on("/red", []() {
    cont = false;
    server.send(200, "text/plain", "red");
    colorWipe(strip.Color(255,   0,   0),20);
  });
  server.on("/green", []() {
    cont = false;
    server.send(200, "text/plain", "green");
    colorWipe(strip.Color(0,   255,   0),20);
  });

  server.on("/blue", []() {
    cont = false;
    server.send(200, "text/plain", "blue");
    colorWipe(strip.Color(0,   0,   255),20);
  });

  server.on("/clear", []() {
    cont = false;
    strip.fill();    
    strip.show();   
  });


  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  //todo: globalka i edin switch case tuka
}
