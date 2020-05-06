#include <XInput.h>
#include <math.h>

const int X = 10;
const int Y = 9;
const int A = 7;
const int B = 8;
const int RB = 12;
const int LB = 11;
const int JB = 6;
const int JV = A1;
const int JH = A0;

void setup()
{
  // Initialize Button Pins
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(RB, INPUT_PULLUP);
  pinMode(LB, INPUT_PULLUP);
  pinMode(JB, INPUT_PULLUP);

  XInput.setJoystickRange(0, 1023); 
  XInput.setAutoSend(false);
  // Initialize Joystick Library
  XInput.begin();
}

// config
bool expo = true;
bool overcooked = true;

void loop()
{
  if (!digitalRead(X) && !digitalRead(JB))
    expo = !expo;
  if (!digitalRead(A) && !digitalRead(JB))
    overcooked = !overcooked;
    
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

  XInput.setButton(BUTTON_START, !digitalRead(JB));
  double h = 1023 - analogRead(JH);
  double v = 1023 - analogRead(JV);

if (expo) 
{
  uint32_t hnorm;
  uint32_t vnorm;

  if (h < 512) 
  {
    h = 512 - h;
    hnorm = exp(h/100)/166.3353696*512;
    hnorm = 512 - hnorm;
  } else {
    h -= 512;
    hnorm = exp(h/100)/166.3353696*512;
    hnorm += 512;
  }

  if (v < 512) 
  {
    v = 512 - v;
    vnorm = exp(v/100)/166.3353696*512;
    vnorm = 512 - vnorm;
  } else {
    v -= 512;
    vnorm = exp(v/100)/166.3353696*512;
    vnorm += 512;
  }

  XInput.setJoystick(JOY_LEFT,hnorm, vnorm);
}
else 
{
  XInput.setJoystick(JOY_LEFT,h, v);
}

  XInput.send();
  delay(10);
}
