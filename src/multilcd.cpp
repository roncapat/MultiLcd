#include "multilcd.h"

void MultiLcd::attach(LiquidCrystal& lcd){
  _lcds[_num_of_lcds++] = &lcd;
}

void MultiLcd::begin(byte lcd_cols, byte lcd_rows, byte matrix_cols, byte matrix_rows, uint8_t charsize = LCD_5x8DOTS){
  _lcd_dim.cols    = lcd_cols;
  _lcd_dim.rows    = lcd_rows;
  _matrix_dim.cols = matrix_cols;
  _matrix_dim.rows = matrix_rows;
  _char_dim.cols   = lcd_cols * matrix_cols;
  _char_dim.rows   = lcd_rows * matrix_rows;
  for (byte i = 0; i<_num_of_lcds; i++) 
    _lcds[i] -> begin(lcd_cols, lcd_rows, charsize);
}

void MultiLcd::clear(){
  for (byte i = 0; i<_num_of_lcds; i++) 
    _lcds[i] -> clear();
  this -> home();
}

void MultiLcd::home(){
  this -> setCursor(0,0);
}

void MultiLcd::noDisplay(){
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> noDisplay();
}

void MultiLcd::display(){
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> display();
}

void MultiLcd::noBlink(){
  _blink_status = false;
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> noBlink();
}

void MultiLcd::_blink(){
  for (byte i = 0; i<_num_of_lcds; i++)
    (i == _cur_lcd_index)  ?  _lcds[i] -> blink()  :  _lcds[i] -> noBlink();
}

void MultiLcd::blink(){
  _blink_status = true;
  _blink();
}

void MultiLcd::noCursor(){
  _cursor_status = false;
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> noCursor();
}

void MultiLcd::_cursor(){
  for (byte i = 0; i<_num_of_lcds; i++)
    (i == _cur_lcd_index)  ?  _lcds[i] -> cursor()  :  _lcds[i] -> noCursor();
}

void MultiLcd::cursor(){
  _cursor_status = true;
  _cursor();
}

void MultiLcd::setCursor(uint8_t col, uint8_t row){
  _cur_pos.row = row;
  _cur_pos.col = col;
  _cur_matrix_pos.row  =  _cur_pos.row / _lcd_dim.rows;
  _cur_matrix_pos.col  =  _cur_pos.col / _lcd_dim.cols;
  _cur_lcd_pos.row     =  _cur_pos.row % _lcd_dim.rows;
  _cur_lcd_pos.col     =  _cur_pos.col % _lcd_dim.cols;
  _cur_lcd_index       =  (_cur_matrix_pos.row * _matrix_dim.cols) + _cur_matrix_pos.col;
  _lcds[_cur_lcd_index] -> setCursor(_cur_lcd_pos.col, _cur_lcd_pos.row);
  if (_blink_status) _blink();
  if (_cursor_status) _cursor();
}

void MultiLcd::noAutoscroll(){
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> noAutoscroll();
}

void MultiLcd::autoscroll(){   
  if (_matrix_dim.cols == 1)              //Disable autoscroll if more than one lcd on a row
    for (byte i = 0; i<_num_of_lcds; i++)
      _lcds[i] -> autoscroll();
}

void MultiLcd::scrollDisplayLeft(){
  if (_matrix_dim.cols == 1)              //Disable autoscroll if more than one lcd on a row
    for (byte i = 0; i<_num_of_lcds; i++)
      _lcds[i] -> scrollDisplayLeft();}

void MultiLcd::scrollDisplayRight(){
  if (_matrix_dim.cols == 1)              //Disable autoscroll if more than one lcd on a row
    for (byte i = 0; i<_num_of_lcds; i++)
      _lcds[i] -> scrollDisplayRight();
}

void MultiLcd::leftToRight(){
  _dir = TO_LEFT;
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> leftToRight();
}

void MultiLcd::rightToLeft(){
  _dir = TO_RIGHT;
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> leftToRight();
}

void MultiLcd::createChar(uint8_t num, uint8_t data[]){
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> createChar(num, data);
}

void MultiLcd::command(uint8_t code){
  for (byte i = 0; i<_num_of_lcds; i++)
    _lcds[i] -> command(code);
}

void MultiLcd::_advanceCursor(){  //Maybe condition ((_cur_pos.col + 1)/_char_dim != 0) is better
  byte target_col, target_row;
  if (_dir == TO_RIGHT){
    if ((_cur_pos.col + 1) == _char_dim.cols)   target_col = 0,                 target_row = _cur_pos.row + 1;
    else                                        target_col = _cur_pos.col + 1,  target_row = _cur_pos.row;
  }
  else {
    if (_cur_pos.col == -1)                     target_col = _char_dim.cols +1, target_row = _cur_pos.row -1;
    else                                        target_col = _cur_pos.col -1,   target_row = _cur_pos.row;
  }
  this -> setCursor(target_col % _char_dim.cols, target_row % _char_dim.rows);
}

inline size_t MultiLcd::write(uint8_t value) {
  _lcds[ _cur_lcd_index ] -> write(value);
  _advanceCursor();
  return 1;
}

//#########################################
//############## DEBUG CODE ###############
//#########################################

#ifdef MULTILCD_DEBUG

void MultiLcd::debugStartup(byte line){
  Serial.println("\nLINE "+String(line));
  Serial.print("_num_of_lcds = ");
  Serial.println(_num_of_lcds);
  Serial.print("_blink_status = ");
  Serial.println(_blink_status);
  Serial.print("_cursor_status = ");
  Serial.println(_cursor_status);
  Serial.print("_char_dim = ");
  Serial.print(_char_dim.cols);
  Serial.print(" * ");
  Serial.println(_char_dim.rows);
  Serial.print("_lcd_dim = ");
  Serial.print(_lcd_dim.cols);
  Serial.print(" * ");
  Serial.println(_lcd_dim.rows);
  Serial.print("_matrix_dim = ");
  Serial.print(_matrix_dim.cols);
  Serial.print(" * ");
  Serial.println(_matrix_dim.rows);
}

void MultiLcd::debugSerial(byte line){
  Serial.println("\nLINE "+String(line));
  Serial.print("_cur_pos = (");
  Serial.print(_cur_pos.col);
  Serial.print(", ");
  Serial.print(_cur_pos.row);
  Serial.println(')');
  Serial.print("_cur_lcd_pos = (");
  Serial.print(_cur_lcd_pos.col);
  Serial.print(", ");
  Serial.print(_cur_lcd_pos.row);
  Serial.println(')');
  Serial.print("_cur_matrix_pos = (");
  Serial.print(_cur_matrix_pos.col);
  Serial.print(", ");
  Serial.print(_cur_matrix_pos.row);
  Serial.println(')');
  Serial.print("_cur_lcd_index = ");
  Serial.println(_cur_lcd_index);
}

#endif
