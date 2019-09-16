#ifndef BULLET
#define BULLET

#include <Arduino.h>

#include <SPI.h>

#include <Adafruit_ST7735.h>

#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>

static int _nBullets = 0;
class Bullet{
    private:
      int _id;
      int _bullet_x;
      int _bullet_y;
      int _prev_x;
      int _prev_y;
      int _x_axis;
      int _y_axis;
      int _limit_x;
      int _limit_y;
      bool _delete;
      Adafruit_ST7735 * _tft;


    public:
      Bullet();
      Bullet(int x_axis, int y_axis);
      Bullet(const Bullet&);
      ~Bullet();

      void update();
      void on_collision();
      void set_initial_pos(int x, int y);
      void set_boundaries(int limit_x, int limit_y);
      void set_display(Adafruit_ST7735 * tft);
      bool destroyed();
      void on_draw(Adafruit_ST7735 * tft);
      Bullet& operator = (const Bullet&);
      int operator ==(const Bullet&) const;
      void position(int * position, int * prev_position);
      void destroy(Adafruit_ST7735 * tft);
      void clear(Adafruit_ST7735 * tft);

};

#endif //BULLET
