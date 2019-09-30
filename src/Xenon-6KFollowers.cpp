/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/Users/rueloquindo/Projects/LearnParticle/Argon-6KFollowers/Xenon-6KFollowers/src/Xenon-6KFollowers.ino"
/*
 * Project Xenon-6KFollowers
 * Description: Watch for mesh messages, and display to OLED screen
 * Author: @owel.codes 
 * Date: Sept 30, 2019
 */

// #include "Arduino.h" // this declares that our app/library wants the extended Arduino support
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
void myHandler(const char *event, const char *data);
void DisplayFollowers(const char *data);
void setup();
void loop();
#line 12 "/Users/rueloquindo/Projects/LearnParticle/Argon-6KFollowers/Xenon-6KFollowers/src/Xenon-6KFollowers.ino"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_SDA D0
#define OLED_SCL D1
#define OLED_RESET -1
#define OLED_ADDR 0x3C
// Declaration for SSD1306 display connected using I2C, address of 0x3C
Adafruit_SSD1306 display(OLED_RESET);

const char * followers;
char buffer[10];
int mutex = 0;

void myHandler(const char *event, const char *data)
{
  Serial.printlnf("event=%s data=%s", event, data ? data : "NULL");
  followers = data;
}

void DisplayFollowers(const char *data){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,10);
  display.println(F("Owel.codes"));
  display.setCursor(0,28);
  display.println(F("followers"));
  display.setCursor(0,48);
  display.println(F(data));  
  display.display();
}


// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  Serial.println("This is Xenon device...");

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); // OLED_ADDR 0x3C
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,10);
  display.println(F("Mesh"));
  display.setCursor(0,35);
  display.println(F("Network"));
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();

  // display IG text
  display.setTextSize(2);
  display.setCursor(0,10);
  display.println(F("Owel.codes"));
  display.setCursor(0,28);
  display.println(F("followers"));
  display.setCursor(0,50);
  display.println(F("6000"));  
  display.display();

  // setup event listender and check if an event occured
  Mesh.subscribe("igfollowers", myHandler);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  yield();
  DisplayFollowers(followers);
}