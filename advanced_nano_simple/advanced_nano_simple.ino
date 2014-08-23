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
int buttonPin1 = 12;
int buttonPin2 = 8;

int pot0 = 0;
int pot1 = 1;
int pot2 = 2;

int button1State = 0; 
int lastButton1State = 0;
int song = -1;
 
long t = 0; 

unsigned int p0 = 0;
unsigned int p1 = 0;
unsigned int delta_T = 0;

int snd = 0; 


void setup () {

  TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to 1 for fast PWM frequency of 31372.55 Hz
 
  pinMode (speakerPin, OUTPUT);

  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);

  pinMode (pot0, INPUT);
  pinMode (pot1, INPUT);
  pinMode (pot2, INPUT);

}
 
void loop () {
  
// read the state of the button into a local variable:
  button1State = digitalRead(buttonPin1);
  
  if (button1State != lastButton1State && button1State == HIGH) {
    // if the state has changed, increment the counter
    song++;
    t = 0; 
    delay(20); 
    
    if (song > 6) {
      song = 0;
    } 
      
   
  } 
  
  lastButton1State = button1State;
    
  switch(song) {
    
  case 0: // test0
 
    p0 = (analogRead(pot0)>>4);
    p1 = (analogRead(pot1)>>4);
    delta_T = (1023 - (analogRead(pot2)));
    
    snd = t * ((t>>3|t>>p0)&70&t>>p1);

    digitalWrite (speakerPin, snd);
    delayMicroseconds(delta_T+1);
    t++;
    
  break; 

  case 1: // test1
 
    p0 = (analogRead(pot0)>>4);
    p1 = (analogRead(pot1)>>4);
    delta_T = ((1023 - (analogRead(pot2)))>>0);
    
    snd = t*(t^t+(t>>15|1)^(t-(14-(p1/2))^t)>>(10-(pot0/5)));

    digitalWrite (speakerPin, snd);
    delayMicroseconds((delta_T+1));
    t++;
    
  break; 
  
  case 2: // dubStep
 
    p0 = (analogRead(pot0)>>4);
    p1 = (analogRead(pot1)>>4);
    delta_T = ((1023 - (analogRead(pot2)))<<0);
    
    snd = (t|4) * ((t>>p1|t>>11)&p0&t>>3);

    //analogWrite (speakerPin, snd);
    digitalWrite (speakerPin, snd);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
    
  case 3: // a classic
 
    p0 = ((analogRead(pot0)>>5)+0);
    p1 = (analogRead(pot1)>>6);
    delta_T = ((1023 - (analogRead(pot2)))>>0);
     
    snd = t * ((t>>p1|t>>p0)&63&t>>(13>>3));

    analogWrite (speakerPin, snd);
    //digitalWrite (speakerPin, snd);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  case 4: // a single

    p0 = ((analogRead(pot0)>>5)+0);
    p1 = (analogRead(pot1)>>6);
    delta_T = ((1023 - (analogRead(pot2)))>>0);
     
    snd = t * ((t>>6|t>>p0)&77&t>>(p1>>3));

    digitalWrite (speakerPin, snd);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  case 5: // PechBlenda Staayle
 
    p0 = (analogRead(pot0)>>4);
    p1 = (analogRead(pot1)>>4);
    delta_T = ((1023 - (analogRead(pot2)))<<0);
    
    snd = t>>p0&1?t>>17:-t>>p1;

    digitalWrite (speakerPin, snd);
    delayMicroseconds((delta_T+1));
    t++;
    
  break;
  
  }  
 
}

// t * ((t>>3|t>>15)&70&t>>9)
// snd = t>>p2&1?t>>p1:-t>>p0;
// snd = (t|p2) * ((t>>p1|t>>11)&p0&t>>3);
// bitMeat snd = t*(((t>>(12+(p1/2)))|(t>>8))&((p0-(p2/2))&(t>>4)));
// snd = ((((p0*t)/50)*(((p1*t)/50)>>8|t>>9)&((p2*46)/50)&t>>8))^(t&t>>13|t>>6);
 
