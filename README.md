# MultiLcd Library for Arduino
A third-party Arduino library for bigger LCDs and multiple LCDs

This library let you use multi-controller LCDs (like the 4x40) or a bunch of distinct LCDs as a single LiquidCrystal object: in fact, the API is the same of the wide-known library, except for constructor and .begin() method, and the new ".attach()". 

Once initialization is done, you can drive the designated LCDs (or LCDs controllers) as a single, virtual LCD.
