#ifndef PLAYER
#define PLAYER

#include <Arduino.h>

#include <SPI.h>

#include <Adafruit_ST7735.h>

#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>

#include <Bullet.h>

#include <LinkedList.h>

#define PLAYER_RADIUS 8
#define SHIELD_COUNTDOWN 30
#define MAX_HEALTH 3

const static char text[3] = "SH";



const static uint8_t player_bitmap[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x0f, 0xf0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const static uint8_t player_health[] PROGMEM = {
  0x18, 0x18, 0x3e, 0x7c, 0x7e, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe,
  0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00
};
/*const static uint8_t player_data[512] PROGMEM = {
    // ░░░∙∙∙▒░∙░░▓▓∙∙∙
    // ░░█∙░▒▒░░░░∙∙∙∙∙
    // ∙∙░∙∙∙░▒∙∙∙∙∙∙∙∙
    // ░░░∙∙▒▒▒░∙∙░∙∙∙∙
    // ░░∙∙░▒▒░░░░░░░░∙
    // ∙∙∙∙░░░░∙░▒░░▓∙∙
    // ░░░░▒░∙∙∙∙░▒░∙∙∙
    // ▒▒░▒░░∙∙∙∙░░∙∙∙░
    // ░▒░▒░░∙∙∙∙∙░∙∙∙░
    // ∙░░░░░∙∙∙∙░▒░∙∙∙
    // ∙∙∙∙∙░░░∙░▒░░▒∙∙
    // ░∙∙∙∙░░▒░░░░∙∙░∙
    // ∙∙∙∙∙░░░░∙∙∙∙∙∙∙
    // ∙∙∙∙∙∙∙░∙∙∙∙∙∙∙∙
    // ░░▒∙∙░░∙░∙∙∙∙∙∙∙
    // ∙∙∙∙∙∙░∙∙∙∙░░∙∙∙
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x82,0xfe,0x82,0x00,0x1f,0x42,0xb9,0x42,0xb9,0x00,0x1f,0xfe,0x82,0xfe,0x82,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xe6,0x05,0xe6,0x05,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0xff,0xa0,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xfe,0x82,0xff,0xa0,0x00,0x00,0x00,0x00
,0x00,0x00,0x31,0x90,0xf6,0x43,0x4a,0x0f,0xe5,0xc4,0xee,0x04,0xee,0x04,0xee,0x04,0xee,0x04,0xee,0x04,0xee,0x04,0xe5,0xc4,0x4a,0x0f,0xf6,0x43,0x31,0x90,0x00,0x00
,0x31,0x0c,0x31,0x6f,0x31,0x90,0x31,0x90,0x4a,0x2e,0x52,0x4e,0x52,0x4e,0x52,0x4e,0x52,0x4e,0x52,0x4e,0x52,0x4e,0x4a,0x2e,0x31,0x90,0x31,0x90,0x31,0x6f,0x31,0x0c
,0x39,0xf4,0x39,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x31,0xd3,0x39,0xd3,0x39,0xf4
,0x3a,0x78,0x3a,0x79,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x99,0x3a,0x79,0x3a,0x78
,0x3a,0x99,0x3a,0x9a,0x3a,0xba,0x3a,0x36,0x39,0xf4,0x39,0xf4,0x39,0xf4,0x39,0xf4,0x39,0xf4,0x39,0xf4,0x39,0xf4,0x39,0xf4,0x3a,0x36,0x3a,0xba,0x3a,0x9a,0x3a,0x99
,0x00,0x00,0x00,0x00,0x31,0x6f,0x31,0x6f,0x31,0x70,0x31,0x90,0x31,0x90,0x31,0x90,0x31,0x90,0x31,0x90,0x31,0x90,0x31,0x70,0x31,0x6f,0x31,0x6f,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};*/

class Player {
    public:
        Player();
        ~Player();
        void set_boundaries(int width, int height);
        bool check_collision(int * pos, double radius);
        void update(int x_axis, int y_axis, bool click, LinkedList<Bullet> & bullets);
        void on_collide(int object);
        bool firemode();
        void on_draw(Adafruit_ST7735 * tft);
        void position(int * position);
        bool dead();
        void reset();
        void clear(Adafruit_ST7735 * tft);
    private:
        int _player_x;
        int _player_y;
        int _prev_x;
        int _prev_y;
        int _limit_x;
        int _limit_y;
        int _health;
        int _shields;
        bool _shielded;
        int _shield_timer;
        bool text_written;

};

#endif //PLAYER
