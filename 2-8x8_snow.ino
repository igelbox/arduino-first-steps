

// max7219_two
// Based on https://gist.github.com/nrdobie/8193350

#include <SPI.h>
#define SS_PIN 10

// MAX7219 SPI LED Driver
#define MAX7219_TEST 0x0f
#define MAX7219_BRIGHTNESS 0x0a
#define MAX7219_SCAN_LIMIT 0x0b
#define MAX7219_DECODE_MODE 0x09
#define MAX7219_SHUTDOWN 0x0C

void maxTransferCMD(uint8_t address, uint8_t value) {
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS_PIN, HIGH);
}

void maxTransferDATA(uint8_t address, uint8_t value) {
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS_PIN, HIGH);
}

void setup() {
  pinMode(SS_PIN, OUTPUT);

  SPI.setBitOrder(MSBFIRST);   // Reverse the SPI Data o/p.
  SPI.begin();                 // Start SPI
  // Run test - All LED segments lit.
  maxTransferCMD(MAX7219_TEST, 0x01);  delay(1000);
  maxTransferCMD(MAX7219_TEST, 0x00);        // Finish test mode.
  maxTransferCMD(MAX7219_DECODE_MODE, 0x00); // Disable BCD mode.
  maxTransferCMD(MAX7219_BRIGHTNESS, 0x05);  // Use lowest intensity.
  maxTransferCMD(MAX7219_SCAN_LIMIT, 0x0f);  // Scan all digits.
  maxTransferCMD(MAX7219_SHUTDOWN, 0x01);    // Turn on chip.
}

unsigned buffer[8] = {0,0,0,0,0,0,0,0};

void loop() {
  //  for(int i = 1; i <= 8; ++i) {
  //   for (int r = 1; r <= 8; ++r) {
  //     maxTransferDATA(r, (r == i) ? 255 : 0);
  //   }
  //   delay(200);
  //  }
  //  for(int i = 1; i <= 8; ++i) {
  //   for (int r = 1; r <= 8; ++r) {
  //     maxTransferDATA(r, 1 << (i-1));
  //   }
  //   delay(200);
  //  }

    for (int i = 1; i < 8; ++i) {
      int b = buffer[i];
      maxTransferDATA(i, b);
      buffer[i-1] = b;
    }
    int b = random(0, 0xff) & random(0, 0xff);
    maxTransferDATA(8, b);
    buffer[7] = b;
    delay(100);
}
