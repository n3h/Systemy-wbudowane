//piny
int LDR = A1;
int GLOSNIK = 10;
int PRZYCISK1 = 3;
int PRZYCISK2 = 2;
int LED1 = 9; // zielona
int LED2 = 6; // czerwona

const int rozmiarNagrania = 700;
int nagranie[rozmiarNagrania];
int ileNagrano = 0;
int ileOdtworzono = 0;

int wartosc;
int stanPrzyciskuOdtwarzania;
int stanPrzyciskuNagrywania;

// 0 - normalny tryb
// 1 - odtwarzanie
// 2 - nagrywanie
int stan = 0;
int poprzedniStan = 0;

int max = 1000; // 1000
int min = 0; // 0

void setup() {
  Serial.begin(9600); 
  wartosc = analogRead(LDR);
  /*
  Serial.println("Poczatek kalibracji");
  for (int i = 0; i < 1000; i++) {
    if (wartosc > max)
      max = wartosc;
    if (wartosc < min)
      min = wartosc;
      
  delay(5);
  }
  Serial.println("koniec kalibracji");
  */
    
  
  pinMode(PRZYCISK1, INPUT);
  pinMode(PRZYCISK2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(GLOSNIK, OUTPUT);
}
// 0 - 600
int pobierzWartosc() {
  return map(analogRead(LDR), 0, 1024, 50, 5000);
}
  
void loop() {
  Serial.println(analogRead(LDR));
  
  stanPrzyciskuOdtwarzania = digitalRead(PRZYCISK1);
  stanPrzyciskuNagrywania = digitalRead(PRZYCISK2);
  if (stanPrzyciskuNagrywania == HIGH) {
    if (stan != 2) 
      ileNagrano = 0;
    stan = 2;
    
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    
    wartosc = pobierzWartosc();
    nagranie[ileNagrano] = wartosc;
    tone(GLOSNIK, wartosc, 40);
    ileNagrano = (ileNagrano + 1) % rozmiarNagrania;
    
  } else if (stanPrzyciskuOdtwarzania == HIGH) {
    if (stan != 1) 
      ileOdtworzono = 0;
    stan = 1;
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    tone(GLOSNIK, nagranie[ileOdtworzono], 40);
    ileOdtworzono = (ileOdtworzono + 1) % ileNagrano;
    
  } else {
    stan = 0;
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    
    wartosc = pobierzWartosc();
    tone(GLOSNIK, wartosc);
  }  
}
