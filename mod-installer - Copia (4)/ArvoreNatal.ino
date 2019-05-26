/*
   Q0405
   AUTOR:   BrincandoComIdeias
   LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
   COMPRE:  https://www.arducore.com.br/
   SKETCH:  Arvore de Natal com Arduino
   DATA:    05/12/2018
*/

#define pinSom 3
#define pinRele 12
#define pinAcop 2

#define tempoEntrePalmas 150 //milisegundos
#define tempoMaximoEntrePalmas 500 //milisegundos

// DECLARAÇÃO DE VARIÁVEIS
int contaPalmas = 0;
unsigned long tempoEspera = 0;
unsigned long tempoEsperaEntrePalmas = 0;

// DECLARAÇÃO DE FUNÇÃO
void executarAcao();

void setup() {

  Serial.begin(9600);

  // DEFININDO MODO DOS PINOS
  pinMode(pinSom, INPUT);
  pinMode(pinRele, OUTPUT);
  pinMode(pinAcop, OUTPUT);

  // INICIANDO COM O PINO DO RELE E DO FOTOACOPLADOR DESLIGADOS
  digitalWrite(pinRele, LOW);
  digitalWrite(pinAcop, LOW);

  Serial.println("Setup Concluído");
}

void loop() {
  //VERIFICA O ESTADO DO SENSOR, AO BATER PALMA O SINAL VAI PARA HIGH
  static int sensorSomAnt;
  int sensorSom = digitalRead(pinSom);

  //SE O SENSOR DETECTAR MUDANÇA DO ESTADO LOW PARA HIGH
  if ((sensorSom == HIGH) && (sensorSomAnt == LOW)) {
    Serial.print("detectou");

    //CALCULA O TEMPO DA ULTIMA MUDANÇA PARA NAO DETECTAR ECO DA MESMA PALMA
    if ((millis() - tempoEspera) > tempoEntrePalmas) {
      tempoEspera = millis(); // ATUALIZA O TEMPO PARA CONTROLE DE ECO
      tempoEsperaEntrePalmas = millis(); // ATUALIZA O TEMPO PARA CONTROLE DA CONTAGEM
      contaPalmas++;
    }
  }
  sensorSomAnt = sensorSom;

  // CASO EXCEDA O TEMPO DE CONTROLE DA CONTAGEM, EXECUTA A AÇÃO E ZERA A CONTAGEM
  if ( (contaPalmas != 0) && ((millis() - tempoEsperaEntrePalmas) > tempoMaximoEntrePalmas) ) {
    executarAcao();
    contaPalmas = 0;
    tempoEsperaEntrePalmas = millis();
  }

}


void executarAcao() {

  switch (contaPalmas) {
    case 3:
      digitalWrite(pinAcop, HIGH);
      delay(200);
      digitalWrite(pinAcop, LOW);
      Serial.println("Duas Palmas, trocando modo do pisca");
      break;
    case 2:
      digitalWrite(pinRele, !digitalRead(pinRele));
      Serial.println("Tres Palmas, trocando estado do rele");
      break;
    default:
      Serial.print("A quantidade de palmas foi de:");
      Serial.println(contaPalmas);
  }
}
