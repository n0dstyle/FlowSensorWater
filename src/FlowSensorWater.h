#ifndef FlowSensorWater_h
#define FlowSensorWater_h

#include "Arduino.h"

static const uint8_t YFS201{1};
static const uint8_t YFB1{2};
static const uint8_t OF10ZAT{3};
static const uint8_t OF10ZZT{3};
static const uint8_t OF05ZAT{4};
static const uint8_t OF05ZZT{4};

class FlowSensorWater
{
private:
  uint8_t _pin;
  uint8_t _type;
  volatile int _totalpulse;
  volatile int _pulse;
  float _pulse1liter;
  float _flowrateminute;
  float _flowratesecound;
  float _volume;
  long _timebefore = 0;

public:
  FlowSensorWater(uint8_t type ,uint8_t pin);
  uint8_t getPin();
  uint8_t getType();
  void begin(void (*userFunc)(void));
  void read(int calibration = 0);
  void count();
  int getPulse();
  float getFlowRate_m();
  float getFlowRate_s();
  float getVolume();
  void clearAll();
};

#endif
