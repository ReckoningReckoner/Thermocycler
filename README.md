# Thermocycler

For APSC 200

This program can be compiled an run using platformIO using and Arduino MEGA/ATMEGA 2560 Clone.
~~~
cd src/
platformio run --target upload
~~~

Unit tests are run like the following:
~~~
cd src/test
mkdir bin
cd bin
cmake
make unittest
./unittest
~~~
Make sure to write '''#define TESTING''' in the Interface.h header.
