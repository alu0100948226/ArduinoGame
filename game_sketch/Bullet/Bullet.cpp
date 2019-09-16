#include "Bullet.h"

Bullet::Bullet(){
  _id = _nBullets;
  _nBullets++;

}

Bullet::Bullet(int x_axis, int y_axis){
  _id = _nBullets;
  _nBullets++;
  _x_axis = x_axis;
  _y_axis = y_axis;
  _delete = false;
}

Bullet::Bullet(const Bullet& other){
  _id = other._id;
  _x_axis = other._x_axis;
  _y_axis = other._y_axis;
  _delete = other._delete;
  _prev_x = other._prev_x;
  _prev_y = other._prev_y;
  _bullet_x = other._bullet_x;
  _bullet_y = other._bullet_y;
  _limit_x = other._limit_x;
  _limit_y = other._limit_y;
}

Bullet::~Bullet(){
  // Serial.println("Bullet destroyed");
}

void Bullet::position(int * position, int * prev_position){
  position[0] = _bullet_x;
  position[1] = _bullet_y;
  prev_position[0] = _prev_x;
  prev_position[1] = _prev_y;
}

void Bullet::update(){
  _prev_x = _bullet_x;
  _prev_y = _bullet_y;

  // Serial.print("bullet direction: (");
  // Serial.print(_x_axis);
  // Serial.print(",");
  // Serial.print(_y_axis);
  // Serial.println(")");

  _bullet_x += _x_axis;
  _bullet_y += _y_axis;
  if( _bullet_x < 0 || _bullet_x >= _limit_x)
    _delete = true;
  if( _bullet_y < 0 || _bullet_y >= _limit_y)
    _delete = true;
  // Serial.print("updating bullet: (");
  // Serial.print(_bullet_x);
  // Serial.print(",");
  // Serial.print(_bullet_y);
  // Serial.println(")");


}

void Bullet::on_collision(){
  _delete = true;
}
void Bullet::set_initial_pos(int x, int y){
  _prev_x = _bullet_x = x;
  _prev_y = _bullet_y = y;
}

void Bullet::set_boundaries(int limit_x, int limit_y){
  _limit_x = limit_x;
  _limit_y = limit_y;
}

void Bullet::on_draw(Adafruit_ST7735 * tft){
  _tft = tft;
  tft->drawPixel(_prev_x, _prev_y, ST77XX_BLACK);
  tft->drawPixel(_bullet_x, _bullet_y, ST77XX_YELLOW);
}

Bullet& Bullet::operator = (const Bullet& other){
  _id = other._id;
  _x_axis = other._x_axis;
  _y_axis = other._y_axis;
  _delete = other._delete;
  _prev_x = other._prev_x;
  _prev_y = other._prev_y;
  _bullet_x = other._bullet_x;
  _bullet_y = other._bullet_y;
  _limit_x = other._limit_x;
  _limit_y = other._limit_y;
}

bool Bullet::destroyed(){
  return _delete;
}

int Bullet::operator ==(const Bullet& other) const {
  if(_id == other._id)
    return 1;
  return 0;
}

void Bullet::set_display(Adafruit_ST7735 * tft){
  _tft = tft;
}

void Bullet::destroy(Adafruit_ST7735 * tft){

  tft->drawPixel(_bullet_x, _bullet_y, ST77XX_BLACK);
}

void Bullet::clear(Adafruit_ST7735 * tft){
  tft->drawPixel(_prev_x, _prev_y, ST77XX_BLACK);
}
