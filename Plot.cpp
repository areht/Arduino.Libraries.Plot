#include "Plot.h"


int linesCount;
int numbers;
Adafruit_ST7735 *tft;

Matrix *matrix;
                 
Plot::Plot(int _linesCount, int _numbers, Adafruit_ST7735 *_tft, Matrix *_matrix)
{
linesCount = _linesCount;
numbers = _numbers;
tft = _tft;
matrix = _matrix;
}

int Plot::GetMinTempValue() {return 0;}
int Plot::GetMaxTempValue() {return 0x07D0;}


void Plot::DrawTemperature()
{
  int temp[linesCount];
  int labelCoordinate[linesCount];

  for (int i = 0; i < numbers; i++)
  {
    int tempcolors[3] = {
      ST7735_RED,
      ST7735_GREEN,
      ST7735_BLUE
    };
    for (int d = 0; d < linesCount; d++)
    {
      int x = map(matrix->valueAt(i,d), GetMinTempValue(), GetMaxTempValue(), 0, tft->height() / 2);
      temp[d] = x;
      labelCoordinate[d] = x;
    }

    tft->fillRect(i , tft->height() / 2, 1, tft->height() / 2, ST7735_BLACK);
    tft->drawPixel(i, tft->height() - 75, ST7735_WHITE);
    for (int d = 0; d < linesCount; d++)
    {
      for (int t = d + 1; t < linesCount; t++)
      {
        if (temp[d] == temp[t])
        {
          temp[t] = 0;
          labelCoordinate[t] = -1;
          unsigned int c = tempcolors[d] | tempcolors[t];
          tempcolors[d] = c;
          tempcolors[t] = c;
        } 
        else if ((i == (numbers-1)) && (temp[d] - temp[t] < 7) && (matrix->labelAt(numbers - 1,d) != matrix->labelAt(numbers - 1,t)))
        {
          if (labelCoordinate[d] > labelCoordinate[t] )
            labelCoordinate[t] = labelCoordinate[t] - 8;
          else
            labelCoordinate[d] = labelCoordinate[d] - 8;
        }
      }
      int x = temp[d];
      tft->drawPixel(i, tft->height() - x, tempcolors[d]);

    }
  }

  for (int i = numbers; i < 128; i++)
  {
    tft->fillRect(i , tft->height() / 2, 1, tft->height() / 2, ST7735_BLACK);
  }

  tft->setTextColor(ST7735_WHITE);
  for (int d = 0; d < linesCount; d++)
  {
    int x = labelCoordinate[d];
    if (x != -1)
    {
      tft->setCursor(numbers - 6, tft->height() - x - 9);
      tft->print(matrix->labelAt(numbers - 1,d));
    }
  }
}
