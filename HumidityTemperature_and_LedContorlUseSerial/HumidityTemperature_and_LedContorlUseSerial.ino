#include <DHT.h>
#define buttonPin 21
#define ledPin 19
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int buttonState=0;
int ledState=0;
char data;

unsigned long tunggu=5000;
unsigned long waktuSebelumnya=0;
unsigned long waktuSekarang=0;

float h=0;
float t=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  waktuSekarang = millis();
  if(waktuSekarang - waktuSebelumnya >= tunggu){
    waktuSebelumnya = waktuSekarang;
    h = dht.readHumidity();
    t = dht.readTemperature();

    kirim(h, t, ledState);
  }
  if(Serial.available()){
    data = Serial.read();

    if(data == '1'){
      ledState = ~ledState;
    }
    digitalWrite(ledPin, ledState);
    kirim(h, t, ledState);
  }

  buttonState = digitalRead(buttonPin);
  if(buttonState){
    debounce(buttonPin, HIGH);
    ledState = ~ledState;
    digitalWrite(ledPin, ledState);
    kirim(h, t, ledState);
  }

}

void kirim(float h, float t, int ledState){
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.println(ledState);
}

void debounce(int pin, unsigned char active_logic){
  delay(10);
  if(digitalRead(pin)==active_logic){
    delay(100);
    while(digitalRead(buttonPin)==active_logic){};
  }
}
