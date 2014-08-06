/*
 * LED Experiments
 * -----------------
 *
 * Trying out HSI and easing with LEDs.
 *
 * Erin RobotGrrl
 * robotgrrl.com
 * Tuesday, August 5th, 2014
 *
 */

#include <math.h>
#include <Streaming.h>


uint8_t r_pin = 9;
uint8_t g_pin = 10;
uint8_t b_pin = 11;

int rgb[3];


void setup() {
  Serial.begin(9600);

  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  
  digitalWrite(r_pin, LOW);
  digitalWrite(g_pin, LOW);
  digitalWrite(b_pin, LOW);

  Serial << "Hello everyone!" << endl;
}


void loop() {
  
  // uncomment the following test blocks to try them out
  
  // test 1
  // cycle around the colour wheel
  
  for(int i=0; i<360; i++) {
    setLedHSI((float)i, 1.0, 0.5);
    delay(10);
  }
  
  
  
  // test 2
  // start at warm magenta, and ease into warm green
  /*
  setLedHSI(315.0, 1.0, 0.5);
  
  for(int i=0; i<100; i++) {
    float newHue = easeInCubic((float)i, 315.0, (105.0-315.0), 100);
    setLedHSI(newHue, 1.0, 0.5);
    delay(10);
  }
  setLedHSI(105.0, 1.0, 0.5);
  */
  
  
  // test 3
  // ease in and out from warm green to warm blue
  /*
  setLedHSI(105.0, 1.0, 0.5);
  
  for(int i=0; i<100; i++) {
    float newHue = easeInOutCubic((float)i, 105.0, (255.0-105.0), 100);
    setLedHSI(newHue, 1.0, 0.5);
    delay(10);
  }
  setLedHSI(255.0, 1.0, 0.5);
  */
  
  
  // test 4
  // ease in & out (back) from mid blue to mid yellow
  /*
  setLedHSI(240.0, 1.0, 0.5);
  
  for(int i=0; i<100; i++) {
    float newHue = easeInOutBack((float)i, 240.0, (60.0-240.0), 100);
    setLedHSI(newHue, 1.0, 0.5);
    delay(10);
  }
  setLedHSI(60.0, 1.0, 0.5);
  */
  
  
  // test 5
  // ease out (bounce) from cool blue to orange
  /*
  setLedHSI(225.0, 1.0, 0.5);
  
  for(int i=0; i<100; i++) {
    float newHue = easeOutBounce((float)i, 225.0, (30.0-225.0), 100);
    setLedHSI(newHue, 1.0, 0.5);
    delay(10);
  }
  setLedHSI(30.0, 1.0, 0.5);
  */
  
  
}


// This function is by Brian Neltner from Saikoled
// http://blog.saikoled.com/post/43693602826/why-every-led-light-should-be-using-hsi-colorspace
void hsi2rgb(float H, float S, float I, int *rgb) {
  
  int r, g, b;
  H = fmod(H,360); // cycle H around to 0-360 degrees
  H = 3.14159*H/(float)180; // Convert to radians.
  S = S>0?(S<1?S:1):0; // clamp S and I to interval [0,1]
  I = I>0?(I<1?I:1):0;
    
  // Math! Thanks in part to Kyle Miller.
  if(H < 2.09439) {
    r = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    g = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    b = 255*I/3*(1-S);
  } else if(H < 4.188787) {
    H = H - 2.09439;
    g = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    b = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    r = 255*I/3*(1-S);
  } else {
    H = H - 4.188787;
    b = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
    r = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    g = 255*I/3*(1-S);
  }
  
  rgb[0]=r;
  rgb[1]=g;
  rgb[2]=b;
  
}


void setLedHSI(float H, float S, float I) {
 
  hsi2rgb(H, S, I, rgb);
    
  analogWrite(r_pin, rgb[0]);
  analogWrite(g_pin, rgb[1]);
  analogWrite(b_pin, rgb[2]);
  
}



/*
 * These are the Easing functions, by Robert Penner
 *
 * A nice online example can be found here:
 * http://easings.net/
 *
 * Based on these ports:
 * http://www.kirupa.com/forum/showthread.php?378287-Robert-Penner-s-Easing-Equations-in-Pure-JS-(no-jQuery)
 * https://github.com/jesusgollonet/ofpennereasing/blob/master/PennerEasing/
 *
 * changeInValue is endValue-startValue
 */


float easeInCubic(float currentIteration, float startValue, float changeInValue, float totalIterations) {
  return changeInValue * pow(currentIteration/totalIterations, 3) + startValue;
}


float easeOutCubic(float currentIteration, float startValue, float changeInValue, float totalIterations) {
  return changeInValue * ( pow(currentIteration / totalIterations - 1, 3) + 1 ) + startValue;
}


float easeInOutCubic(float currentIteration, float startValue, float changeInValue, float totalIterations) {
  
  if( (currentIteration /= totalIterations / 2) < 1 ) {
    return changeInValue / 2 * pow(currentIteration, 3) + startValue;
  }
  return changeInValue / 2 * (pow(currentIteration-2, 3) + 2) + startValue;
  
}


float easeInOutBack(float currentIteration, float startValue, float changeInValue, float totalIterations) {
  
  float s = 1.70158f;
  
  if( (currentIteration /= totalIterations / 2) < 1 ) {
    return changeInValue / 2 * ( currentIteration * currentIteration * ( ( (s *= 1.525) + 1) * currentIteration-s) ) + startValue;
  }
  float postFix = currentIteration-=2;
  return changeInValue / 2 * ( postFix * currentIteration * ( ( (s *= 1.525) + 1) * currentIteration+s) + 2 ) + startValue;
  
}


float easeOutBounce(float currentIteration, float startValue, float changeInValue, float totalIterations) {
  
  float postFix = 0.0f;
  float s = 7.5625;
  
  if( (currentIteration /= totalIterations) <  (1.0/2.75) ) {
    
    return changeInValue * (s * currentIteration * currentIteration) + startValue;
  
  } else if( currentIteration < (2.0/2.75) ) {
    
    postFix = currentIteration -= (1.5/2.75);
    return changeInValue * ( s * postFix * currentIteration + 0.75 ) + startValue;
  
  } else if( currentIteration < (2.5/2.75) ) {
    
    postFix = currentIteration -= (2.25/2.75);
    return changeInValue * (s * postFix * currentIteration + 0.9375) + startValue;
  
  } else {
    
    postFix = currentIteration -= (2.625/2.75);
    return changeInValue * (s * postFix * currentIteration + 0.984375) + startValue;
    
  }
  
}






