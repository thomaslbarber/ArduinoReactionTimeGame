// Includes...
#include "LiquidCrystal.h"

// Pin locations on the arduino board (for the display).
#define BS_PIN 7
#define E_PIN 8
#define D4_PIN 9
#define D5_PIN 10
#define D6_PIN 11
#define D7_PIN 12
#define BTN_PIN 13
#define MIN_DELAY 3000
#define MAX_DELAY 6000


// The display.
LiquidCrystal lcd(BS_PIN, E_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

bool startFinished = false;


void setup() {
  lcd.begin(16, 2);
  
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  startingLoop();

  playGame();
}

void startingLoop() {
  // Print starting message to the LED.
  lcd.setCursor(0, 0);
  lcd.print("Press the button");
  lcd.setCursor(0, 1);
  lcd.print("to begin!");

  // Loop while the user hasn't pressed the button to start.
  while (!startFinished) {
    // Start the game on button press.
    if (digitalRead(BTN_PIN) == 0) {
      lcd.clear();
      startFinished = true;
    }
  }
}

// Provides a full iteration of the game.
void playGame() {
  readyState();
 
  delay(random(MIN_DELAY, MAX_DELAY));

  goState();

  reactionTimeInput();
}

// Displays a ready message to the display.
void readyState() {  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready...");
}

// Displays a go message to the display, signalling the user to press the button.
void goState() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GO!");
}

// Waits for the user to press the button, outputting their reaction time to the display.
void reactionTimeInput() 
{
  bool waiting = true;
  float startTime = second();
  
  while (waiting) {
    if (digitalRead(BTN_PIN) == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      
      float reactionTime = second() - startTime;
      
      lcd.print("Time: ");
      lcd.print(reactionTime,3);
      waiting = false;
    }
  }
  
  delay(3000);

  playAgainInput();
}

// Waits for the user to press the button to play again.
void playAgainInput() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Play again?");
  
  bool playAgain = false;
  
  while (!playAgain) {
    if (digitalRead(BTN_PIN) == 0) {
      lcd.clear();
      return;
    }
  }
}

// Converts milliseconds to seconds.
float second() {
  return millis() * 0.001;
}
