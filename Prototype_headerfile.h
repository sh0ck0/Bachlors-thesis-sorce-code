//
//  Prototype_headerfile.h
//  
//
//  Created by Jakob berntzen on 14/03/2023.
//

#ifndef Prototype_headerfile_h
#define Prototype_headerfile_h
// color codes
#define LTBLUE        0xB6DF
#define LTTEAL        0xBF5F
#define LTGREEN       0xBFF7
#define LTCYAN        0xC7FF
#define LTRED         0xFD34
#define LTMAGENTA     0xFD5F
#define LTYELLOW      0xFFF8
#define LTORANGE      0xFE73
#define LTPINK        0xFDDF
#define LTPURPLE      0xCCFF
#define LTGREY        0xE71C

#define BLUE          0x001F
#define TEAL          0x0438
#define GREEN         0x07E0
#define CYAN          0x07FF
#define RED           0xF800
#define MAGENTA       0xF81F
#define YELLOW        0xFFE0
#define ORANGE        0xFD20
#define PINK          0xF81F
#define PURPLE        0x801F
#define GREY          0xC618
#define WHITE         0xFFFF
#define BLACK         0x0000

#define DKBLUE        0x000D
#define DKTEAL        0x020C
#define DKGREEN       0x03E0
#define DKCYAN        0x03EF
#define DKRED         0x6000
#define DKMAGENTA     0x8008
#define DKYELLOW      0x8400
#define DKORANGE      0x8200
#define DKPINK        0x9009
#define DKPURPLE      0x4010
#define DKGREY        0x4A49

//SPI MCU 
#define TFT_DC 17
#define TFT_RST -1 // RST can be set to -1 if you tie it to Arduino's reset
#define MOSI 18
#define MISO 19
#define SCK 5
#define TFT_CS 16 // TFT display CS pin
#define SD_CS 21
#define MAX_CS 23

// Button pins
#define BUTTON1_PIN 13
#define BUTTON2_PIN 12
#define BUTTON3_PIN 27
#define BUTTON4_PIN 33
#define BUTTON5_PIN 15
#define BUTTON6_PIN 32
#define BUTTON7_PIN 14
#define BUTTON8_PIN 22

const uint8_t SPI_CSAFE_N = 0;
const uint32_t AFE_FIFO_SIZE = 256;
const uint32_t NUM_BYTES_PER_SAMPLE = 3;
const uint32_t NUM_STATUS_REGS = 2;
const uint32_t NUM_SAMPLES_PER_INT = 2;
uint8_t readBuf[NUM_SAMPLES_PER_INT * NUM_BYTES_PER_SAMPLE];
uint32_t adcCountArr[NUM_SAMPLES_PER_INT];



#endif /* Prototype_headerfile_h */
