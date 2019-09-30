#include <Arduino.h>
#include <SPI.h>
#include "LongFi.h"

// set OUI and device_id to work with LongFi routing
const uint32_t oui = 1234;
const uint16_t device_id = 99;

// Discovery L072CZ-LRWAN1
const uint8_t RADIO_RESET_PIN = RADIO_RESET_PORT;
const uint8_t RADIO_DIO_0_PIN = RADIO_DIO_0_PORT;
const uint8_t RADIO_MOSI_PIN  = RADIO_MOSI_PORT;
const uint8_t RADIO_MISO_PIN  = RADIO_MISO_PORT;
const uint8_t RADIO_SCLK_PIN  = RADIO_SCLK_PORT;
const uint8_t RADIO_SS_PIN    = RADIO_NSS_PORT;

// MCCI Catena 4610
// const uint8_t RADIO_RESET_PIN = RADIO_RESET;
// const uint8_t RADIO_TCXO_PIN  = 33;
// const uint8_t RADIO_DIO_0_PIN = 25;
// const uint8_t RADIO_MOSI_PIN  = RADIO_MOSI;
// const uint8_t RADIO_MISO_PIN  = RADIO_MISO;
// const uint8_t RADIO_SCLK_PIN  = RADIO_SCK;
// const uint8_t RADIO_SS_PIN    = RADIO_SS;

LongFi LongFi(LongFi::RadioType::SX1276, RADIO_RESET_PIN, RADIO_SS_PIN, RADIO_DIO_0_PIN);

void setup() {
  Serial.begin(9600);

  SPI.setMOSI(RADIO_MOSI_PIN);
  SPI.setMISO(RADIO_MISO_PIN);
  SPI.setSCLK(RADIO_SCLK_PIN);
  SPI.setSSEL(RADIO_SS_PIN);
  SPI.begin();

  LongFi.init(oui, device_id);
  Serial.println("Setup Start");

  // ***IMPORTANT: Only For Catena 4610
  //LongFi.enable_tcxo(RADIO_TCXO_PIN);
}

uint8_t data[8] = {1, 2, 3, 4, 5, 6, 7, 8};

void loop() {
  Serial.print("sending: ");
  Serial.println(data[0]);
  // send blocks until complete
  LongFi.send(data, sizeof(data));
  data[0]++;
}