# BalCConLOC
BalCCon Lights Operation Center


## Esthetics and vision
Tubes, pipes and ducts, with moving, pulsating content going in and out of walls, connecting the important parts of the event together. Suggesting a massive and complex machinery hidden and uncharted behind the surface.
Inspired by the vision of Janus from Pushing Ice by Alistair Reynolds ( https://www.goodreads.com/book/show/89186.Pushing_Ice )
Light diffusing solution inspired by things seen at CCCamp2019 like : https://pbs.twimg.com/media/ECjMEaqWwAE3QXV.jpg 


## Technical setup
Light are controlled using DMX512 protocol, over ArtNet / WiFi, on ESP32 micro-controllers and LEDS strips. Smart LED strips (APA10) are controlled using FASTLed library directly using SPI. Nonprogrammable LEDs are controled using a GPIO PWM FASTLed warapper and MOSFETs.

## Hardware
Owned by Igor
- Lenovo X121e laptop as main controller
- GL-MT300A router for testing
- 12 x 90 adressable RGB LED ledstrip + SHA2017 badge controller,  3m, DMX universe 1
- 2 x nonadressable RGB strip + SHA2017 badge controller, ~3m, DMX universe 2
- 30cm Disco ball + motor
- 3W 3 degree white PinSpot
- Red & Green laser pattern projector
- RGBW food light, non-DMX
- 20 x SHA2017 badge controllers
- 6 MOSFET RGB controllers, self built, based on IRL540N
- 5V, 10A power supply, weatherproofed
- 2x 12V 5A power supply
- ~12 X 5V, 3.5A  KOPPLA USB power supplies
- $number of 5V 2A usb power supplies 

Owned by BalCCon orga
- 11 X  dumb RGB strp + cables to make the logo
- 12V, ??A, Power supply  for the logo 
- Several RGB strips, mainly non-programmable
- ...

## Files relevant for the BalCCon LOC. Plans, code, etc.
- Lighting plan: lightsPlan2019.svg
- ESP32 code for the Artnet DMX LEDstrip controllers
- Code for producing ledcat input  (coming soon)
- QLC+ fixture definitions, effects and mixing panel : balccon2k19.qxw


## Software tools and libraries used  :
- Fedora 30 for the laptop : https://getfedora.org/
- Q Lights Controller+ : https://www.qlcplus.org/
- ledcat : https://github.com/polyfloyd/ledcat
- ArtnetWifi library : https://github.com/rstephan/ArtnetWifi/
- FASTLed library : https://github.com/FastLED/FastLED
- Arduino IDE : https://www.arduino.cc/


