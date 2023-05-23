
#define BUTTON1_PIN 13
#define BUTTON2_PIN 12
#define BUTTON3_PIN 27
#define BUTTON4_PIN 33
#define BUTTON5_PIN 15
#define BUTTON6_PIN 32
#define BUTTON7_PIN 14
#define BUTTON8_PIN 22


void setup() {
  Serial.begin(9600);


  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);
  pinMode(BUTTON6_PIN, INPUT_PULLUP);
  pinMode(BUTTON7_PIN, INPUT_PULLUP);
  pinMode(BUTTON8_PIN, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(BUTTON1_PIN) == HIGH) {
    Serial.println("Button 1 was pressed");

  }
  if (digitalRead(BUTTON2_PIN) == HIGH) {
    Serial.println("Button 2 was pressed");

  }
  if (digitalRead(BUTTON3_PIN) == HIGH) {
    Serial.println("Button 3 was pressed");

  }
  if (digitalRead(BUTTON4_PIN) == HIGH) {
    Serial.println("Button 4 was pressed");

  }
  if (digitalRead(BUTTON5_PIN) == HIGH) {
    Serial.println("Button 5 was pressed");

  }
 if (digitalRead(BUTTON6_PIN) == HIGH) {
    Serial.println("Button 6 was pressed");
    delay(100);

  }
  if (digitalRead(BUTTON7_PIN) == HIGH) {
    Serial.println("Button 7 was pressed");
    delay(100);
  }
  if (digitalRead(BUTTON8_PIN) == HIGH) {
    Serial.println("Button 8 was pressed");
    delay(100);
  }
 
 



}
