# BalCConLOC
_BalCCon Lights Operation Center_


Welcome to BalCCon, a SocioCyberPhysical self-organizing entity. We are happy you decided to join its evolution into Uncharted Waters over the next several days. 

In the middle of the facility you will find the *Organic binary human-machine inteRaction GenerAtor*  (ORGA) core, the coordinating hub of the entity. From there, many connector radiate carrying data, knowledge and wisdom in all of it multicolored and dynamic beauty. Ducts are going in and out of walls, connecting the core parts of the entity together with the underlying complex technical, social and environmental infrastructure of outside world, hidden and uncharted behind the surface. 

The ORGA  draws its main computing power from the  *BAsic Large Community Computing Organizational uNit* (BALCCON) situated in the *Hacker Area* motherboard. Primary visual output is the distributed and up-cycled *Man-machine Terminal Write-only Landscape* (MATEWall). To the right is the main physical input-output  connector and to the left of the ORGA and MATEWall is the *The neurAl network Logic Training aSembly* (TALKS). 

In the likely case that the TALKS cause a neural stack overload, you will find *the  neural reBalancing ARray* (BAR) right next door.  Please dump excess core only in the designated areas. We wish you a pleasant participation in the collective computing process! 

## How to play with the light
During BalCCon2k19 you have the following options :
1 Come to the LOC desk, use the controller GIU
1 Use the WEB GUI : http://192.168.1.105:9999/
1 Use ledcat tool. Come ask for the login credentials, ssh into the controller, upload your program that generates a *binary string* of RGB values or the correct length to standard output, set the protocol and geometry (see below) and run: $yourProgram | ./ledcat --geometry 90 artnet -b --universe 1


## Lights plan and DMX setup

- Universe 1 : Programmable RGB LED strips of 90 LEDS, DMX addresses 1-270 
- Universe 2 : Non-programmable RGB strips, various lengths, mainly  between 3-5m, DMX address 1-3
- Universe 3 : ORGA core human figure lights, DMX addresses 1/2 human figures, 3 connector between them
- Universe 4 : Logo lights, DMX addresses : 1-5 opposing pairs of legs, 6 chip body

## Technical setup
Light are controlled using DMX512 protocol, over ArtNet / WiFi, on ESP32 micro-controllers and LEDS strips. Smart LED strips (APA10) are controlled using FASTLed library directly using SPI. Non-programmable (analogue) LEDs are controlled using a GPIO PWM FASTLed wrapper and MOSFETs.

## Hardware
Owned by Igor
- Lenovo X121e laptop as main controller
- GL-MT300A router for testing
- 12 x 90 addressable RGB LED ledstrip + SHA2017 badge controller,  3m, DMX universe 1
- 2 x non-adressable RGB strip + SHA2017 badge controller, ~3m, DMX universe 2
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

## Inspiration
- The vision of Janus from Pushing Ice by Alistair Reynolds ( https://www.goodreads.com/book/show/89186.Pushing_Ice )
- Light diffusing solution inspired by things seen at CCCamp2019 like : https://pbs.twimg.com/media/ECjMEaqWwAE3QXV.jpg 

