# ArduinoPortScanner
Detect and report the port's status of Arduino, with a LCD shield working on its top!

It manipulates three AVR's internal registers.  (Arduino's pin name -> AVR register's name(see the sketch.))
// D0..7 -> DDRD,   D8..13 -> DDRB,  D14(A0)..D19(A5) -> DDRC.   1 is output, 0 is input.
