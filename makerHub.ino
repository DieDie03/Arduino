//Leds
#define greenL 7
#define yellowL 8
#define redL 9

//Ambiant

const int greenLEDPin = 10;    // LED connected to digital pin 9
const int redLEDPin = 11;     // LED connected to digital pin 10
const int blueLEDPin = 12;    // LED connected to digital pin 11

const int redSensorPin = A3;  // pin with the photoresistor with the red gel
const int greenSensorPin = A4;   // pin with the photoresistor with the green gel
const int blueSensorPin = A5;   // pin with the photoresistor with the blue gel

int redValue = 0; // value to write to the red LED
int greenValue = 0; // value to write to the green LED
int blueValue = 0; // value to write to the blue LED

int redSensorValue = 0; // variable to hold the value from the red sensor
int greenSensorValue = 0; // variable to hold the value from the green sensor
int blueSensorValue = 0; // variable to hold the value from the blue sensor

//Micro
const int microphone = A0;
const int treshold1 = 767;
const int treshold2 = 895;
const int treshold3 = 1023;

// named constant for the pin the sensor is connected to
const int sensorPin = A1;
// room temperature in Celsius
const float baselineTemp = 20.0;
const int pinNumber2 = 2;
const int pinNumber3 = 3;

void setup() {
  // open a serial connection to display values
  Serial.begin(9600);
  // set the LED pins as outputs
  // the for() loop saves some extra coding
  pinMode(greenL, OUTPUT);
  pinMode(yellowL, OUTPUT);
  pinMode(redL, OUTPUT);
  pinMode(microphone, INPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(pinNumber2, OUTPUT);
  pinMode(pinNumber3, OUTPUT);

}

void loop() {
  // read the value on AnalogIn pin 0 and store it in a variable
  int sensorVal = analogRead(sensorPin);
  int microsens = analogRead(microphone);
  redSensorValue = analogRead(redSensorPin);
  greenSensorValue = analogRead(greenSensorPin);
  blueSensorValue = analogRead(blueSensorPin);
  
  redValue = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue = blueSensorValue / 4;
  
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
  // send the 10-bit sensor value out the serial port


  // convert the ADC reading to voltage

  // convert the voltage to temperature in degrees C
  // the sensor changes 10 mV per degree
  // the datasheet says there's a 500 mV offset
  // ((voltage - 500 mV) times 100)

  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - .5) * 100;
  // Send the voltage level out the Serial port

  Serial.print("LIGHT sensor Values \t red: ");
  Serial.print(redSensorValue);
  Serial.print("\t green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);
  Serial.print("TEMPERATURE sensor Value: ");
  Serial.print(sensorVal);

  Serial.print(", Volts: ");
  Serial.print(voltage);

  Serial.print(", degrees C: ");
  Serial.println(temperature);

  if(temperature<20){
    digitalWrite(pinNumber2,HIGH);
    digitalWrite(pinNumber3,LOW);
    
  }
  else if (temperature >20 && temperature <30){
    digitalWrite(pinNumber2,LOW);
    digitalWrite(pinNumber3,HIGH);
  }
  else if (temperature > 30){
    digitalWrite(pinNumber2,HIGH);
    digitalWrite(pinNumber3,HIGH);
  }

  
  if (microsens <= treshold1) {
    digitalWrite(redL, LOW);
    digitalWrite(yellowL, LOW);
    digitalWrite(greenL, LOW);
  }
  else if (microsens >= treshold1 && microsens < treshold2) {

    digitalWrite(redL, HIGH);
    digitalWrite(yellowL, LOW);
    digitalWrite(greenL, LOW);
    Serial.print("MICROPHONE RED : " );
    Serial.println(microsens);
  }
  else if (microsens >= treshold2 && microsens < treshold3) {

    digitalWrite(redL, HIGH);
    digitalWrite(yellowL, HIGH);
    digitalWrite(greenL, LOW);
    Serial.print("MICROPHONE YELLOW : " );
    Serial.println(microsens);
  }
  else if (microsens >= treshold3) {

    digitalWrite(redL, HIGH);
    digitalWrite(yellowL, HIGH);
    digitalWrite(greenL, HIGH);
    Serial.print("MICROPHONE BLUE : " );
    Serial.println(microsens);

  }

  delay(1000);
}
