int wylosowany_kolor = 0;
int d = 7; //opoznienie między przejściami do mocniejszego/jaśniejszego koloru w trybie 0

/*
0 -> stałe przerwy
1 -> im mocniej, tym dłuższe przerwy
2 -> im mocniej, tym krótsze przerwy
*/ 
int tryb_oddychania = 1;

//piny
int czerwony = 11;
int zielony = 10;
int niebieski = 9; 
void opoznienie(int);

void setup() {
  pinMode(czerwony, OUTPUT);
  pinMode(zielony, OUTPUT);
  pinMode(niebieski, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(0)); //ziarno
  
  //delay(500);
}

void loop() {

int wylosowany_kolor = random(4); //losujemy liczbę
// Serial.println(wylosowany_kolor); //wypisanie na konsolę

for (int a = 255; a >= 0 ; a-- )
  {
    switch (wylosowany_kolor) {
    case 0: //czerwona
      analogWrite(czerwony, a);    
      break;
    case 1: //zielona
      analogWrite(zielony, a);
      break;
    case 2: //niebieska
      analogWrite(niebieski, a);
      break;
    case 3: //magenta/aqua
      analogWrite(zielony, a);
      analogWrite(niebieski, a);
      break;
    }
    opoznienie(a);
  }
  
 delay(180);
 
 for (int a = 0; a < 256 ; a++ )
  {
    switch (wylosowany_kolor) {
    case 0: //czerwona
      analogWrite(czerwony, a);
      break;
    case 1: //zielona
      analogWrite(zielony, a);
      break;
    case 2: //niebieska
      analogWrite(niebieski, a);
      break;
    case 3: //magenta/aqua
      analogWrite(zielony, a);
      analogWrite(niebieski, a);
      break;
    }
    opoznienie(a);
  }
  
  delay(60);
} 

void opoznienie(int a) {
  if (tryb_oddychania == 0) {
    delay(d);
  } else if (tryb_oddychania == 1) {
    if (a > 180)
      delay(3);
    if ((a > 155) && (a < 181))
      delay(4);
    if ((a > 130) && (a < 156))
      delay(6);
    if ((a > 100) && (a < 131))
      delay(9);
    if ((a > 70) && (a < 101))
      delay(12);
    if ((a > 35) && (a < 71))
      delay(15);
    if ((a >= 0) && (a < 36))
      delay(18);
  } else if (tryb_oddychania == 2) {
    if (a > 180)
      delay(18);
    if ((a > 155) && (a < 181))
      delay(15);
    if ((a > 130) && (a < 156))
      delay(12);
    if ((a > 100) && (a < 131))
      delay(9);
    if ((a > 70) && (a < 101))
      delay(6);
    if ((a > 35) && (a < 71))
      delay(4);
    if ((a >= 0) && (a < 36))
      delay(3);
  }

}
