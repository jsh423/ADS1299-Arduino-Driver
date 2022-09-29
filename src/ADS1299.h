/* ADS1299.h
 * Header file for ADS1299.cpp
 * Driver library for ADS1299 from TI
 * 
 * Authors: Mingye Chen
 */
#ifndef ADS1299_h
#define ADS1299_h

#include <stdio.h>
#include <Arduino.h>
#include <SPI.h>
#include "Definitions.h"
#include "configs.h"

#define ADS1299_PIN_DRDY 27

#define ADS1299_PIN_SCK 14
#define ADS1299_PIN_MISO 12
#define ADS1299_PIN_MOSI 13
#define ADS1299_PIN_SS 26


class ADS1299 {
public:
    int mode = 1;
    int DRDY, CS, RESET_pin;
    int logcounter=0;
    long datalog[LOGSIZE][NUMBEROFCHANNELS*2];
    float VREF;
    void setup(int _DRDY, int _CS, int RESET_PIN, int mode); // mode is either RDATAC - 0 or RDATA - 0

    void RESET();
    void START();
    void STOP();
    
    void RDATAC();
    void SDATAC();
    void RDATA();

    void getID();
    void RREG(byte _address);
    void RREG(byte _address, byte _numRegistersMinusOne); //to read multiple consecutive registers (Datasheet, pg. 38)
    
    void printRegisterName(byte _address);
    
    void WREG(byte _address, byte _value); //
    void WREG(byte _address, byte _value, byte _numRegistersMinusOne); //

    /// @brief 
    //static void drdy_interrupt();//中断读取数据
    
    void updateData(); // RDATAC
    void RDATA_update(); // RDATA
    void RDATA_logger();
    void STARTUP(); // Startup routine
    void init_ADS_4();// initialize configs for 4 channel version
    void init_ADS_8();// initialize configs for 8 channel version
    void init_ADS_4_test();
};
void ads1299_drdy_interrupt(void) ;
typedef struct openbci_data_packet
{
    uint8_t header;

    uint8_t sample_number;

    uint8_t channel_data[24];

    uint8_t auxiliary_data[6];

    uint8_t footer;
} __attribute__ ((packed)) openbci_data_packet;

typedef struct ads1299_data_packet
{
    uint32_t stat : 24;

    uint8_t channel_data[24];
} __attribute__ ((packed)) ads1299_data_packet;

#endif