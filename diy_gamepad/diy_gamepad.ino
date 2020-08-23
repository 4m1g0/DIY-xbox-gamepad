#include <XInput.h>
#include <math.h>

const int X = 10;
const int Y = 9;
const int A = 7;
const int B = 8;
const int RB = 12;
const int LB = 11;
const int RT = A3;
const int LT = A2;
const int JB1 = 6;
const int JV1 = A1;
const int JH1 = A0;
const int JB2 = 5;
const int JV2 = A5;
const int JH2 = A4;


const int LEFT = 13;
const int RIGHT = 3;
const int UP = 4;
const int DOWN = 2;

void setup()
{
  // Initialize Button Pins
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(RB, INPUT_PULLUP);
  pinMode(LB, INPUT_PULLUP);
  pinMode(JB1, INPUT_PULLUP);
  pinMode(JB2, INPUT_PULLUP);

  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);

  XInput.setJoystickRange(0, 1023); 
  XInput.setTriggerRange(215, 900); 
  XInput.setAutoSend(false);
  // Initialize Joystick Library
  XInput.begin();
}

// config
bool expo = false;
bool overcooked = true;
bool flightSim = false;

void loop()
{
  if (!digitalRead(X) && !digitalRead(JB1))
  {
    expo = !expo;
    delay(100);
  }
    
  if (!digitalRead(A) && !digitalRead(JB1))
  {
    overcooked = !overcooked;
    delay(100);
  }
    
  if (!digitalRead(Y) && !digitalRead(JB1))
  {
    flightSim = !flightSim;
  }
    
  XInput.setButton(BUTTON_X, !digitalRead(X));
  XInput.setButton(BUTTON_Y, !digitalRead(Y));
  XInput.setButton(BUTTON_A, !digitalRead(A));
  
  if (overcooked)
    XInput.setButton(BUTTON_B, !digitalRead(RB));
  else 
    XInput.setButton(BUTTON_B, !digitalRead(B));
    
  XInput.setButton(BUTTON_LB, !digitalRead(LB));
  
  if (overcooked)
    XInput.setButton(BUTTON_RB, !digitalRead(B));
  else
    XInput.setButton(BUTTON_RB, !digitalRead(RB));

  XInput.setButton(BUTTON_START, !digitalRead(JB1));
  XInput.setButton(BUTTON_R3, !digitalRead(JB2));
  
  XInput.setButton(DPAD_UP, !digitalRead(UP));
  XInput.setButton(DPAD_DOWN , !digitalRead(DOWN));
  XInput.setButton(DPAD_LEFT , !digitalRead(LEFT));
  XInput.setButton(DPAD_RIGHT  , !digitalRead(RIGHT ));
  
  double hl = 1023 - analogRead(JH1);
  double vl = 1023 - analogRead(JV1);

if (expo) 
{
  uint32_t hnorm;
  uint32_t vnorm;

  if (hl < 512) 
  {
    hl = 512 - hl;
    hnorm = exp(hl/100)/166.3353696*512;
    hnorm = 512 - hnorm;
  } else {
    hl -= 512;
    hnorm = exp(hl/100)/166.3353696*512;
    hnorm += 512;
  }

  if (vl < 512) 
  {
    vl = 512 - vl;
    vnorm = exp(vl/100)/166.3353696*512;
    vnorm = 512 - vnorm;
  } else {
    vl -= 512;
    vnorm = exp(vl/100)/166.3353696*512;
    vnorm += 512;
  }

  XInput.setJoystick(JOY_LEFT,hnorm, vnorm);
}
else 
{
  XInput.setJoystick(JOY_LEFT,hl, vl);
}

  double hr = analogRead(JH2);
  double vr = 1023 - analogRead(JV2);
  XInput.setJoystick(JOY_RIGHT,hr, vr);


  double lt = analogRead(LT);
  double rt = 1023 - analogRead(RT);
  if (!flightSim)
  {
    XInput.setTrigger(TRIGGER_LEFT, lt);
    XInput.setTrigger(TRIGGER_RIGHT, rt);
  }
  else 
  {
    double ruder = 512.0f - lt + rt;
    XInput.setTrigger(TRIGGER_LEFT, ruder);
  }
  

  XInput.send();
  delay(10);
}
