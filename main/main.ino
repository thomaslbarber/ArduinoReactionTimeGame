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
#define R_LED_PIN 6
#define G_LED_PIN 4
#define B_LED_PIN 5

// The display.
LiquidCrystal lcd(BS_PIN, E_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

bool startFinished = false;

// Colours.
// RGB values when performing a rainbow() effect.
int r = 254;
int g = 1;
int b = 127;

// The direction of each colour in the rainbow() effect.
int r_dir = -1;
int g_dir = 1;
int b_dir = -1;


// Called at the initialisation phase.
void setup() {
  lcd.begin(16, 2);
  
  pinMode(2, INPUT_PULLUP);

  pinMode(R_LED_PIN, OUTPUT);
  pinMode(G_LED_PIN, OUTPUT);
  pinMode(B_LED_PIN, OUTPUT);
}

// Loops repeatedly.
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
    rainbow();
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
  setColor(255, 0, 0);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready...");
}

// Displays a go message to the display, signalling the user to press the button.
void goState() {
  setColor(0, 255, 0);
  
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

    rainbow();
  }
}

// Converts milliseconds to seconds.
float second() {
  return millis() * 0.001;
}

// Produces a rainbow effect for the LED.
void rainbow() {
  // Changing values of LEDs
  r = r + r_dir;   
  g = g + g_dir;
  b = b + b_dir;
  
  // Changes direction for each colour if it reaches the threshold.
  if (r >= 255 || r <= 0)
  {
    r_dir = r_dir * -1;
  }
  if (g >= 255 || g <= 0)
  {
    g_dir = g_dir * -1;
  }
  if (b >= 255 || b <= 0)
  {
    b_dir = b_dir * -1;
  }
  
  setColor(r, g, b);

  // Delay to allow the colours to be seen.
  delay(5);
}

void setColor(int r, int g, int b) {
  analogWrite(R_LED_PIN,   r);
  analogWrite(G_LED_PIN, g);
  analogWrite(B_LED_PIN,  b);
}
