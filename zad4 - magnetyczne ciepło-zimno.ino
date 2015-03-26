#include <TinkerKit.h>

//piny
int RESET = 8;
int DZWIEK = 9;
int LED = 10;
TKHallSensor hs(I0);

int losowa_wartosc;
long czas_pikniecia = 0;
bool koniec = false;

void setup() {
  //Serial.begin(9600);

  pinMode(RESET, INPUT);
  pinMode(DZWIEK, OUTPUT);
  pinMode(LED,   OUTPUT);

  randomSeed(analogRead(0));
  losowa_wartosc = random(18, 1018);
}

void loop() {
  int wartosc = hs.read();
  //Serial.println(wartosc); 
  //Serial.println(losowa_wartosc);

  int roznica_natezenia = abs(wartosc - losowa_wartosc);
  int roznica_czasu = millis() - czas_pikniecia;
	
  if ((!koniec) && (roznica_czasu > roznica_natezenia)) {
    tone(DZWIEK, 800, 5);
    czas_pikniecia = millis();
  }
	
  if (roznica_natezenia == 0) {
    tone(DZWIEK, 100);
    digitalWrite(LED, HIGH);
    //delay(3000);
    //digitalWrite(LED, LOW);
    //noTone(DZWIEK);
    koniec = true;
  } 
  
  if (digitalRead(RESET) == HIGH) {
    noTone(DZWIEK);
    digitalWrite(LED, LOW);
    losowa_wartosc = random(18, 1018);
    koniec = false;
    delay(1000);
  }
}
