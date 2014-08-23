/* PCrazy shit 8-bit symphony generator                   */

/*
 * inspired by:
 *  http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
 *  http://countercomplex.blogspot.com.es/2011/10/some-deep-analysis-of-one-line-music.html
 *
 *  try it online:
 *  http://wurstcaptures.untergrund.net/music/
 *
 */

int speakerPin = 3;

int pot0 = A0;
int pot1 = A1;
int pot2 = A2;
 
long t = 0; 

unsigned int p0 = 0;
unsigned int p1 = 0;
unsigned int delta_T = 0;

int snd = 0; 


void setup () {

  TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to 1 for fast PWM frequency of 31372.55 Hz
 
  pinMode (speakerPin, OUTPUT);

  pinMode (pot0, INPUT);
  pinMode (pot1, INPUT);
  pinMode (pot2, INPUT);

}
 
void loop () {
 
    p0 = (analogRead(pot0)>>4);
    p1 = (analogRead(pot1)>>4);
    delta_T = (1023 - (analogRead(pot2)));
    
    snd = (t|4) * ((t>>p1|t>>11)&p0&t>>3);

    digitalWrite (speakerPin, snd);
    delayMicroseconds(delta_T+1);
    t++;
 
}
