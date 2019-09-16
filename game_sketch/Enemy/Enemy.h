#ifndef ENEMY_H
#define ENEMY_H

#include <Arduino.h>
#include <math.h>
#include <Bullet.h>
#include <Player.h>

#define ENEMY_FR 30
#define ENEMY_RADIUS 8
#define ENEMY_BULLET_SPEED 4

static const uint8_t enemy_bitmap[] PROGMEM = {
  0x10, 0x08, 0x0c, 0x30, 0x0c, 0x30, 0x1f, 0xf8, 0x73, 0xce, 0x73, 0xce, 0xff, 0xff, 0x9f, 0xf9,
	0x9f, 0xf9, 0x90, 0x09, 0x0e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static int enemy_positions[] = {0, 0, 0, 0, 0, 0};

/*static const uint8_t enemy_data[512] PROGMEM = {
    // ▓▓▓███▒▓█▓▓░░███
    // ▓▓∙█▓▒▒▓▓▓▓█████
    // ██▓███▓▒████████
    // ▓▓▓██▒▒▒▓██▓████
    // ▓▓██▓▒▒▓▓▓▓▓▓▓▓█
    // ████▓▓▓▓█▓▒▓▓░██
    // ▓▓▓▓▒▓████▓▒▓███
    // ▒▒▓▒▓▓████▓▓███▓
    // ▓▒▓▒▓▓█████▓███▓
    // █▓▓▓▓▓████▓▒▓███
    // █████▓▓▓█▓▒▓▓▒██
    // ▓████▓▓▒▓▓▓▓██▓█
    // █████▓▓▓▓███████
    // ███████▓████████
    // ▓▓▒██▓▓█▓███████
    // ██████▓████▓▓███
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x85,0x21,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5a,0xea,0x4a,0x68,0x84,0x50,0xad,0x54,0x8c,0x4f,0x52,0xa9,0x31,0x85,0x39,0xe6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0xff,0xff,0x84,0x2f,0xbd,0xf6,0xa5,0x13,0x84,0x0e,0x6b,0x4b,0x42,0x27,0xcd,0xd4,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x7c,0x0e,0xb5,0x95,0x8c,0x2f,0x6b,0x2b,0x4a,0x47,0x29,0x43,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x40,0x00,0x00,0x4a,0x89,0x8c,0x50,0xbd,0xd6,0xc5,0xf6,0xa4,0xf2,0x8c,0x2f,0x6b,0x4b,0x4a,0x47,0x31,0xc5,0x21,0x43,0x00,0x00,0x08,0x81,0x00,0x00
,0x00,0x40,0xde,0xba,0x7b,0xee,0xbd,0xd6,0xc6,0x37,0xad,0x33,0x8c,0x70,0x6b,0x6c,0x63,0x2a,0x6b,0x4b,0x5a,0xa9,0x52,0x47,0x4a,0x47,0x39,0xc5,0x5a,0xc9,0x00,0x40
,0x00,0x40,0x00,0x00,0x6b,0x8d,0x5b,0x0b,0x42,0x27,0x41,0xe6,0x3a,0x42,0x4b,0x81,0x4b,0x81,0x42,0x62,0x39,0xc5,0x29,0x23,0x29,0x64,0x39,0xc5,0x00,0x00,0x00,0x40
,0x00,0x40,0x00,0x00,0x10,0xa1,0x08,0x60,0x39,0xa5,0x39,0xc5,0x4b,0x20,0xb6,0x6b,0xb6,0x6b,0x4b,0x40,0x39,0xc5,0x21,0x23,0x00,0x40,0x08,0xa1,0x00,0x40,0x00,0x40
,0x00,0x00,0x00,0x00,0x18,0xe2,0x10,0xc1,0x31,0xc5,0x29,0x43,0x08,0xa0,0x42,0x63,0x3a,0x43,0x08,0xa0,0x29,0x64,0x29,0x64,0x00,0x20,0x08,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};*/

static const int direction_x[8] = { 0,  1, 1, 1, 0, -1, -1, -1};
static const int direction_y[8] = {-1, -1, 0, 1, 1,  1,  0, -1};

static int _nEnemies = 0;
class Enemy{
    private:
      int _pos_x;
      int _pos_y;
      bool _destroyed;
      int _id;
      int _limit_x;
      int _limit_y;
      int _bullet_cd;
      int _prev_x;
      int _prev_y;
      char turn;
      char iteration;
      int _last_distance;

    public:
      Enemy();
      ~Enemy();
      Enemy(const Enemy& other);

      bool check_collision(Bullet &blt);
      bool check_collision(Player &player);
      bool check_collision(int * pos, double radius);
      void on_collision(int type);
      void update(int * player_pos, LinkedList<Bullet> & bullets);
      void on_draw(Adafruit_ST7735 * tft);
      void set_position(int posx, int posy);
      void set_boundaries(int limitx, int limity);
      Enemy& operator=(const Enemy& other);
      int operator==(const Enemy& other) const;
      void position(int * pos);
      void destroy(Adafruit_ST7735 * tft);
      bool destroyed();
      void respawn();
      void clear(Adafruit_ST7735 * tft);
};

#endif // ENEMY_H