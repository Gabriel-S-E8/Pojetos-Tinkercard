// Definição dos pinos
const int sensorUltrassonicoPin = 9; // Pino para o sensor ultrassônico
const int piezoPin = 8;
const int ledVerde = 5;
const int ledAmarelo = 6;
const int ledVermelho = 7;

void setup() {
  // Inicializa os pinos como saída
  pinMode(piezoPin, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(sensorUltrassonicoPin, OUTPUT); // Configura o pino do sensor como saída para o pulso
  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  // Configura o pino do sensor como saída
  pinMode(sensorUltrassonicoPin, OUTPUT);
  digitalWrite(sensorUltrassonicoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorUltrassonicoPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorUltrassonicoPin, LOW);

  // Configura o pino do sensor como entrada para ler o eco
  pinMode(sensorUltrassonicoPin, INPUT);
  long duracao = pulseIn(sensorUltrassonicoPin, HIGH);

  // Calcula a distância
  int distanciaCm = duracao / 29 / 2; // Velocidade do som no ar (343 m/s) dividida por 2 (ida e volta)

  // Imprime a distância no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distanciaCm);
  Serial.println(" cm");

  // Acende o LED verde, amarelo ou vermelho baseado na distância
  if (distanciaCm > 80) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } else if (distanciaCm > 50 && distanciaCm <= 80) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }

  // Emite um som baseado na distância
  int frequencia = map(distanciaCm, 150, 0, 400, 2000); // Frequência mais alta para distâncias menores
  tone(piezoPin, frequencia, 100);

  // Intervalo entre as medições
  int intervalo = map(distanciaCm, 150, 0, 1000, 200); // Intervalos mais curtos para distâncias menores
  delay(intervalo);
}
