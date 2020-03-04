
#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

#include <FastLED.h>

#include "Config.h"

class Clock{

  public:
    static bool ClockOn;

    static CRGB leds[NUM_LEDS];

    static CRGB digitsColor;

  public:

    static void init();

    // basic display
    static void displayDigit(int segment, int digit);
    static void displayDigitAndUpdate(int segment, int digit);

    static void turnOnTwoPoints();
    static void turnOnTwoPointsAndUpdate();

    static bool updateScreen();

    // advanced display
    static void displayNumber(int number);
    static void displayNumberAndUpdate(int number);

    static void displayMinutes(int minutes);
    static void displayHours(int hours);
    static void displayMinutesAndUpdate(int minutes);
    static void displayHoursAndUpdate(int hours);

    // personalisation
    static void setDigitsColor(int r, int g, int b); // set the color for future displays
    static void updateDigitsColor(int r, int g, int b); // set and instantly update the screen color

    // Screen power management
    static void turnOnScreen();
    static void turnOffScreen();
    static void switchScreenOnOff();
    static bool getScreenState();

    // clearing
    static void clearScreen();
    static void clearAllSegments();
    static void clearSegment(int segment);
    static void turnOffTwoPoints();

    static void clearMinutes();
    static void clearHours();

    static void clearScreenAndUpdate();
    static void clearAllSegmentsAndUpdate();
    static void clearSegmentAndUpdate(int segment);
    static void turnOffTwoPointsAndUpdate();

    static void clearMinutesAndUpdate();
    static void clearHoursAndUpdate();

// functions to encapsulate the constants in file LedNumbers.h
private:
    static int getTopOfSegment(int segment);
    static int getTopLeftOfSegment(int segment);
    static int getTopRightOfSegment(int segment);
    static int getCenterOfSegment(int segment);
    static int getBottomOfSegment(int segment);
    static int getBottomLeftOfSegment(int segment);
    static int getBottomRightOfSegment(int segment);
    static int getTwoPoints();
};

#endif
