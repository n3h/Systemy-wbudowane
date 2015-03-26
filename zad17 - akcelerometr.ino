#include <TinkerKit.h>

//piny
TKAccelerometer accelerometer(I0, I1);
int PRZYCISK = 2;
int LED1 = 9;
int LED2 = 10;

// wartosci z czujnika przypieszenia
int odczytX = 0;
int odczytY = 0;
bool ruch = false;

//
int poprzedniX = 0;
int poprzedniY = 0;
int stanX = 0;
int stanY = 0;

int maxX = 0;
int maxY = 0;

int stanPrzycisku = 0;

int szukanyX;
int szukanyY;

bool koniecGry = true;

int blad = 35;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  pinMode(PRZYCISK, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  
  if (koniecGry) {
    szukanyX = random(256);
    szukanyY = random(256);
    
    analogWrite(LED1, szukanyX);
    analogWrite(LED2, szukanyY);
  
    delay(1500);

    koniecGry = false;
    
    stanX = 0;
    stanY = 0;
    poprzedniX = accelerometer.readX();
    poprzedniY = accelerometer.readY();
  }
  
  stanPrzycisku = digitalRead(PRZYCISK);
  if (stanPrzycisku == HIGH) {     
    analogWrite(LED1, szukanyX);
    analogWrite(LED2, szukanyY);
  } else {
    analogWrite(LED1, stanX);
    analogWrite(LED2, stanY);
  }
  
  odczytX = accelerometer.readX(); 
  odczytY = accelerometer.readY(); 
  
  if (!ruch && (odczytX - poprzedniX >= 8 || odczytY - poprzedniY >= 8)) {
    ruch = true;
    maxX = odczytX;
    maxY = odczytY;
  } else if (ruch == true) {
    if (maxX < odczytX) maxX = odczytX;
    if (maxY < odczytY) maxY = odczytY;
    if (poprzedniX - odczytX <= 1 && poprzedniY - odczytY <= 1) {
      ruch = false;
      maxX = map(maxX, 480, 980, 0, 255);
      maxY = map(maxY, 480, 980, 0, 255);
      stanX = (stanX + maxX) % 256;
      stanY = (stanY + maxY) % 256;
      maxX = 0;
      maxY = 0;
    }
  }
  
  if (abs(szukanyX - stanX) < blad && abs(szukanyY - stanY) < blad) {
    Serial.println("koniec");
    koniecGry = true;
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    delay(400);
    analogWrite(LED1, 255);
    analogWrite(LED2, 255);
    delay(400);
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    delay(400);
    analogWrite(LED1, 255);
    analogWrite(LED2, 255);
    delay(400);
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    delay(400);
  }
  
  poprzedniX = odczytX;
  poprzedniY = odczytY;
  
  Serial.print("X = ");                       
  Serial.println(odczytY);   
  Serial.print("Y = ");                       
  Serial.println(odczytY);     

  //Serial.println("X = ");                       
  //Serial.print(abs(szukanyX - stanX));   
  //Serial.println("Y = ");                       
  //Serial.print(abs(szukanyY - stanY));    
}

