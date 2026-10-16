#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//TODO: USE LOPKA.APP FOR BETTER GUI AFTER BUILDING 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  display.clearDisplay();
  display.display();

  playIntro();

  playCyberLoading();

  showBadge();
}

void loop() {
}


// TODO: USE A BETETR ANIMATION LAZY TO ADD NOW
void playIntro() {
  display.clearDisplay();
  
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.drawRect(2, 2, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 4, SSD1306_WHITE);

  // Text: HELLO
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 24);
  display.println(F("HELLO"));

  display.display();
  delay(1500);
}

void playCyberLoading() {
  int progress = 0;
  while(progress <= 100) {
    display.clearDisplay();

    // Cyber header
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(14, 8);
    display.println(F("SYS.INIT // v1.0.4"));

    // Draw loading percentage text
    display.setCursor(38, 22);
    display.print(F("LOAD: "));
    display.print(progress);
    display.print(F("%"));

    display.drawRect(14, 36, 100, 10, SSD1306_WHITE);
    
    int barWidth = map(progress, 0, 100, 0, 96);
    display.fillRect(16, 38, barWidth, 6, SSD1306_WHITE);

    for(int i = 0; i < SCREEN_WIDTH; i += 8) {
      display.drawPixel(i, 56, SSD1306_WHITE);
    }

    display.display();
    
    progress += random(4, 12);
    if(progress > 100) progress = 100;
    delay(80);
  }
  
  delay(400);
}

void showBadge() {
  display.clearDisplay();

  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.drawRect(3, 3, SCREEN_WIDTH - 6, SCREEN_HEIGHT - 6, SSD1306_WHITE);

  display.drawFastHLine(0, 0, 10, SSD1306_WHITE);
  display.drawFastVLine(0, 0, 10, SSD1306_WHITE);
  display.drawFastHLine(SCREEN_WIDTH - 10, 0, 10, SSD1306_WHITE);
  display.drawFastVLine(SCREEN_WIDTH - 1, 0, 10, SSD1306_WHITE);
  display.drawFastHLine(0, SCREEN_HEIGHT - 1, 10, SSD1306_WHITE);
  display.drawFastVLine(0, SCREEN_HEIGHT - 10, 10, SSD1306_WHITE);
  display.drawFastHLine(SCREEN_WIDTH - 10, SCREEN_HEIGHT - 1, 10, SSD1306_WHITE);
  display.drawFastVLine(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 10, 10, SSD1306_WHITE);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(24, 18);
  display.println(F("DevX-Dragon"));

  display.drawFastHLine(20, 32, 88, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(34, 40);
  display.println(F("14 y/o"));

  display.display();
}