#include <LiquidCrystal.h>  // Redundant, multilcd.h itself includes this header.
#include <multilcd.h>       // This is needed

void setup() {
// For this example, we're using a 40*4 LCD. Those large LCDs have two controllers,
// each controlling a 40*2 portion of the LCD. So, we have shared pins, except the
// traditional EN (enable) that is usually replaced by two pins (E0 and E1): they
// are the enable pins, one per controller.
// We instantiate two LiquidCrystal objects, each representing a LCD controller.

//       D7 to D0 ----------|--|--|--|--|--|--|--|
//          E0/E1 -------|  |  |  |  |  |  |  |  |
//             RS ---|   |  |  |  |  |  |  |  |  |
//                   |   |  |  |  |  |  |  |  |  |
  LiquidCrystal l1 (13, 10, 9, 8, 7, 6, 5, 4, 3, 2);
  LiquidCrystal l2 (13, 11, 9, 8, 7, 6, 5, 4, 3, 2);

// Create a MultiLcd instance. No parameters are required.
  MultiLcd my440;

// A bit of theory:
// MultiLcd can handle a generic matrix of phisical LCDs or logical LCDs (controllers).
// Each LiquidCrystal instance, once attached to a MultiLcd, is identified by an index: 0, 1, eccetera. 
// The matrix is filled from the virtual top-left corner to the bottom-right one, from left to right, 
// from the top to bottom, so using the occidental reading conventions.
// Now, the practice: 
// the 4*40 LCD is a matrix of 1 column and 2 rows. We attach the LiquidCrystal instances in this order: 
// first the one controlling the two upper LCD lines, then the second one.

// Assign the LiquidCrystal instances to the MultiLcd instance.
  my440.attach(l1);
  my440.attach(l2);

// Use the special .begin method.
// First two parameters are the same of the LiquidCrystal.begin() method: consider a single LCD and
// write the number of columns, then number of rows. In this example, we have 40 columns and 2 rows.
// Then, the new two parameters: those describe the shape of the matrix. In this example, as discussed
// above, we have 1 column, 2 rows.
  my440.begin(40, 2, 1, 2);

// Now you can use the MultiLcd instance as a normal LiquidCrystal object.
  my440.blink();
  my440.cursor();
  my440.home();
  my440.print(0);
  delay(1000);
  my440.setCursor(39,0);
  my440.print(0);
  delay(1000);
  my440.setCursor(39,3);
  my440.print(0);
  delay(1000);
  my440.setCursor(0,3);
  my440.print(0);
  delay(1000);
  my440.setCursor(16,0);
  my440.print("Hello");
  my440.setCursor(16,1);
  my440.print("World");
  my440.setCursor(16,2);
  my440.print("with");
  my440.setCursor(16,3);
  my440.print("MultiLcd!");
  delay(1000);
}

void loop(){
}
