# include <Ultrasonic.h>
# include <FastLED.h>

# define DATA_PIN 8  // Pino de dados da fita de LED
# define MAX_LEDS 87

# define NUM_MAGICO 65

# define pino_trigger_0 4  //vinho
# define pino_echo_0 5     //orange

# define pino_trigger_1 7  //azul
# define pino_echo_1 6     //amarelo

# define pino_trigger_2 12  //branco
# define pino_echo_2 10     //preto

# define pino_trigger_3 13  //marrom
# define pino_echo_3 11     //cinza

# define MAX_ANO 4 // Quantos anos têm no vetor
# define MAX_CIDADE 4 // Quantas cidades há

//Inicialização de cada sensor de ultrassom, para passagem dos anos
Ultrasonic ultrasonic0(pino_trigger_0, pino_echo_0);
Ultrasonic ultrasonic1(pino_trigger_1, pino_echo_1);
Ultrasonic ultrasonic2(pino_trigger_2, pino_echo_2);
Ultrasonic ultrasonic3(pino_trigger_3, pino_echo_3);

int j = 0;

//Vetor que indica a quantidade de acidentes em cada ano
int acidentesMedia[MAX_ANO] = { 14, 27, 42, 51 };

//Médias do Brasil em cada um dos quatro anos
int mediaBrasil[MAX_ANO] = { 19, 14, 11, 12 };

//Definição das cidades
char cidade[MAX_CIDADE][15] = { "Vitoria", "Vila Velha", "Serra", "Cariacica" };

//Declaração dos LEDs
CRGB color;
CRGB leds[MAX_LEDS];
int numeroLeds = 0;
int numeroLedsBR = 0;
int flag = 0;

//Começa com valor maior que o limite das funções
long microsec0 = 1500;
long microsec1 = 1500;
long microsec2 = 1500;
long microsec3 = 1500;

long tempoMudanca;

void setColor(int j) {
  //Proporcionalmente ao número máximo de LEDs (MAX_LEDS), a fita ligará
  numeroLeds = (acidentesMedia[j] * MAX_LEDS/NUM_MAGICO);
  numeroLedsBR = (mediaBrasil[j] * MAX_LEDS/NUM_MAGICO);

  Serial.print(j + 2019);
  Serial.print(", ");
  Serial.print(cidade[0]);
  Serial.print(", Acidentes: ");
  Serial.println(acidentesMedia[j]);

  if (j == 0) {
    color = CRGB::Red;
  } else if (j == 1) {
    color = CRGB::Yellow;
  } else if (j == 2) {
    color = CRGB::Magenta;
  } else if (j == 3) {
    color = CRGB::Cyan;
  }

  // color = CRGB::Red;

  for (int i = 0; i < MAX_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();

  for (int i = 0; i < numeroLedsBR; i++) {
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(8);
  }

  for (int i = numeroLedsBR; i < numeroLeds + numeroLedsBR; i++) {
    leds[i] = color;
    FastLED.show();
    delay(8);
  }

}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, MAX_LEDS);
  tempoMudanca = millis();
}

void loop() {

  microsec0 = ultrasonic0.timing();
  microsec1 = ultrasonic1.timing();
  microsec2 = ultrasonic2.timing();
  microsec3 = ultrasonic3.timing();

  if (microsec0 <= 1000) {
    j = 0;
    setColor(j);
    tempoMudanca = millis();

    while(microsec0 <= 1000)
    {
      microsec0 = ultrasonic0.timing();
      Serial.print(".");
      tempoMudanca = millis();
      delay(100);
    }
    Serial.println();
  }

  else if (microsec1 <= 1000) {
    j = 1;
    setColor(j);
    tempoMudanca = millis();

    while(microsec1 <= 1000)
    {
      microsec1 = ultrasonic1.timing();
      Serial.print(".");
      tempoMudanca = millis();
      delay(100);
    }
    Serial.println();
  }

  else if (microsec2 <= 1000) {
    j = 2;
    setColor(j);
    tempoMudanca = millis();

    while(microsec2 <= 1000)
    {
      microsec2 = ultrasonic2.timing();
      Serial.print(".");
      tempoMudanca = millis();
      delay(100);
    }
    Serial.println();
  }

  else if (microsec3 <= 1000) {
    j = 3;
    setColor(j);
    tempoMudanca = millis();

    while(microsec3 <= 1000)
    {
      microsec3 = ultrasonic3.timing();

      Serial.print(".");
      tempoMudanca = millis();
      delay(150);
    }
    Serial.println();
  }

  if(millis() - tempoMudanca > 4000)
  {
    j++;
    j = j % MAX_ANO;
    setColor(j);
    tempoMudanca = millis();
  }

  delay(30);
}