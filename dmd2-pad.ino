// Use included zip in libraries directory. Add it through:
//   Sketch -> Include Library -> Add .ZIP library menu in arduino IDE
#include <BleKeyboard.h>  // bleKeyboard
#include <Bounce2.h>      // Bounce

// Set Bluetooth Device Name, manufacturer, (virtual) battery level
BleKeyboard BleKeyboard("DMD2 CTL 8K", "koko", 100);

// This is the basic data structure of the sketch
// Each row represents a hardware button with its properties 
struct Button {
  uint8_t pin;
  Bounce debouncer;
  const uint8_t buttonCommand;
  String description;
};

// defined as pinNumber, Bounce instance, buttonCommand, description
Button buttons[] = {
  { 2,  Bounce(), KEY_UP_ARROW,    "UP"     },  // UP
  { 3,  Bounce(), KEY_DOWN_ARROW,  "DOWN"   },  // DOWN
  { 4,  Bounce(), KEY_LEFT_ARROW,  "LEFT"   },  // LEFT
  { 8,  Bounce(), KEY_RIGHT_ARROW, "RIGHT"  },  // RIGHT
  { 6,  Bounce(), KEY_RETURN,      "ENTER"  },  // ENTER
  { 7,  Bounce(), KEY_F5,          "BACK"   },  // BACK
  { 10, Bounce(), KEY_F6,          "ZOOM +" },  // ZOOM +
  { 9,  Bounce(), KEY_F7,          "ZOOM -" }   // ZOOM -
};

// Number of buttons
const int NUMBER_OF_BUTTONS = sizeof(buttons) / sizeof(buttons[0]);
// Delay in milliseconds between button state change
const int DEBOUNCE_DELAY = 15;

// SETUP
void setup() {
  // Setup Serial
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Setup bleKeyboard
  BleKeyboard.begin();
  Serial.println("BleKeyboard started");

  // Set pullup mode and bounce interval in ms
  for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
    buttons[i].debouncer.attach(buttons[i].pin);
    buttons[i].debouncer.interval(DEBOUNCE_DELAY); // Set debounce interval to 10ms
  }
  Serial.println("DMD2 Pad: Initialization done!");

}


// MAIN LOOP
void loop() {
  for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
    buttons[i].debouncer.update();

    if (buttons[i].debouncer.fell()) {
      // Button was pressed
      Serial.println("Pressed " + buttons[i].description);
      BleKeyboard.press(buttons[i].buttonCommand);
    }
    else if (buttons[i].debouncer.rose()) {
      // Button was released
      BleKeyboard.release(buttons[i].buttonCommand);
      Serial.println("Released " + buttons[i].description);
    }
  }

  delay(1); // Loop delay of 1ms

}
