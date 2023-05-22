#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdint.h>
#include "Prototype_headerfile.h"
#include "MAX30009.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "ArduinoJson.h"
#include "SD.h"
#include "FS.h"
#include "SPI.h"



bool display1 = true;
bool display2 = true;
bool display3 = true;
bool display4 = true;
bool display5 = true;
bool display6 = true;
bool display7 = true;
bool display8 = true;
bool display9 = true;
double ox, oy;
int startFreq = 100;      // Default start frequency in kHz
int stopFreq = 10000;     // Default stop frequency in kHz
int numSamples = 1;      // Default number of samples
bool freqUnitKHz = true;  // Frequency units in kHz by default


// Creating a display object called "tft" using Adafruit HX8357 and GFX library.
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);

//function to write to registers using SPI this does not work. need to be changed

void regWrite(uint8_t regAddr, uint8_t val){
    uint8_t ix = 0, tx_len = 3, tx_buf[tx_len];
    tx_buf[ix++] = regAddr;
    tx_buf[ix++] = 0x00;
    tx_buf[ix++] = val;
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(MAX_CS, LOW);

    for(int i = 0; i < tx_len; i++){
      SPI.transfer(tx_buf[i]);
    }
    digitalWrite(MAX_CS, HIGH);
    SPI.endTransaction();
}
//function to read registers using SPI
uint8_t regRead(uint8_t regAddr, uint8_t numBytes){
    uint8_t ix = 0, tx_len = 2, tx_buf[tx_len], reg_val;
    tx_buf[ix++] = regAddr;
    uint8_t rx_buf[numBytes + tx_len];
    tx_buf[ix++] = 0x80;
    SPI.transfer(tx_buf[0] & tx_buf[1]);
    reg_val = SPI.transfer(0x00);
    return reg_val;
}

  
void setup() {
  Serial.begin(9600);
  tft.begin();  // Initialize TFT display
  //start_up();
  tft.setRotation(3);  // Set display rotation
  tft.fillScreen(BLACK); // Set screen color to black to clear any old graphics.
  pinMode(MAX_CS, OUTPUT);
  digitalWrite(MAX_CS, HIGH);
  drawUI();

  // Initialize buttons
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);
  pinMode(BUTTON6_PIN, INPUT_PULLUP);
  pinMode(BUTTON7_PIN, INPUT_PULLUP);
  pinMode(BUTTON8_PIN, INPUT_PULLUP);

  // Initialize the SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");
}

void loop() {
  while(true) {
  if (digitalRead(BUTTON2_PIN) == HIGH) {
    startFreq -= freqUnitKHz ? 1000 : 100;
    if (startFreq < (freqUnitKHz ? 100 : 100)) {
      startFreq = freqUnitKHz ? 100 : 100;
    }
    updateFreqValues();
    delay(100);
  }

  if (digitalRead(BUTTON1_PIN) == HIGH) {
    startFreq += freqUnitKHz ? 1000 : 100;
    if (startFreq > (freqUnitKHz ? 100000 : 10000)) {
      startFreq = freqUnitKHz ? 100000 : 10000;
    }
    updateFreqValues();
    delay(100);
  }

  if (digitalRead(BUTTON4_PIN) == HIGH) {
    stopFreq -= freqUnitKHz ? 1000 : 100;
    if (stopFreq < (freqUnitKHz ? 10 : 1000)) {
      stopFreq = freqUnitKHz ? 10 : 1000;
    }
    updateFreqValues();
    delay(100);
  }

  if (digitalRead(BUTTON3_PIN) == HIGH) {
    stopFreq += freqUnitKHz ? 1000 : 100;
    if (stopFreq > (freqUnitKHz ? 100000 : 1000000)) {
      stopFreq = freqUnitKHz ? 100000 : 1000000;
    }
    updateFreqValues();
    delay(100);
  }
  if (digitalRead(BUTTON5_PIN) == HIGH) {
    numSamples += 1;
    updateFreqValues();
    delay(100);
  }
  if (digitalRead(BUTTON6_PIN) == HIGH) {
    if(numSamples > 1){
      numSamples -= 1;
      updateFreqValues();
      delay(100);
    }
  }
  if (digitalRead(BUTTON7_PIN) == HIGH) {
    freqUnitKHz = !freqUnitKHz;
    updateFreqValues();
    delay(100);
  }
  if (digitalRead(BUTTON8_PIN) == HIGH) {
    break;
    delay(100);
  }
}
tft.fillScreen(BLACK);
  while(true){
    
    warning();

    float results = BioZ_Measurement(startFreq, stopFreq, numSamples);;
    Display_BioZ_Data(results);
    delay(10000);
    tft.fillScreen(BLACK); // Set screen color to black to clear any old graphics.
    tft.setCursor(50, 170);
    tft.print("Do you want to svave the mesurement data?");
    tft.setCursor(70, 230);
    tft.print("Button 1 for YES  Button 2 for NO");

    if (digitalRead(BUTTON1_PIN) == HIGH) {

      // Create a JSON object to hold the data
      DynamicJsonDocument doc(1024);

      // Add some data to the JSON object
      doc["sensor"] = "temperature";
      doc["sensor"] = "temperature";
      doc["value"] = 25.5;

      // Generate a unique file name based on the current time
      String fileName = "/data_" + String(millis()) + ".json";

      // Open the file for writing
      File file = SD.open(fileName, FILE_WRITE);

      if (!file) {
        Serial.println("Failed to open file!");
        return;
      }

      // Serialize the JSON object to a string and write it to the file
      serializeJson(doc, file);

      // Close the file
      file.close();

      Serial.print("Data saved to file: ");
      Serial.println(fileName);

      // Wait for 1 second before saving the next data
      delay(1000);
    }
    else if(digitalRead(BUTTON2_PIN) == HIGH){
      continue;
    }
    tft.fillScreen(BLACK); // Set screen color to black to clear any old graphics.
    tft.setCursor(50, 170);
    tft.print("Do you want to svave the mesurement data?");
    tft.setCursor(70, 230);
    tft.print("Button 1 for YES  Button 2 for NO");
    if (digitalRead(BUTTON1_PIN) == HIGH){
      continue;
    }
    else if(digitalRead(BUTTON2_PIN) == HIGH){
      break;
    }
  }
}

void Start_Up() {  // code for starting MAX30009

  regWrite(0x20, 1 << 2); // BIOZ_BG_EN
  regWrite(0x11, 0); // clear SHDN
  regWrite(0x17, 0); // clear PLL_EN
  regWrite(0x1a, 0); // clear REF_CLK_SEL
  delay(1000);
  regWrite(0x11, 1); // RESET
  regRead(0x00, NUM_STATUS_REGS); // read and clear all status registers
  regWrite(0x0d, AFE_FIFO_SIZE - NUM_SAMPLES_PER_INT); // FIFO_A_FULL; assert A_FULL on NUM_SAMPLES_PER_INT samples
  regWrite(0x80, 0x80); // A_FULL_EN; enable interrupt pin on A_FULL assertion
  regWrite(0x18, 0xbb); // MDIV
  regWrite(0x19, 0x01); // PLL_LOCK_WNDW
  regWrite(0x1a, (0 << 6) | (1 << 5)); // REF_CLK_SEL | CLK_FREQ_SEL
  regWrite(0x17, (1 << 6) | (0 << 5) | (2 << 1) | 1);  // MDIV | NDIV | KDIV | PLL_EN
  regWrite(0x22, (3 << 4) | (2 << 2)); // BIOZ_VDRV_MAG | BIOZ_IDRV_RGE: 64uA
  regWrite(0x25, (3 << 2) | 3);  // BIOZ_AMP_RGE | BIOZ_AMP_BW
  regWrite(0x41, 1 << 1);  // MUX_EN
  // ensure to enable the MCU's interrupt pin before enabling BIOZ
  regWrite(0x20, (3 << 6) | (4 << 3) | (1 << 2) | (1 << 1) | 1); // BIOZ_DAC_OSR | BIOZ_ADC_OSR | BIOZ_BG_EN | BIOZ_Q_EN | BIOZ_I_EN: ADC 222Sps, DAC 14.208kHz
}
int BioZ_Measurement(uint8_t startFreq, uint8_t stopFreq, uint8_t numSamples) {  // sending the range and the number of freqs from the MCU to MAX30009 and starting the measurement


  return 0;
}

void drawUI() {
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(40, 20);
  tft.print("Please input the Frequency range");
  tft.setCursor(20, 70);
  tft.print("Start Frequency:");
  tft.setCursor(20, 120);
  tft.print("Stop Frequency:");
  tft.setCursor(20, 170);
  tft.print("Sample Points:");
  tft.setCursor(20, 230);
  tft.print("Frequency Units:");
  tft.setCursor(20, 280);
  tft.setTextSize(1);
  tft.print("1: Start freq up 2: Start freq down 3: Stop freq up 4: Stop freq down");
  tft.setCursor(20, 290);
  tft.print("5: sample points up 6: sample points down 7: change unit (Hz/kHz) 8: confirm");
  tft.setTextSize(2);
  updateFreqValues();
}
void updateFreqValues() {
  tft.setTextSize(2);
  tft.setTextColor(YELLOW);
  // Clear previous start frequency value
  tft.fillRect(220, 70, 130, 25, BLACK);
  tft.setCursor(220, 70);
  tft.print(startFreq);
  tft.print(" Hz");

  // Clear previous stop frequency value
  tft.fillRect(220, 120, 130, 25, BLACK);
  tft.setCursor(220, 120);
  tft.print(stopFreq);
  tft.print(" Hz");

  // Clear previous sample points value
  tft.fillRect(220, 170, 130, 25, BLACK);
  tft.setCursor(220, 170);
  tft.print(numSamples);

  // Clear previous frequency units value
  tft.fillRect(220, 230, 130, 25, BLACK);
  tft.setCursor(220, 230);
  tft.print(freqUnitKHz ? "kHz" : "Hz");
}

void warning() {
  tft.setCursor(50, 170);
  tft.setTextSize(3);
  tft.print("Please connect the electrodes and plase them on the ");
}
void Graph(Adafruit_HX8357
             /*
  function to draw a cartesian coordinate system and plot whatever data you want
  just pass x and y and the graph will be drawn
*/
             &d,                 //name of your display object
           double x,             // x      = x data point
           double y,             // y      = y datapont
           double gx,            // gx     = x graph location (lower left)
           double gy,            // gy     = y graph location (lower left)
           double w,             // w      = width of graph
           double h,             // h      = height of graph
           double xlo,           // xlo    = lower bound of x axis
           double xhi,           // xhi    = upper bound of x asis
           double xinc,          // xinc.  = division of x axis (distance not count)
           double ylo,           // ylo    = lower bound of y axis
           double yhi,           // yhi    = upper bound of y asis
           double yinc,          // yinc   = division of y axis (distance not count)
           String title,         // title  = title of graph
           String xlabel,        // xlabel = x asis label
           String ylabel,        // ylabel = y asis label
           unsigned int gcolor,  // gcolor = graph line colors
           unsigned int acolor,  // acolor = axi ine colors
           unsigned int pcolor,  // pcolor = color of your plotted data
           unsigned int tcolor,  // tcolor = text color
           unsigned int bcolor,  // bcolor = background color
           boolean &redraw) {

  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * (w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for (i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp = (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      } else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp = (i - xlo) * (w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      } else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }

    //now draw the labels
    d.setTextSize(2);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx, gy - h - 30);
    d.println(title);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx, gy + 20);
    d.println(xlabel);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);
  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x = (x - xlo) * (w) / (xhi - xlo) + gx;
  y = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;
}

void Display_BioZ_Data(float data) {  // displaying the measurement on screen using the grapging func that is decribed later

  double y = data;

  for (int x; x > 10; x++) {
    Graph(tft, x, y, 50, 290, 390, 260, 0, 60, 10, 70, 90, 5, "BioZ", " Time [s]", "Temperature [deg F]", DKBLUE, RED, GREEN, WHITE, BLACK, display7);
  }

  delay(250);
}
