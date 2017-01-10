#ifndef MultiLcd_h
#define MultiLcd_h

//#define MULTILCD_DEBUG

#include "Arduino.h"
#include "LiquidCrystal.h"

#define TO_RIGHT 0
#define TO_LEFT 1

class MultiLcd : public Print{
  using __Direction = bool;
  
  private:
    struct  __Position    {uint8_t col; uint8_t row;};
    struct  __Dimension   {uint8_t cols; uint8_t rows;};

    LiquidCrystal*  _lcds[8];
    __Position      _cur_pos         = {0, 0};
    __Position      _cur_lcd_pos     = {0, 0};
    __Position      _cur_matrix_pos  = {0, 0};
    __Dimension     _char_dim        = {0, 0};
    __Dimension     _lcd_dim         = {0, 0};
    __Dimension     _matrix_dim      = {0, 0};
    __Direction     _dir             = TO_RIGHT; //left-to-right, default
    byte            _num_of_lcds     = 0;
    bool            _blink_status    = false;
    bool            _cursor_status   = false;
    byte            _cur_lcd_index   = 0;
    
    void    _blink();
    void    _cursor();
    void    _advanceCursor();
    
  public:
    #ifdef MULTILCD_DEBUG           //###############################
    void debugStartup(byte line);   //####### DEBUG METHODS #########
    void debugSerial(byte line);    //#######   DON'T USE   #########
    #endif                          //###############################
    
    void attach(LiquidCrystal&);
    void begin(byte lcd_cols, byte lcd_rows, byte matrix_cols, byte matrix_rows, uint8_t charsize = LCD_5x8DOTS);
    
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row); 
       
    void autoscroll();
    void blink();
    void cursor();
    void display();

    void noAutoscroll();    
    void noBlink();
    void noCursor();
    void noDisplay();
    
    void scrollDisplayLeft();
    void scrollDisplayRight();
    
    void leftToRight();
    void rightToLeft();
    
    void createChar(uint8_t, uint8_t[]);
    void command(uint8_t);
    
    size_t MultiLcd::write(uint8_t value);
};

#endif // MultiLcd_h
