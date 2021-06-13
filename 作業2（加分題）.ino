// C++ code
//
#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262

int melody[] = {
  NOTE_C4,
  NOTE_G3,
  NOTE_G3,
  NOTE_A3,
  NOTE_G3,
  0,
  NOTE_B3,
  NOTE_C4
};

int melody2[] = {
  NOTE_C3,
  NOTE_C3,
  NOTE_G3,
  NOTE_G3,
  NOTE_A3,
  NOTE_A3,
  NOTE_G3
};

int noteDurations[] = {
  4,8,8,4,4,4,4,4
};

int noteDurations2[] = {
  4,4,4,4,4,4,2
};

int thisNote = -1, noteDuration = 0, thisNote2 = -1;
long previousTime = 0,
     presentTime = 0,
     pauseBetweenNotes = 0;

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int button = 2;
int button2 = 3;

byte previousState = 1, presentState = 1, patternNum = 0;
byte previousState2 = 1, presentState2 = 1, songNum = 0;

byte colDataMatrix[8] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111
};

byte rowDataMatrix[8] = {
  B00000000,
  B00000000,
  B00100100,
  B00000000,
  B01000010,
  B00100100,
  B00011000,
  B00000000
};
byte rowDataMatrix2[8] = {
  B00000000,
  B00000000,
  B00100100,
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B00000000
};       
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT); 
  pinMode(button,INPUT_PULLUP); 
  pinMode(button2,INPUT_PULLUP); 
}

void checkToPlay(){
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes){
    thisNote++;
    if(thisNote >= 8){
      thisNote = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }
    else{
      noteDuration = 500/ noteDurations[thisNote];
      tone(9, melody[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}

void checkToPlay2(){
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes){
    thisNote2++;
    if(thisNote2 >= 7){
      thisNote2 = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }
    else{
      noteDuration = 500/ noteDurations2[thisNote2];
      tone(9, melody2[thisNote2], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}
void Button(){
  presentState = digitalRead(button);
  if(presentState == 0 && previousState == 1){
    patternNum ++;
    if(patternNum > 1){
      patternNum = 0;
    }
  }
  delay(2);
  previousState = presentState;
}
void Button2(){
  presentState2 = digitalRead(button2);
  if(presentState2 == 0 && previousState2 == 1){
    songNum ++;
    if(songNum > 1){
      songNum = 0;
    }
  }
  delay(2);
  previousState2 = presentState2;
}
void loop() {
  Button();
  Button2();
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    if(patternNum == 0)
      shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
    else
      shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix2[i]);
    digitalWrite(latchPin,HIGH);
    if(songNum == 0)checkToPlay();
    else checkToPlay2();
    delay(1);
  }
  
}

