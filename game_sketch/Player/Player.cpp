#include "Player.h"

Player::Player(){
    _prev_y = _player_x = 0;
    _prev_y = _player_y = 0;
    _health = 3;
    _shields = 0;
    _shielded = false;
    _shield_timer = 0;
    text_written = false;
}

Player::~Player(){

}

void Player::set_boundaries(int width, int height){
  _limit_x = width;
  _limit_y = height;
}

void Player::update(int x_axis, int y_axis, bool pressed, LinkedList<Bullet> & bullets){
  _prev_x = _player_x;
  _prev_y = _player_y;
  _player_x += 2*x_axis;
  _player_y += 2*y_axis;
  if(_player_x < 0)
    _player_x = 0;
  else if(_player_x >= _limit_x)
    _player_x = _limit_x - 1;

  if(_player_y < 0)
    _player_y = 0;
  else if(_player_y >= _limit_y)
    _player_y = _limit_y - 1;

  if(pressed && !_shielded && _shields >= 1){
    _shielded = true;
    _shield_timer = SHIELD_COUNTDOWN;
    _shields--;
  }

  if(_shielded)
    _shield_timer--;

  if(_shielded && _shield_timer == 0 )
    _shielded = false;
}

void Player::on_collide(int object){
  if( object == 1 || object == 2){
    if(!_shielded){
      _health--;
    }
  }
  else
    _shields++;
}
void Player::on_draw(Adafruit_ST7735 * tft){
  if(_shielded && !text_written){
    for(int i = 0; i < 2*8; i+=8)
      tft->drawChar(i, 0, text[i/8], ST77XX_WHITE, ST77XX_BLACK, 1);
    text_written = true;
  }
  for(int i = 0; i < _health; i++)
    tft->drawBitmap(_limit_x - 48 + i*16, 0, &player_health[0], 16, 16, ST77XX_WHITE);

  for(int i = _health; i < 3; i++)
    tft->fillRect(_limit_x - 48 + i*16, 0, 16, 16, ST77XX_BLACK);
  // tft->drawBitmap(_prev_x - 8, _prev_y - 8, &black_scr[0], 16, 16, ST77XX_BLACK);
  tft->drawBitmap(_player_x - 8, _player_y - 8, &player_bitmap[0], 16, 16, ST77XX_GREEN );
}

void Player::position(int * position){
  position[0] = _player_x;
  position[1] = _player_y;
}

bool Player::check_collision(int * pos, double radius){
  int calc_x = pos[0] - _player_x;
  int calc_y = pos[1] - _player_y;
  double distance = sqrt(pow(calc_x, 2) + pow(calc_y, 2));
  if (distance <= PLAYER_RADIUS + radius){
    // Serial.println("I've been hit!!");
    return true;
  }
  return false;

}

bool Player::dead(){
  if (_health <= 0)
    return true;
  return false;
}

void Player::reset(){
  _player_x = analogRead(A4);
  _player_y = analogRead(A5);
  _health = MAX_HEALTH;
  text_written = false;
}

void Player::clear(Adafruit_ST7735 * tft){
  // tft->fillRect(_limit_x - 48,0,36, 16, ST77XX_BLACK);
  tft->fillRect(_prev_x-5,_prev_y-3,10, 6, ST77XX_BLACK);
  if(text_written)
    tft->fillRect(0,0,24, 8, ST77XX_BLACK);
    text_written = false;
}
