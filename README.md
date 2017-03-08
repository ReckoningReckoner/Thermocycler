# Thermocycler

For APSC 200

This program can be built and uploaded using platformIO using and Arduino MEGA/ATMEGA 2560 Clone.
~~~
cd src/
platformio run # for building
platformio run --target upload # for uploading
~~~

If on Unix or Linux
~~~
cd src/
make # for building
make upload # for uploading
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
