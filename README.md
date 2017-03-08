# Thermocycler

For APSC 200

This program can be built and uploaded using [platformIO](http://platformio.org/get-started/cli) using and Arduino MEGA/ATMEGA 2560 Clone.

The simplest way to install platformIO (with python2.7 installed) is:
~~~
pip install platformio
~~~

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
