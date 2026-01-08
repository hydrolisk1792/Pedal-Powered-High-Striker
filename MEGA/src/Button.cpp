#include "Button.h"

Button::Button(uint8_t pin, unsigned long debounce, bool activeLow)
  : pin(pin), debounceTime(debounce), activeLow(activeLow) 
{
  pinMode(pin, activeLow ? INPUT_PULLUP : INPUT);
}

bool Button::isDown() {
  bool rawState = digitalRead(pin);
  return activeLow ? !rawState : rawState;
}

bool Button::pressed() {
  bool rawState = isDown();

  if (rawState != prevState) {
    if (millis() - lastChange > debounceTime) {
      lastChange = millis();
      prevState = rawState;

      if (rawState == true) {  
        return true;           // Button was just pressed
      }
    }
  }
  return false;
}

bool Button::released() {
  bool rawState = isDown();

  if (rawState != prevState) {
    if (millis() - lastChange > debounceTime) {
      lastChange = millis();
      prevState = rawState;

      if (rawState == false) {  
        return true;           // Button was just released
      }
    }
  }
  return false;
}
