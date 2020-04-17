#include "Adafruit_GFX.h"
#include "Adafruit_SPITFT.h"
#include "Adafruit_SPITFT_Macros.h"
#include "gfxfont.h"
#include "Adafruit_HX8357.h"
#include "TouchScreen.h"
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <SPI.h>
#include <SD.h>

/*#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <RF24Network.h>
#include <RF24Mesh.h>*/

#include <Encoder.h>
#include <TimeLib.h>
#define TIME_HEADER  "T"   // Header tag for serial time sync message

#include <EEPROM.h>

struct EEPromMem{
  float dragConst;
  float SpeedConst;
  int inertia;
};







// TFT Chip Select and Reset Pins
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define TFT_LITE 7
uint8_t backlite = 255;

// TFT Touch Screen
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A5  // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin
#define XP 17

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 80
#define TS_MINY 35
#define TS_MAXX 915
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000


Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);


// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


//SD card setup myfile
const int chipSelect = BUILTIN_SDCARD; //use built in SD card for all operations

Encoder Selecter(36, 37);
#define EncoderSwitch 35
#define UseEncoder HIGH
long EncoderPos, PrevEncoderPos;


#define EN 2

#define BUZZER 23
#define FLYWHEEL_PIN 14

#define RF_CE 21
#define RF_CSN 29
#define nodeID 1

//RF24 radio(RF_CE, RF_CSN); // CE, CSN
//RF24Network network(radio);
//RF24Mesh mesh(radio, network);

//colours
#define white 0xFFFF
#define Black 0x0000
#define lightgray 0xCE79
#define LightBlue 0x2599
#define Blue 0x4C73
#define Green 0x1FF4
#define Orange 0xFACA
#define Red 0xC92D
#define DarkGreen 0x0C01
#define DarkOrange 0xB281
#define DarkRed 0x8860




//Variables

long loopRefreshTime = 0;
#define maxW 200;
#define maxWTimeMicro 31426
float w = 0;
uint64_t prevTime = 0; //for attach interrupt
int I =  4000;
float k = 3.67;
float c = 2.80;
long ptime = -1; // alarm timer
bool timer = LOW; // timer on off
int timer_time = 60; // time in secconds of timer
bool PlayTone = LOW;

float power = 0;
float ppower = 0;
float Speed = 0;
float distancelarge = 0;
float distance = 0;
float wPrev = 15;

//Stroke variables
int StrokeRate = 0;
long Stroketime = 0;
float StrokePrevDist = 0;
float DistancePerStroke = 0;
float StrokeData[4];
uint32_t StrokeTimes[4];
float StrokePeak = 0;
float StrokePrevPeak = 0;
bool StrokeBeginFound = LOW;

float calorie = 0;

long runtime = 0;// for variables
//bluetooth
//char BTchar = "";


//Menu 
bool Displayed = LOW;
int screen = 0;
byte menuScroll = 0;
bool inMenu = HIGH;
bool Refresh = LOW;

bool Record = LOW;
int recordFreq = 4;
long recordTime = 0;
bool RecordPause = LOW;
byte Selected = 0; // for Encoder
byte PageMax = 3; // start on screen 0 so max is 4 options / 3 from 0

long RefreshTime = 0;


// Sessions
#define MAX_SESSIONS 5 // can be higher but for the sake of storage is low
char SessionName1[16];
char SessionName2[16];
char SessionName3[16];
char SessionName4[16];
char SessionName5[16];
byte TotalSessions = 0;
uint16_t SessionLengths[MAX_SESSIONS];
boolean SessionUnits[MAX_SESSIONS];

bool RunningSession = LOW;
bool RunningSessionPause = LOW;
bool setupSession = LOW;
byte RunningSessionNum = 0;
uint16_t RunningSessionLine = 0;
long innitLengthCovered = 0;
uint16_t lengthtoCover = 0;
bool currentUnit = LOW;
bool currentEffort = LOW;
bool SessionChangeValues = LOW; //Set to high when they change so the screen does not change them constantly



//GRAPH
long graphTime = 0;
#define GraphFPS 10
#define GraphTime 3
float graphData[GraphFPS*GraphTime];
int displayGraph = 1;



//======================================
//SETUP
//======================================

void setup() {
    Serial.begin(38400);// USB communication
    Serial1.begin(9600);//Bluetooth communication

    // TFT
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(HX8357_BLACK);
    analogWrite(TFT_LITE, backlite);
    uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
    Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDMADCTL);
    Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDCOLMOD);
    Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDDIM);
    Serial.print("Image Format: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDDSDR);
    Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

    //SET TIME
    setSyncProvider(getTeensy3Time);

    delay(100);
    if (timeStatus()!= timeSet) {
      Serial.println("Unable to sync with the RTC");
      tft.println("Unable to sync with Real Time Clock");
      tft.setCursor(0,0); tft.print("NO REAL TIME CLOCK \n The Real Time clock was unable to sync meaning there is a fault in your computers processor");
      
      delay(1000);
    } else {
      Serial.println("\n =====================================\nRTC has set the system time\n =====================================");
    }

    
    //Pins

    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);
    
    pinMode(BUZZER, OUTPUT);

    pinMode(EncoderSwitch, INPUT);

    //SD card
    if (!SD.begin(chipSelect)) {
      Serial.println("SD initialization failed!");
      tft.setCursor(0,0); tft.print("NO SD CARD\n possibly a card larger then 32GB or not in Fat32 format, other possibilites include broken card or no card\n \n go to perrylewis.com for info on sd cards and other information about your paddle monitor");
      return; //exit program and stop all.
    }
    
    
    Serial.println("\n =====================================\nSD initialization done\n =====================================");
    if (!Serial1){
      tft.setCursor(0,0);
      tft.print("NO BLUETOOTH\n the bluetooth card could not communicate with the processor");
    }

    //Set flywheel pin as input and attach the interupt
    pinMode(FLYWHEEL_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(FLYWHEEL_PIN), angVelocity, RISING);
    
    // READ EEPROM MEMORY
    EEPromMem ConstMem;
    EEPROM.get(0, ConstMem);
    Serial.println("\n =====================================\nConstants retreived\n =====================================");
    k = ConstMem.dragConst;
    c = ConstMem.SpeedConst;
    I = ConstMem.inertia;


    //RF Device
    //mesh.SetNodeID(nodeID);
    //mesh.begin();
    

    
    //Refresh the screen
    tft.setFont(&FreeSans12pt7b);
    refresh(HIGH);
    
    //Set Clock if available Threw Serial
    if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
      Serial.print(hour());Serial.print(":");Serial.print(minute());Serial.print(":");Serial.print(second());
      
    }
  }

    
    
}
//=====================================
// END STARTUP
//=====================================


//=====================================
// MAIN LOOP
//=====================================
void loop() {
  if (millis() - loopRefreshTime >= 1){ //Ensures some time has passed
    //CALCULATE VARIABLES
    //readDataDebug();
    
    variables();

    // UPDATE micros64 to ensure no Overflow is missed
    micros64();
    
    //RUN TIMER
    Timer();
  
    //RUN MENU
    menuInteract();
  
    //DATA RECORDER
    if (Record == HIGH and millis() >= recordTime + (1000/recordFreq)){ //Set to record at correct frequency
      recordData();
      recordTime = millis();
    }
    
    // Refresh Screens when needed
    if ((screen == 1 or screen == 8) and millis() >= RefreshTime + 1000){ //Refresh every second for screens with time on them
      RefreshTime = millis(); refresh(LOW);
    }else if(screen == 1 and StrokePeak != StrokePrevPeak){ //Refresh for every detected stroke
      refresh(LOW);
      StrokePrevPeak = StrokePeak;
    }
    
    // Write any data recived from BT to Serial
    if (Serial1.available()){
      Serial.write(Serial.read());
    }

    //Session
    if (RunningSession){
      sessionRun(RunningSessionNum);
    }
    if (millis()-graphTime >= 1000/GraphFPS and (screen == 1 or screen == 15)){ //update graphs at the FPS set
      graphs(LOW);
      graphTime = millis();
    }
    
    //Serial.println(millis()-loopRefreshTime);
    
    loopRefreshTime = millis();
  }//END LOOP EVERY 1MS

  
  //LOOP EVERY TIME


  //END LOOP EVERY TIME
} 
// ========================================
// END LOOP
// ========================================

void angVelocity() {
  long changeInTime = micros64() - prevTime;
  if (changeInTime >= maxWTimeMicro) {
    w = 2 * PI * 1000000 / (changeInTime);
    prevTime = micros64();
  }
  //Serial.println(w);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */

unsigned long processSyncMessage() { // UNDERSTAND TIME SENT FROM COMPUTER
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

uint64_t micros64() { // MICROSECOND ROLLOVER CONTROLLER
    static uint32_t low32, high32;
    uint32_t new_low32 = micros();
    if (new_low32 < low32) high32++; // by comparison so that catches ar found
    low32 = new_low32;
    return (uint64_t) high32 << 32 | low32;
}
