#ifndef _PLOT_H
#define _PLOT_H

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

class Matrix 
{
 public:
  virtual int valueAt (int x, int y);
  virtual float labelAt (int x, int y);
} ;

class Plot {

 public:

  Plot(int _linesCount, int _numbers, Adafruit_ST7735 *_tft, Matrix *_measurements); // Constructor
  int GetMinTempValue();
  int GetMaxTempValue();


  // This MUST be defined by the subclass:
  void DrawTemperature();

};

#endif // _PLOT_H
