#include <TinkerKit.h>

TKJoystick joystick(I0, I1);

int x = 0; // min - 9; neutralnie: 504; max 908
int y = 0; // min - 9; neutralnie: 504; max 1021

int lewy = 5;
int gora = 6;
int prawy = 7;
int dol = 8;

int losowaLiczba;
//int ostatnioWylosowano = 5;
unsigned long czasGry = 0;
unsigned long czasPoczatkowy;
unsigned long czasOstatniejOdpowiedzi;
unsigned long roznicaCzasu;

bool koniecGry = false;
bool wczytaneDane = false;
bool pierwszaGra = true;

long punktowZaOdpowiedz = 2000;
long wszystkiePunkty = 0;
long naleznePunkty;

int kierunek();

void setup() {
  pinMode(lewy, OUTPUT);
  pinMode(gora, OUTPUT);
  pinMode(prawy, OUTPUT);
  pinMode(dol, OUTPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  Serial.println("Nowa gra!");
  Serial.println("Podaj czas gry (w milisekundach): ");
  while (!wczytaneDane) {
    if (Serial.available() > 0) {
      czasGry = Serial.parseInt();
      Serial.println(czasGry);
      wczytaneDane = true;
    }
  }
  
  if (pierwszaGra == true) {
  Serial.println("Wyreguluj joystick krecac go w kazdym kierunku ");
    while (kierunek() != 4) { }
      Serial.println("OK!");
      pierwszaGra = false;
  }
  
  Serial.println("Trzy sekundy na przygotowanie sie:");
  delay(500);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("Start!");
  czasPoczatkowy = millis();
  czasOstatniejOdpowiedzi = czasPoczatkowy;
  
  while (!koniecGry) {
    //do {
    while (kierunek() != 4) { } // losowanie tylko, gdy joystick w stanie neutralnym
    losowaLiczba = random(4);
    //} while (losowaLiczba == ostatnioWylosowano);
    //ostatnioWylosowano = losowaLiczba;

    digitalWrite(losowaLiczba + 5, HIGH);
    do { 
        int x2 = joystick.readX();  
        int y2 = joystick.readY(); 
        //Serial.print("Joystick X = " );                       
        //Serial.print(x);   
        //Serial.print("\t Joystick Y = " );                       
        //Serial.println(y);   
      if (millis() - czasPoczatkowy > czasGry) {
        koniecGry = true;
        break;
      }
    } while ((kierunek() != losowaLiczba));    
    digitalWrite(losowaLiczba + 5, LOW);
    if (!koniecGry) {
      roznicaCzasu = millis() - czasOstatniejOdpowiedzi;
      naleznePunkty = punktowZaOdpowiedz - roznicaCzasu;
      if (naleznePunkty < 0)
        naleznePunkty = 0;
      Serial.print("Punkty za runde: ");
      Serial.println(naleznePunkty);
      wszystkiePunkty += naleznePunkty;
    }
    czasOstatniejOdpowiedzi = millis();
  }
  
  Serial.println("Koniec gry!");
  Serial.print("Twoj wynik: ");
  Serial.println(wszystkiePunkty);
  Serial.println("Aby zagrac ponownie wpisz 1");
  
  while (koniecGry) {
    if (Serial.available() > 0) {
      if (Serial.parseInt() == 1) {
        koniecGry = false;
        wczytaneDane = false;
      }
    } 
  }
}

int kierunek() {
  x = joystick.readX();  
  y = joystick.readY();
  
  if (x < 100)
    return 0;
  else if (y > 900)
    return 1;
  else if (x > 800)
    return 2;
  else if (y < 100)
    return 3;
  else if (x > 400 && x < 600 && y > 400 && y < 600) //stan neutralny
    return 4;
  else
    return 5;
}
