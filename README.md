# SecurityBot: Home Surveillance Assistant v1

## Description

In the present day, home security typically boils down to home alarms and surveillance cameras. While these methods do often times protect consumers from intruders, many adept criminals can find ways to bypass a home alarm. This leaves the security cameras, which are still passive objects. If the position of these objects are known the criminal beforehand, it is possible to evade the detection of these cameras. The Home Surveillance Assistant (HSA) combats this problem by providing a method of active surveillance. If utilized properly, active surveillance can boost the benefits gained from passive surveillance.

HSA1 is the a base platform for creating active surveillance robots that can be controlled using a mobile device. The primary purpose of HSA1 is to navigate around a household, actively checking for intruders. HSA1 is equipped with a microphone, speaker, and camera to effectively capture evidence of an intruder as well as provide audio feedback remotely if required. By utilizing this repository, we hope to help others build active surveillance robots.

## How It Works

HSA1 consists of one Raspberry Pi 3, one Arduino Uno, two AndyMark NeveRest DC Motors, one Raspberry Pi Camera, two mini servos for controlling camera pan/tilt, a 12V 6000 mAH battery, and a L298N Motor Controller.

The head of HSA1 is a Raspberry Pi 3. This Raspberry Pi 3 both hosts a HTTP server and opens a websocket, allowing external devices to communicate with the Raspberry Pi. These commands are sent as standard HTTP requests by an Android application. You must login to utilize the application. Once these commands are received, the Raspberry Pi sends commands to the Arduino through a USB Serial interface. The Arduino is connected to the motor controller and the pan/tilt servos. Once the Arduino receives the command, it parses it and sends commands to either the DC Motor or the pan/tilt servo motors.

The mobile application uses Ionic Framework for quick prototyping, ease of use, and great compatibility with our server. The Arduino code was uploaded using [PlatformIO](http://platformio.org/), allowing us to utilize external libraries easily, including the low-level [Atlasbuggy](https://github.com/AtlasBuggy/AtlasbuggyLowLevel/tree/master/Arduino/libraries/Atlasbuggy) library. This Arduino library allows us to easily connect with the Raspberry Pi 3, which utilizes the main [Atlasbuggy](https://github.com/Atlasbuggy/atlasbuggy) library.

The server is based off waveform80's wonderful [pistreaming](https://github.com/waveform80/pistreaming) library.

## Installation

In order run HSA1, you need to have a following dependencies installed. First off, you will need to install Python 3.5. This is because Python 3.4 is installed on Raspbian by default, but the Atlasbuggy utilizes asyncio, a feature added in Python 3.5+. To do this, you will need to make it from source. First we install the dependencies:

```bash
$ sudo apt-get install build-essential libc6-dev
$ sudo apt-get install libncurses5-dev libncursesw5-dev libreadline6-dev
$ sudo apt-get install libdb5.3-dev libgdbm-dev libsqlite3-dev libssl-dev
$ sudo apt-get install libbz2-dev libexpat1-dev liblzma-dev zlib1g-dev
```

Then, we can download the tarball and make from source:

```bash
$ wget https://www.python.org/ftp/python/3.5.2/Python-3.5.2.tgz
$ tar -zxvf Python-3.5.2.tgz
$ cd Python-3.5.2
$ ./configure
$ make -j4
$ sudo make altinstall
```
This may take some time to complete, since the Raspberry Pi has a fairly slow processor speed of 1 GHz with only 1 GB of DDR2 RAM.

After we have that out of the way, we can install the project dependencies. First you will need picamera in order to get access to the Raspberry Pi Camera connected directly to the Raspberry Pi.

```bash
$ sudo pip3.5 install picamera
```

You will also need pyserial to allow for easy communication through the USB Serial Interface.

```bash
$ sudo pip3.5 install pyserial
```

You will also need w4py for the creation of the websocket and HTTP server.

```bash
$ sudo pip3.5 install w4py
```

And that's it! Assuming you have the hardware put together, you should have all you need to run HSA1! To run the robot and the server, simply run the following command:

```bash
$ python3 runner.py
```

## References

[Atlasbuggy](https://github.com/AtlasBuggy/atlasbuggy) - Software framework written in Python for creating robots.
[pistreaming](https://github.com/waveform80/pistreaming) - A little demo of streaming the Pi's camera to web browsers
