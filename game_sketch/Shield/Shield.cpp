#include <Shield.h>

Shield::Shield(int posx, int posy){
  _pos_x = posx;
  _pos_y = posy;
}

Shield::~Shield(){

}

void Shield::position(int * pos){
  pos[0] = _pos_x;
  pos[1] = _pos_y;
}

void Shield::on_draw(Adafruit_ST7735 * tft){
  // for(int idx = 0; idx< 512; idx+=2){
  //
  //   uint16_t colorUpper = pgm_read_word(&shield_data[idx]);
  //   uint16_t color = (colorUpper << 8) | pgm_read_word(&shield_data[idx + 1]);
  //   tft->drawPixel(_pos_x - 8 + (idx/2)%16, _pos_y - 8 + (idx/2)/16, color);
  // }
  tft->drawBitmap(_pos_x - 8, _pos_y - 8, &shield_bitmap[0], 16, 16, ST77XX_WHITE );


}

void Shield::pickup(Adafruit_ST7735 * tft){
  //reset background
  for(int idx = 0; idx< 512; idx+=2){
    tft->drawPixel(_pos_x - 8 + (idx/2)/16, _pos_y - 8 + (idx/2)%16, ST77XX_BLACK);
  }

}

int Shield::operator==(const Shield& other) const {
  if(_pos_x != other._pos_x || _pos_y != other._pos_y)
    return 0;
  return 1;
}
