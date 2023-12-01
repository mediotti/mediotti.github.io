#include <LiquidCrystal_I2C.h>
#include <stdlib.h>

const int RED_LED_PIN = 7;
const int YELLOW_LED_PIN = 4;
const int GREEN_LED_PIN = 2;
const int LDR_PIN = A0;
const int HUMIDITY_PIN = A3;
const int TEMPERATURE_PIN = A2;
const int BUZZER_PIN = 8;

LiquidCrystal_I2C lcd(0x20,16,2);

void setupLCD() {
  lcd.init();
  lcd.backlight();
  lcd.print("Geladeira de Remedios");
  lcd.setCursor(0, 1);
  lcd.print("Hapvida");
}

double readTemperature() {
  double voltage = (analogRead(TEMPERATURE_PIN) / 1023.0) * 5000; // 5000 to get millivots.
  double tempC = (voltage-500) * 0.1; // 500 is the offset
  return tempC;
}

double readHumidity() {
  int humiditysensorOutput = map(analogRead(HUMIDITY_PIN), 0, 1023, 10, 70);
  return humiditysensorOutput;
}


char* doubleToString(double value) {
  static char buffer[10];
  dtostrf(value, 4, 2, buffer);
  return buffer;
}

void setup() {
  setupLCD();
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);  
  pinMode(LDR_PIN, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void turnOffAllLeds() {
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void printLCD(char * message1, char * message2){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message1);
  lcd.setCursor(0, 1);
  lcd.print(message2);
  delay(5000);
}

void buzz(){
  tone(8, 1000, 1000);
  delay(1000);
  noTone(8);
}

void buzz3seconds(){
  tone(8, 1000, 3000);
  delay(3000);
  noTone(8);
  delay(3000);
}

void printHumidityScenario(double humidity) {
  Serial.println(humidity);
  char* humidityString = doubleToString(humidity);

  if (humidity <= 60){
    lcd.clear();
    printLCD("UMIDADE BAIXA", humidityString);
    buzz3seconds();
  } else if (humidity > 60 && humidity < 80){
    lcd.clear();
    printLCD("UMIDADE OK", humidityString);
  } else if (humidity >= 80) {
    lcd.clear();
    printLCD("UMIDADE ALTA", humidityString);
    buzz3seconds();
  }
}

void printTemperatureScenario(double temperature) {
  Serial.println(temperature);
  char* temperatureString = doubleToString(temperature);
  if (temperature < 10){
    lcd.clear();
    printLCD("TEMP. OK", temperatureString);
  } else {
    lcd.clear();
    printLCD("TEMP. ALTA", temperatureString);
    buzz();
  }
}

void calculateStatusOfWineyard() {
  int count = 0;
  int luminositySum = 0;
  int humiditySum = 0;
  int temperatureSum = 0;

  while (count < 5){
    luminositySum += analogRead(LDR_PIN);
    humiditySum += readHumidity();
    temperatureSum += readTemperature();
    count++;
  }

  int luminosityAverage = map((luminositySum/count), 160, 600, 1, 8);
  double humidityAverage = humiditySum/count;
  double temperatureAverage = temperatureSum/count;

  printHumidityScenario(humidityAverage);
  printTemperatureScenario(temperatureAverage);
}

void loop() {
  calculateStatusOfWineyard();
  delay(1000);
}