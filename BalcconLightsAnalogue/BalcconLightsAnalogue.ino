/* Based on code by 
 *  https://learn.sparkfun.com/tutorials/using-artnet-dmx-and-the-esp32-to-drive-pixels/all
 *  Many thanks!
 */


#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include <ArtnetWifi.h>
#include <FastLED.h>

/////////////////
// Wifi settings
/////////////////
const char* ssid = "artnet"; //make dedicated artnet ssid
const char* password = "";

////////////////
// LED settings
////////////////
//For a norma ESP32
//#define REDPIN   25  //pins connected to analog LED R,G,B
//#define GREENPIN 26
//#define BLUEPIN  27

//SHA badje : on the addon 3/4/5 top row

#define REDPIN   33  //pins connected to analog LED R,G,B
#define GREENPIN 16
#define BLUEPIN  17

// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_RED     0
#define LEDC_CHANNEL_GREEN     1
#define LEDC_CHANNEL_BLUE     2

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000


const int numLeds = 1; //A simple strip only has one color
const int numberOfChannels = numLeds * 3; // Total number of channels you want to receive (1 led = 3 channels)
CRGB leds[numLeds];
uint8_t BRIGHTNESS = 255;  //For adjusting master brightness
uint8_t hue;


//////////////////////
// Art-Net settings
/////////////////////
ArtnetWifi artnet;
const int startUniverse = 2; // All single color lamps are in universe 2

// Check if we got all universes
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength = 0;


// connect to wifi – returns true if successful or false if not
boolean ConnectWifi(void)
{
  boolean state = true;
  int i = 0;

  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false;
      break;
    }
    i++;
  }
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}

void initTest()
{
  for (int i = 0 ; i < numLeds ; i++) {
    leds[i] = CRGB(127, 0, 0);
  }
  showAnalogRGB( leds[0]);  //update the LED display
  delay(500);
  for (int i = 0 ; i < numLeds ; i++) {
    leds[i] = CRGB(0, 127, 0);
  }
  showAnalogRGB( leds[0]);  //update the LED display
  delay(500);
  for (int i = 0 ; i < numLeds ; i++) {
    leds[i] = CRGB(0, 0, 127);
  }
  showAnalogRGB( leds[0]);  //update the LED display
  delay(500);
  for (int i = 0 ; i < numLeds ; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  showAnalogRGB( leds[0]);  //update the LED display
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
      //Serial.println("Got a frame!");

  sendFrame = 1;
  // set brightness of the whole strip
  if (universe == 15)
  {
    BRIGHTNESS = data[0];
    showAnalogRGB( leds[0]);  //update the LED display
  }

  // Store which universe has got in
  if ((universe - startUniverse) < maxUniverses) {
    universesReceived[universe - startUniverse] = 1;
  }

  for (int i = 0 ; i < maxUniverses ; i++)
  {
    if (universesReceived[i] == 0)
    {
      //Serial.println("Broke");
      sendFrame = 0;
      break;
    }
  }

  // read universe and put into the right part of the display buffer
  for (int i = 0; i < length / 3; i++)
  {
    int led = i + (universe - startUniverse) * (previousDataLength / 3);
    if (led < numLeds)
      leds[led] = CRGB(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
  }
  previousDataLength = length;

  if (sendFrame)
  {
    showAnalogRGB( leds[0]);  //update the LED display
    // Reset universeReceived to 0
    memset(universesReceived, 0, maxUniverses);
  }
}

void setup()
{
  Serial.begin(115200);
  ConnectWifi();
  artnet.begin();
  pinMode(REDPIN,   OUTPUT);  //setup pins for controlling analog RGB LED
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN,  OUTPUT);
  // Setup timer and attach timer to a led pin
  ledcSetup(LEDC_CHANNEL_RED, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcSetup(LEDC_CHANNEL_GREEN, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcSetup(LEDC_CHANNEL_BLUE, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);

  ledcAttachPin(REDPIN, LEDC_CHANNEL_RED);
  ledcAttachPin(GREENPIN, LEDC_CHANNEL_GREEN);
  ledcAttachPin(BLUEPIN, LEDC_CHANNEL_BLUE);

  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, numLeds).setCorrection(TypicalLEDStrip);
  // FastLED.addLeds<WS2812, dataPin, GRB>(leds, numLeds); // original code
  initTest();

  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);
}

// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}

//Function to update the analog LED display
void showAnalogRGB( const CRGB& rgb) {
  //Note: scale8 is used to adjust values based on BRIGHTNESS

  //Also note, I needed to update this to use 255 minus the rgb
  //value since the LED I am using is common anode.  If your
  //analog RGB LED is common cathode you don't need the "255-" part.
  //analogWrite(REDPIN,   255-scale8(rgb.r, BRIGHTNESS) );  //for common anode
  //analogWrite(GREENPIN, 255-scale8(rgb.g, BRIGHTNESS) );
  //analogWrite(BLUEPIN,  255-scale8(rgb.b, BRIGHTNESS) );
  //analogWrite(REDPIN,   scale8(rgb.r, BRIGHTNESS) );  //for common cathode
  //analogWrite(GREENPIN, scale8(rgb.g, BRIGHTNESS) );
  //analogWrite(BLUEPIN,  scale8(rgb.b, BRIGHTNESS) );
  
  ledcAnalogWrite(LEDC_CHANNEL_RED, scale8(rgb.r, BRIGHTNESS));
  ledcAnalogWrite(LEDC_CHANNEL_GREEN, scale8(rgb.g, BRIGHTNESS));
  ledcAnalogWrite(LEDC_CHANNEL_BLUE, scale8(rgb.b, BRIGHTNESS));
}

void loop()
{
  // we call the read function inside the loop
  artnet.read();
}
