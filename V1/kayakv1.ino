#include <Encoder.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>

const double pi = 3.1415926535897832384;
double w = 0;
unsigned long prevTime = 0;
const int I = 4000;
float k = 3.67; // typical result from test
float c = 2.80; // typical value for speed constant
long ptime = 0;
double ppower = 0;
bool inMenu = LOW;
int Selected = 0;

double power = 0;
double Speed = 0;
double distancelarge = 0;
double distance = 0;

//Stroke variables
int StrokeRate = 0;
long Stroketime = 0;
bool StrokeRising = LOW;
double StrokePower = 0;
float StrokePrevDist = 0;
float DistancePerStroke = 0;
float calorie = 0;
long runtime = 0;


char* Options[] = {"Timer", "Advanced", "Restart"};
char* Timer[] = {"Time", "On/Off"};
bool timer = LOW;
int timer_time = 60;

char* DataScreens[] = {"Power", "Speed", "Distance", "Cadence"};
char* Advanced[] = {"Set Drag", "Speed const"}; //k and c
byte screen = 2;
byte scroll = 0;


byte arrow[] = {
  0x00,
  0x04,
  0x06,
  0x1F,
  0x06,
  0x04,
  0x00,
  0x00
};

#define LCD_WIDTH 20
#define LCD_HEIGHT 4
LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

#define Encoder_clock_pin 2
#define Encoder_data_pin 5
#define Encoder_button 4

#define alarm 6


// encoder program
Encoder Cmain(Encoder_clock_pin, Encoder_data_pin);
long pos = 0;
long ppos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT);
  pinMode(2, INPUT);
  pinMode(5, INPUT);
  pinMode(alarm, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(3), angVelocity, RISING);

  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, arrow);
  lcd.clear();
  //lcd.write(0);
  refresh(0);
}

void loop() {
  // get position of encoder
  pos = Cmain.read();

  // calculate current power and speed
  power = (k * pow(w, 3)) / 10000;
  Speed = pow((power / c), 0.3333333333333333) * 3.6;
  //Catch for slow speeds
  if (power <= 1) {
    Speed = 0;
  }

  // Calculate Distance with the speed variable and time
  distancelarge += Speed * ((millis() - runtime) / 3.6);
  distance = (distancelarge / 1000000);
  runtime = millis();
  
  //Stroke Rate (Runs only when there is a change in power)
  if(power < StrokePower){ // power falling
    if (StrokeRising == HIGH){//there is a peek detected
      if(millis() - Stroketime >= 300){ // 300ms would give 200strokes/min which should be an error on a paddle machine
        // A valid stroke has occured...
        //Set New variables
        StrokeRate = round(((1000)/(millis()-Stroketime)) * 60);
        DistancePerStroke = (distance - StrokePrevDist)*1000;

        //Set new time and distance
        Stroketime = millis();
        StrokePrevDist = distance;
        
      }
    }
    StrokeRising = LOW; // power is falling so set the variables to show so after any checks
  }else if (power > StrokePower){
    StrokeRising = HIGH;// stroke is rising set so
  }
  StrokePower = power; // constantly has power from previous round. often will be equal if so nothing happends. but when it changes the code is run.

  //Calorie equation
  calorie += (4*(power * (millis() /1000)) + 0.35*(millis()/1000))/4.2;
  


  if ((screen == 2 and abs(power - ppower) >= 10) or (screen == 2 and power < 5 and power != ppower)) { //refresh machine with change in power (which changes all other variables)
    refresh(0); // manual refresh of LCD
    ppower = power;
  }

  // Timer Alarm Code
  if (timer == HIGH and (ptime <= millis() - timer_time * 1000) and (ptime >= millis() - timer_time * 1000 - 400)) { // check if timer is on and the beem should sound
    tone(alarm, 1000); // Send 1KHz sound signal...
  } else if (timer == HIGH and (ptime <= millis() - timer_time * 1000 - 400)) { // check if sound should end... only runs if it should't start
    noTone(alarm); //Stop sound...
    ptime = millis(); // reset ptime to repeat
  }


  menu(); // run menu including scroll and screen change check and refresh

  
  //Serial Display
  Serial.print(w);
  Serial.print(", ");
  Serial.print(millis() - prevTime);
  Serial.print(", ");
  Serial.print(power);
  Serial.print(", ");
  Serial.print(Speed);
  Serial.print(", ");
  Serial.print(distancelarge);
  Serial.print(", ");
  Serial.println(runtime);

  delay(1);

}

void angVelocity() {
  long changeInTime = millis() - prevTime;
  if (changeInTime >= 30) {
    w = 2 * pi * 1000 / (changeInTime);
    prevTime = millis();
  }
  /*
    Serial.println("CHECK:");
    Serial.print(w);
    Serial.print(", ");
    Serial.print(prevTime);
    Serial.print(", ");
    Serial.println(changeInTime);*/
}
