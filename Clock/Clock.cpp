#include "Clock.h"

#include "Tools.h"

// local variables
CRGB Clock::leds[NUM_LEDS];
CRGB Clock::digitsColor = CRGB(255, 0, 0);
bool Clock::ClockOn = true;


void Clock::init(){
  // init of the FastLED library
  digitalWrite(13, LOW);
  FastLED.addLeds<WS2812, LEDS_PIN, GRB>(Clock::leds, NUM_LEDS);

  // setting the mosfet pin as output to switch on and off the leds power
  pinMode(LEDS_SWITCH_PIN, OUTPUT);

  // turning on the screen
  turnOnScreen();

  // clearing the display of the clock
  clearScreenAndUpdate();
}


void Clock::displayDigit(int segment, int digit){

  segment = segment % 4;
  digit = digit % 10;

  int top = getTopOfSegment(segment);
  int top_left = getTopLeftOfSegment(segment);
  int top_right = getTopRightOfSegment(segment);
  int center = getCenterOfSegment(segment);
  int bottom = getBottomOfSegment(segment);
  int bottom_left = getBottomLeftOfSegment(segment);
  int bottom_right = getBottomRightOfSegment(segment);

  clearSegment(segment);

  switch(digit){
    case 0:
      leds[top] = digitsColor;
      leds[top_right] = digitsColor;
      leds[top_left] = digitsColor;
      leds[bottom_right] = digitsColor;
      leds[bottom_left] = digitsColor;
      leds[bottom] = digitsColor;
    break;

    case 1:
      leds[top_right] = digitsColor;
      leds[bottom_right] = digitsColor;
    break;

    case 2:
      leds[top] = digitsColor;
      leds[top_right] = digitsColor;
      leds[center] = digitsColor;
      leds[bottom_left] = digitsColor;
      leds[bottom] = digitsColor;
    break;

    case 3:
      leds[top] = digitsColor;
      leds[top_right] = digitsColor;
      leds[center] = digitsColor;
      leds[bottom_right] = digitsColor;
      leds[bottom] = digitsColor;
    break;

    case 4:
      leds[top_right] = digitsColor;
      leds[top_left] = digitsColor;
      leds[center] = digitsColor;
      leds[bottom_right] = digitsColor;
    break;

    case 5:
      leds[top] = digitsColor;
      leds[top_left] = digitsColor;
      leds[center] = digitsColor;
      leds[bottom_right] = digitsColor;
      leds[bottom] = digitsColor;
    break;

    case 6:
      leds[top] = digitsColor;
      leds[top_left] = digitsColor;
      leds[center] = digitsColor;
      leds[bottom_right] = digitsColor;
      leds[bottom_left] = digitsColor;
      leds[bottom] = digitsColor;
    break;

    case 7:
      leds[top] = digitsColor;
      leds[top_right] = digitsColor;
      leds[bottom_right] = digitsColor;
    break;

    case 8:
      leds[top] = digitsColor;
      leds[top_right] = digitsColor;
      leds[top_left] = digitsColor;
      leds[center] = digitsColor;
      leds[bottom_right] = digitsColor;
      leds[bottom_left] = digitsColor;
      leds[bottom] = digitsColor;
    break;

    case 9:
      leds[top] = digitsColor;
      leds[top_right] = digitsColor;
      leds[top_left] = digitsColor;
      leds[center] = digitsColor;
      leds[bottom_right] = digitsColor;
      leds[bottom] = digitsColor;
    break;
  }
}

void Clock::displayDigitAndUpdate(int segment, int digit){
  displayDigit(segment, digit);
  updateScreen();
}

void Clock::turnOnTwoPoints(){
  leds[getTwoPoints()] = digitsColor;
}

void Clock::turnOnTwoPointsAndUpdate(){
  turnOnTwoPoints();
  updateScreen();
}

bool Clock::updateScreen(){
  if(ClockOn){
    FastLED.show();
    return true;
  }
  return false;
}


void Clock::displayNumber(int number){
  String numStr = numberToFixedString(number, 4);

  clearAllSegments();
  for(int s=0; s<4; s++){
    int d = numStr[s] - '0';
    displayDigit(s, d);
  }
}

void Clock::displayNumberAndUpdate(int number){
    displayNumber(number);
    updateScreen();
}

void Clock::displayMinutes(int minutes){
  minutes = minutes % 100;
  String numStr = numberToFixedString(minutes, 2);
  clearMinutes();

  int decimals = numStr[0] - '0';
  int units = numStr[1] - '0';

  displayDigit(2, decimals);
  displayDigit(3, units);

}

void Clock::displayMinutesAndUpdate(int minutes){
  displayMinutes(minutes);
  updateScreen();
}

void Clock::displayHours(int hours){
  hours = hours % 100;

  String numStr = numberToFixedString(hours, 2);
  clearHours();

  int decimals = numStr[0] - '0';
  int units = numStr[1] - '0';

  displayDigit(0, decimals);
  displayDigit(1, units);
}

void Clock::displayHoursAndUpdate(int hours){
  displayHours(hours);
  updateScreen();
}

void Clock::setDigitsColor(int r, int g, int b){
  digitsColor = CRGB(r,g,b);
}

void Clock::updateDigitsColor(int r, int g, int b){
  setDigitsColor(r,g,b);

  for(int i=0; i<NUM_LEDS; i++){
    if( leds[i] != CRGB(0,0,0) ){
      leds[i] = digitsColor;
    }
  }
  updateScreen();
}


void Clock::turnOnScreen(){
  // turning on the mosfet to close the leds circuit
  digitalWrite(LEDS_SWITCH_PIN, HIGH);

  ClockOn = true;
}

void Clock::turnOffScreen(){
  // turning off the mosfet to open up the leds circuit
  digitalWrite(LEDS_SWITCH_PIN, LOW);

  // writing high to the data pin to remove voltage between the Vcc and data pin of the clock
  digitalWrite(LEDS_PIN, HIGH);

  ClockOn = false;
}

void Clock::switchScreenOnOff(){

  if(ClockOn){
    turnOffScreen();
  }else{
    turnOnScreen();
  }
}

bool Clock::getScreenState(){
  return ClockOn;
}


void Clock::clearScreen(){
  // updating the local state of the leds
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB(0, 0, 0);
  }
}

void Clock::clearScreenAndUpdate(){
  clearScreen();
  updateScreen();
}

void Clock::clearAllSegments(){
  for(int i=0; i<4; i++){
    clearSegment(i);
  }
}

void Clock::clearAllSegmentsAndUpdate(){
  clearAllSegments();
  updateScreen();
}

void Clock::clearSegment(int segment){
  segment = segment % 4;
  switch(segment){
    case 0:
      for(int i=0; i<7; i++){
        leds[i] = CRGB(0,0,0);
      }
    break;

    case 1:
      for(int i=7; i<14; i++){
        leds[i] = CRGB(0,0,0);
      }
    break;

    case 2:
      for(int i=15; i<22; i++){
        leds[i] = CRGB(0,0,0);
      }
    break;

    case 3:
      for(int i=22; i<29; i++){
        leds[i] = CRGB(0,0,0);
      }
    break;
  }
}

void Clock::clearSegmentAndUpdate(int segment){
  clearSegment(segment);
  updateScreen();
}

void Clock::turnOffTwoPoints(){
  leds[getTwoPoints()] = CRGB(0,0,0);
}

void Clock::turnOffTwoPointsAndUpdate(){
  turnOffTwoPoints();
  updateScreen();
}

void Clock::clearMinutes(){
  clearSegment(2);
  clearSegment(3);
}

void Clock::clearHours(){
  clearSegment(0);
  clearSegment(1);
}

void Clock::clearMinutesAndUpdate(){
  clearMinutes();
  updateScreen();
}

void Clock::clearHoursAndUpdate(){
  clearHours();
  updateScreen();
}



int Clock::getTopOfSegment(int segment){
  switch(segment){
    case 0:
    return LED_SEGMENT_0_TOP;
    case 1:
    return LED_SEGMENT_1_TOP;
    case 2:
    return LED_SEGMENT_2_TOP;
    case 3:
    return LED_SEGMENT_3_TOP;
  }
}

int Clock::getTopLeftOfSegment(int segment){
  switch(segment){
    case 0:
    return LED_SEGMENT_0_TOP_LEFT;
    case 1:
    return LED_SEGMENT_1_TOP_LEFT;
    case 2:
    return LED_SEGMENT_2_TOP_LEFT;
    case 3:
    return LED_SEGMENT_3_TOP_LEFT;
  }
}

int Clock::getTopRightOfSegment(int segment){
  switch(segment){
    case 0:
    return LED_SEGMENT_0_TOP_RIGHT;
    case 1:
    return LED_SEGMENT_1_TOP_RIGHT;
    case 2:
    return LED_SEGMENT_2_TOP_RIGHT;
    case 3:
    return LED_SEGMENT_3_TOP_RIGHT;
  }
}

int Clock::getCenterOfSegment(int segment){
  switch(segment){
    case 0:
    return LED_SEGMENT_0_CENTER;
    case 1:
    return LED_SEGMENT_1_CENTER;
    case 2:
    return LED_SEGMENT_2_CENTER;
    case 3:
    return LED_SEGMENT_3_CENTER;
  }
}

int Clock::getBottomOfSegment(int segment){
  switch(segment){
    case 0:
    return LED_SEGMENT_0_BOTTOM;
    case 1:
    return LED_SEGMENT_1_BOTTOM;
    case 2:
    return LED_SEGMENT_2_BOTTOM;
    case 3:
    return LED_SEGMENT_3_BOTTOM;
  }
}

int Clock::getBottomLeftOfSegment(int segment){
  switch(segment){
    case 0:
    return LED_SEGMENT_0_BOTTOM_LEFT;
    case 1:
    return LED_SEGMENT_1_BOTTOM_LEFT;
    case 2:
    return LED_SEGMENT_2_BOTTOM_LEFT;
    case 3:
    return LED_SEGMENT_3_BOTTOM_LEFT;
  }
}

int Clock::getBottomRightOfSegment(int segment){
  switch(segment){
    case 0:
    return LED_SEGMENT_0_BOTTOM_RIGHT;
    case 1:
    return LED_SEGMENT_1_BOTTOM_RIGHT;
    case 2:
    return LED_SEGMENT_2_BOTTOM_RIGHT;
    case 3:
    return LED_SEGMENT_3_BOTTOM_RIGHT;
  }
}

int Clock::getTwoPoints(){
  return LED_POINTS;
}
