#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
  Button(uint8_t pin, unsigned long debounce = 50, bool activeLow = true);

  bool pressed();       // returns true once per press
  bool hold();        // returns true as long as button is held
  bool released();      // returns true once when released

private:
  uint8_t pin;
  unsigned long lastChange = 0;
  unsigned long debounceTime;
  bool activeLow;

  bool prevState = HIGH;
};

#endif

