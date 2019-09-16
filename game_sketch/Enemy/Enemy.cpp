#include <Enemy.h>

Enemy::Enemy(){
  _id = _nEnemies;
  Serial.print("Id: ");
  Serial.println(_id);
  _nEnemies++;
  _nEnemies = _nEnemies%3;
  _pos_x = 0;
  _pos_y = 0;
  _destroyed = false;
  _bullet_cd = 0;
  _prev_x = 1;
  _prev_y = 1;
  turn = 0;
  iteration = 0;
  _last_distance = 0;
}

Enemy::Enemy(const Enemy& other){
  _id = other._id;
  _pos_x = other._pos_x;
  _pos_y = other._pos_y;
  enemy_positions[_id*2] = _pos_x;
  enemy_positions[_id*2 + 1] = _pos_y;

  _limit_x = other._limit_x;
  _limit_y = other._limit_y;
  _destroyed = other._destroyed;
}

Enemy::~Enemy(){

}

bool Enemy::check_collision(int * pos, double radius){
  char calc_x = pos[0] - _pos_x;
  char calc_y = pos[1] - _pos_y;
  double distance = sqrt(pow(calc_x, 2) + pow(calc_y, 2));
  if (distance <= ENEMY_RADIUS + radius){
    return true;
  }
  return false;
}

void Enemy::on_collision(int type){
  _destroyed = true;
}

void Enemy::update(int * player_pos, LinkedList<Bullet> & bullets){
  if(iteration % 3){
    double distances[3] = {0, 0, 0};
    uint8_t idx_L = (turn - 1 < 0)? 7: turn - 1;
    uint8_t idx_R = (turn + 1 > 7)? 0: turn + 1;
    uint8_t index[3] = {idx_L, turn, idx_R};
    distances[0] = sqrt(   pow(player_pos[0] - _pos_x - direction_x[idx_L], 2)
                         + pow(player_pos[1] - _pos_y - direction_y[idx_L], 2));
    distances[1] = sqrt(   pow(player_pos[0] - _pos_x - direction_x[turn], 2)
                         + pow(player_pos[1] - _pos_y - direction_y[turn], 2));
    distances[2] = sqrt(   pow(player_pos[0] - _pos_x - direction_x[idx_R], 2)
                         + pow(player_pos[1] - _pos_y - direction_y[idx_R], 2));

    double min = 3000;
    uint8_t idx_min = 0;
    uint8_t i = 0;
    for(i = 0; i < 3; i++){
      if (distances[i] < min){
        min = distances[i];
        idx_min = i;
      }
    }
    turn = index[idx_min];
  }
  _prev_x = _pos_x;
  _prev_y = _pos_y;
  _pos_x += direction_x[turn];
  _pos_y += direction_y[turn];

  enemy_positions[_id*2] = _pos_x;
  enemy_positions[_id*2 + 1] = _pos_y;

  if(_pos_x < 0 || _pos_y < 0 || _pos_x > _limit_x || _pos_y > _limit_y){
    respawn();
  }

  for(int i = 0; i < 6; i+=2){
    if ( i/2 != _id && check_collision(&enemy_positions[i], 5/*ENEMY_RADIUS*/)){
        respawn();
    }
  }

  double distance = sqrt(   pow(player_pos[0] - _pos_x , 2)
                          + pow(player_pos[1] - _pos_y , 2));

  if (distance < 50){
    int calc_x = player_pos[0] - _pos_x;
    int calc_y = player_pos[1] - _pos_y;
    _bullet_cd--;
    if(_bullet_cd <= 0 && (calc_x != 0 || calc_y != 0)){
      int bullet_dirx = (calc_x != 0)? calc_x/abs(calc_x): 0;
      int bullet_diry = (calc_y != 0)? calc_y/abs(calc_y): 0;
      _bullet_cd = ENEMY_FR;
      Bullet tmp = Bullet(ENEMY_BULLET_SPEED*bullet_dirx,ENEMY_BULLET_SPEED *bullet_diry);
      tmp.set_boundaries(_limit_x, _limit_y);
      tmp.set_initial_pos(_pos_x,_pos_y);
      bullets.Append(tmp);
    }
  }
  iteration++;


}

void Enemy::on_draw(Adafruit_ST7735 * tft){
  // tft->drawRect(_prev_x - 8, _prev_y - 8, 16, 16, ST77XX_BLACK);
  // tft->drawRect(_prev_x - 7, _prev_y - 7, 15, 15, ST77XX_BLACK);

  tft->drawBitmap(_pos_x - 8, _pos_y - 8, &enemy_bitmap[0], 16, 16, ST77XX_RED );
}

void Enemy::set_position(int posx, int posy){
  _pos_x = posx;
  _pos_y = posy;
  enemy_positions[_id*2] = _pos_x;
  enemy_positions[_id*2 + 1] = _pos_y;
}

void Enemy::set_boundaries(int limit_x, int limit_y){
  _limit_x = limit_x;
  _limit_y = limit_y;
}

Enemy& Enemy::operator=(const Enemy& other){
  _id = other._id;
  _pos_x = other._pos_x;
  _pos_y = other._pos_y;

  _limit_x = other._limit_x;
  _limit_y = other._limit_y;
  _destroyed = other._destroyed;

  return *this;
}

int Enemy::operator==(const Enemy& other) const{
  if(_id == other._id)
    return 1;
  return 0;
}

void Enemy::position(int * pos){
  pos[0] = _pos_x;
  pos[1] = _pos_y;
}

void Enemy::destroy(Adafruit_ST7735 * tft){
  // Restore background
  tft->fillRect(_prev_x - 8, _prev_y - 8, 16, 16, ST77XX_BLACK);
  tft->fillRect(_pos_x - 8, _pos_y - 8, 16, 16, ST77XX_BLACK);
}

bool Enemy::destroyed(){
  return _destroyed;
}

void Enemy::respawn(){
  _prev_x = _pos_x;
  _pos_x = analogRead(A4) % _limit_x;
  _prev_y = _pos_y;
  _pos_y = analogRead(A5) % _limit_y;
  enemy_positions[_id*2] = _pos_x;
  enemy_positions[_id*2 + 1] = _pos_y;
  turn = 0;
  iteration = 0;
}

void Enemy::clear(Adafruit_ST7735 * tft){
  tft->fillRect(_prev_x - 9, _prev_y - 9, 17, 17, ST77XX_BLACK);
  tft->fillRect(_pos_x - 9, _pos_y - 9, 17, 17, ST77XX_BLACK);
}
