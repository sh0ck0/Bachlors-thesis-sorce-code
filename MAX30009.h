//
//  MAX30009.h
//  All the register addresses.
//
//  Created by Jakob berntzen on 28/04/2023.
//

#ifndef MAX30009_h
#define MAX30009_h

#define STATUS_1                0x00 
#define STATUS_2                0x01
#define FIFO_WR_PTR             0x08
#define FIFO_RD_PTR             0x09
#define FIFO_COUNTER_1          0x0A
#define FIFO_COUNTER_2          0x0B
#define FIFO_DATA               0x0C
#define FIFO_CONFIG_1           0x0D
#define FIFO_CONFIG_2           0x0E
#define SYSTEM_SYNC             0x10
#define SYSTEM_CONFIG_1         0x11
#define PIN_FUNC_CONFIG         0x12
#define OUTPUT_PIN_CONFIG       0x13
#define I2C_ADDR                0x14
#define PLL_CONFIG_1            0x17
#define PLL_CONFIG_2            0x18
#define PLL_CONFIG_3            0x19
#define PLL_CONFIG_4            0x1A
#define BIOZ_CONFIG_1           0x20
#define BIOZ_CONFIG_2           0x21
#define BIOZ_CONFIG_3           0x22
#define BIOZ_CONFIG_4           0x23
#define BIOZ_CONFIG_5           0x24
#define BIOZ_CONFIG_6           0x25
#define BIOZ_CONFIG_7           0x28
#define BIOZ_LO_THRESH          0x26
#define BIOZ_HI_THRESH          0x27
#define BIOZ_MUX_CONFIG_1       0x41
#define BIOZ_MUX_CONFIG_2       0x42
#define BIOZ_MUX_CONFIG_3       0x43
#define BIOZ_MUX_CONFIG_4       0x44
#define DC_LEADS_CONFIG         0x50
#define DC_LEAD_DETECT_THRESH   0x51
#define LEAD_BIAS_CONFIG_1      0x58
#define INT_EN_1                0x80
#define INT_EN_2                0x81
#define PART_ID                 0xFF




#endif /* MAX30009_h */
