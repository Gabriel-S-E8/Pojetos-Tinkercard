#include <LiquidCrystal_I2C.h>

// Definição do endereço I2C do LCD
const int lcd_address = 0x27;

// Criação da instância do LCD
LiquidCrystal_I2C lcd(lcd_address, 16, 2);

// Pino compartilhado para os sensores
const int sensorPin = A0;

// Pinos de controle para ativar/desativar os sensores
const int controleTemperatura = 2;
const int controleLuz = 3;
const int controleUmidadeSolo = 4;

void setup() {
  // Inicialização do LCD
  lcd.init();
  lcd.backlight();

  // Configuração dos pinos de controle como saída
  pinMode(controleTemperatura, OUTPUT);
  pinMode(controleLuz, OUTPUT);
  pinMode(controleUmidadeSolo, OUTPUT);

  // Configuração do pino compartilhado como entrada
  pinMode(sensorPin, INPUT);
}

int lerSensor(int controlePin) {
  digitalWrite(controlePin, HIGH); // Ativa o sensor específico
  delay(10); // Pequeno atraso para estabilização
  int valorSensor = analogRead(sensorPin);
  digitalWrite(controlePin, LOW); // Desativa o sensor
  return valorSensor;
}

float converterTemperatura(int valorSensor) {
  float quedaDiodo = 0.124; // Queda de tensão do diodo
  float fatorCorrecao = 0.04; // Fator de correção para ajustar a leitura
  float voltagem = (valorSensor * (5.0 / 1023.0)) + quedaDiodo;
  float temperaturaCelsius = ((voltagem - 0.5) * 100.0) + fatorCorrecao;
  return temperaturaCelsius;
}

int converterLuz(int valorSensor) {
  float quedaDiodo = 0.7; // Ajuste este valor para a queda de tensão do seu diodo
  float fatorCorrecao = 0.04; // Fator de correção para ajustar a leitura
  float voltagem = (valorSensor * (5.0 / 1023.0)) + quedaDiodo;
  float luz = (voltagem - 0.5) * 100.0 + fatorCorrecao;
  luz = constrain(luz, 0, 100); // Limita o valor entre 0 e 100
  return (int)luz;
}

int converterUmidade(int valorSensor) {
  float quedaDiodo = 0.7; // Ajuste este valor para a queda de tensão do seu diodo
  float fatorCorrecao = 0.04; // Fator de correção para ajustar a leitura
  float voltagem = (valorSensor * (5.0 / 1023.0)) + quedaDiodo;
  float umidadeSolo = (voltagem - 0.5) * 100.0 + fatorCorrecao;
  umidadeSolo = constrain(umidadeSolo, 0, 100); // Limita o valor entre 0 e 100
  return (int)umidadeSolo;
}



void loop() {
  // Leitura e conversão da temperatura
  int valorTemperatura = lerSensor(controleTemperatura);
  float temperatura = converterTemperatura(valorTemperatura);
  // Exibição da temperatura no LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" C");
  delay(5000); // Aguarda 5 segundos
  lcd.clear(); // Limpa a tela do LCD

  // Leitura e conversão da luz ambiente
  int valorLuz = lerSensor(controleLuz);
  int luz = converterLuz(valorLuz);
  // Exibição da luz ambiente no LCD
  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.print(luz);
  delay(5000); // Aguarda 5 segundos
  lcd.clear(); // Limpa a tela do LCD

  // Leitura e conversão da umidade do solo
  int valorUmidade = lerSensor(controleUmidadeSolo);
  int umidadeSolo = converterUmidade(valorUmidade);
  // Exibição da umidade do solo no LCD
  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.print(umidadeSolo);
  delay(5000); // Aguarda 5 segundos
  lcd.clear(); // Limpa a tela do LCD
}
