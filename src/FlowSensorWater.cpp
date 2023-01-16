#include "Arduino.h"
#include "FlowSensorWater.h"

/**
 * @brief Construct a new FlowSensorWater::FlowSensorWater object
 *
 * @param type
 * @param pin
 */
FlowSensorWater::FlowSensorWater(uint8_t type ,uint8_t pin)
{
  _pin = pin;
  _type = type;
  switch (this->_type)
  {
  case YFS201:
    _pulse1liter = 450;
    break;

  case YFB1:
    _pulse1liter = 660;
    break;

  case OF10ZAT:
    _pulse1liter = 400;
    break;

  case OF05ZAT:
    _pulse1liter = 2174;
    break;

  default:
    break;
  }
}

/**
 * @brief
 *
 * @return uint8_t pin
 */
uint8_t FlowSensorWater::getPin()
{
  return this->_pin;
}

/**
 * @brief
 *
 * @return uint8_t sensor type
 */
uint8_t FlowSensorWater::getType()
{
  return this->_type;
}

/**
 * @brief count pulse
 *
 */
void FlowSensorWater::count()
{
  this->_pulse++;
  this->_totalpulse++;
}

/**
 * @brief
 *
 * @param userFunc
 */
void FlowSensorWater::begin(void (*userFunc)(void))
{
  pinMode(this->_pin, INPUT);
  digitalWrite(this->_pin, INPUT_PULLUP); // Optional Internal Pull-Up
  attachInterrupt(digitalPinToInterrupt(this->_pin), userFunc, RISING); // For better compatibility with any board, for example Arduino Leonardo Boards
}

/**
 * @brief
 *
 * @param calibration
 */
void FlowSensorWater::read(int calibration)
{
  this->_flowratesecound = (this->_pulse / (this->_pulse1liter + calibration)) / ((millis() - _timebefore) / 1000);
  this->_volume += (this->_pulse / (this->_pulse1liter + calibration));
  this->_pulse = 0;
}

/**
 * @brief
 *
 * @param calibration
 */
void FlowSensorWater::clearAll()
{
  this->_totalpulse = 0;
  this->_pulse = 0;
  this->_volume = 0;
}

/**
 * @brief
 *
 * @return int total pulse
 */
int FlowSensorWater::getPulse()
{
  return this->_totalpulse;
}

/**
 * @brief
 *
 * @return float flow rate / minute
 */
float FlowSensorWater::getFlowRate_m()
{
  this->_flowrateminute = this->_flowratesecound * 60;
  return this->_flowrateminute;
}

/**
 * @brief
 *
 * @return float flow rate / secound
 */
float FlowSensorWater::getFlowRate_s()
{
  return this->_flowratesecound;
}

/**
 * @brief
 *
 * @return float volume
 */
float FlowSensorWater::getVolume()
{
  return this->_volume;
}
