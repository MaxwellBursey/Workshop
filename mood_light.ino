
// ============================================================
//  RGB Mood Light — Arduino Nano
//  The Commons, Memorial University
// ============================================================
//
//  HOW IT WORKS:
//  Press the button to cycle through light "states".
//  Each state is a function that controls how the LED looks.
//
//  LED WIRING (Common Cathode):
//  Cathode (-, longest leg) → GND
//  Red leg   → 220Ω resistor → Pin 9
//  Green leg → 220Ω resistor → Pin 10
//  Blue leg  → 220Ω resistor → Pin 11
//
//  BUTTON WIRING:
//  One leg → Pin 2
//  Other leg → GND
//
// ============================================================


// ── PIN DEFINITIONS ─────────────────────────────────────────

const int RED_PIN    = 9;
const int GREEN_PIN  = 10;
const int BLUE_PIN   = 11;
const int BUTTON_PIN = 2;


// ── STATE TRACKING ──────────────────────────────────────────

int  currentState    = 0;
bool lastButtonState = HIGH;


// ============================================================
//  SETUP — Runs once when the Arduino turns on
// ============================================================

void setup() {
  pinMode(RED_PIN,    OUTPUT);
  pinMode(GREEN_PIN,  OUTPUT);
  pinMode(BLUE_PIN,   OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


// ============================================================
//  SETCOLOR — Sets the colour of the LED
//
//  Think of it like mixing paint:
//
//    setColor(255, 0, 0)     → full red, nothing else
//    setColor(0, 255, 0)     → full green, nothing else
//    setColor(0, 0, 255)     → full blue, nothing else
//    setColor(255, 255, 0)   → red + green mixed = yellow
//    setColor(0, 0, 0)       → all off
//
//  Each number goes from 0 (off) to 255 (full brightness).
// ============================================================

void setColor(int r, int g, int b) {
  analogWrite(RED_PIN,   r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN,  b);
}


// ============================================================
//  LIGHT STATES
// ============================================================


// ── STATE 0 — Off ───────────────────────────────────────────

void stateOff() {
  setColor(0, 0, 0);
}


// ── STATE 1 — Solid Red ─────────────────────────────────────
//
//  We want the LED to show solid red and stay there.
//
//  255 = full red, 0 = green off, 0 = blue off

void stateSolidRed() {
  setColor(255, 0, 0);

}


// ── STATE 2 — Solid Purple ───────────────────────────────────
//
//  We want the LED to show solid purple and stay there.
//
// Task: 
//  1. Use an online color picker to find and generate a shade of purple [rgbcolorpicker.com]
//  2. Remove slashes on the next 3 lines.
//  3. Fill in setColor(R, G, B);
//  4. Remove the slashes from the state list and add 1 to the state count. [Located Further Down]

//void stateSolidPurple() {
//  setColor(?, ?, ?);

//}


// ── STATE 3 — Your Colour ───────────────────────────────────
//
//  This one is yours to customise!
//  Pick any colour you like using a colour picker.
//  Search "RGB colour picker" in your browser.
//
//  Task:
//  1. Write a function like the one above, but name it yourself. [void stateCustom() { ]
//  2. Add one line inside the curly brackets: 
//         - Pick a custom color [setColor(?, ?, ?);]
//         - Make it change between 2 colors [delay(500);] [if (digitalRead(BUTTON_PIN) == LOW) return;]
//  3. Add your state to the state list [Farther Below]

// vvvv ADD CUSTOM STATE HERE vvvv





// ── STATE 4 — Breathing ─────────────────────────────────────
//
//  The light slowly fades in and out like someone breathing.
//  This state is already complete — no changes needed!
//
//  The for loop counts "brightness" from 0 up to 255 (fade in)
//  then back down to 0 (fade out), pausing briefly each step.
//
//  delay(8) controls speed — smaller = faster, larger = slower.
//
// Task: 
//  1. Remove the slashes in front of this state in the state list and update the count
//
// ADVANCED CHALLENGE: Can you make this fade green?

void stateBreathing() {

  // Fade IN — count brightness from 0 up to 255
  for (int brightness = 0; brightness <= 255; brightness++) {
    setColor(brightness, 0, brightness / 4); // Purple
    delay(8);
    if (digitalRead(BUTTON_PIN) == LOW) return;
  }

  // Fade OUT — count brightness from 255 back down to 0
  for (int brightness = 255; brightness >= 0; brightness--) {
    setColor(brightness, 0, brightness / 4);
    delay(8);
    if (digitalRead(BUTTON_PIN) == LOW) return;
  }

  delay(300);  // brief pause at the bottom before the next breath
}


// ── STATE 5 — Colour Cycle ──────────────────────────────────
//
//  The light slowly drifts through every colour of the rainbow.
//  This state is already complete — no changes needed!
//
//  "hue" counts from 0 to 255, each number is a different colour:
//    0 = red,  85 = green,  170 = blue,  255 = back to red
//
//  delay(20) controls speed — smaller = faster, larger = slower.
//
// Task: 
//  1. Remove the slashes in front of this state in the state list and update the count

void stateColorCycle() {

  for (int hue = 0; hue < 256; hue++) {
    int r = (hue < 85)  ? (255 - hue * 3) : (hue < 170 ? 0 : (hue - 170) * 3);
    int g = (hue < 85)  ? (hue * 3) : (hue < 170 ? (170 - hue) * 3 : 0);
    int b = (hue < 85)  ? 0  : (hue < 170 ? (hue - 85) * 3  : 255 - (hue - 170) * 3);
    setColor(r, g, b);
    delay(20);
    if (digitalRead(BUTTON_PIN) == LOW) return;
  }
}


// ============================================================
//  STATE LIST
//
//  This connects each state number to its function.
//  When you add a new state:
//    1. Write the function above
//    2. Add a new case here:   case 6: stateMyThing(); break;
//    3. Add 1 to TOTAL_STATES
// ============================================================

const int TOTAL_STATES = 2;  // ← update this when you add a state!

void runCurrentState() {
  switch (currentState) {
    case 0: stateOff();         break;
    case 1: stateSolidRed();    break;
//    case 2: stateSolidPurple();  break;
//    case 3: YOURCUSTOMSTATENAME(); break;
//    case 4: stateBreathing();   break;
//    case 5: stateColorCycle();  break;
  }
}


// ============================================================
//  LOOP — Runs over and over forever
//
//  Each pass through the loop:
//    1. Checks if the button was just pressed
//       If yes — move to the next state
//    2. Waits for the button to be released
//    3. Runs whatever state we are currently in
// ============================================================

void loop() {

  bool buttonState = digitalRead(BUTTON_PIN);

  // A "fresh press" means the button is down NOW but was up last loop
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);  // debounce, wait for the signal to settle
    currentState = (currentState + 1) % TOTAL_STATES;  // move to next state

    // Wait here until the finger is off the button before continuing
    while (digitalRead(BUTTON_PIN) == LOW) {}
    delay(50);  // debounce on release
  }

  lastButtonState = buttonState;

  runCurrentState();
}
