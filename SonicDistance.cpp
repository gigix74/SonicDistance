/*
  SonicDistance.cpp - Library for UltraSonic sensor
  Created by Gheorghe Nedelcu, April 8, 2019.
  g_nedelcu@yahoo.com
*/

#include "Arduino.h"
#include "SonicDistance.h"

SonicDistance::SonicDistance(int trig, int echo, unsigned long min_limit, unsigned long max_limit)
: _time_ms(millis()), _last_distance(1000000)
{
  _trig = trig;
  _echo = echo;
  _min_limit = min_limit * 1000;
  _max_limit = max_limit * 1000;
}

unsigned long SonicDistance::getDuration()
{
  pinMode(_trig, OUTPUT);
  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);
  pinMode(_echo, INPUT);
  _duration = pulseIn(_echo, HIGH, 6000);
  if(_duration==0) _duration = 6000;
  return _duration;
}

unsigned long SonicDistance::getDistance()
{
  _duration = getDuration();
  _distance = _duration * 10000 / 58;
  _distance = constrain(_distance, _min_limit, _max_limit);
  return _distance;
}

unsigned long SonicDistance::getFilteredDistance(int filter_close, int filter_far)
{
  _distance = getDistance();
  _filter = -(((_last_distance - _min_limit ) * (filter_close - filter_far))/(_max_limit - _min_limit)) + filter_close;
  _raise_amount = (millis() - _time_ms) * _filter;
  _time_ms = millis();
  if ( _distance > _last_distance) {
    if ((_distance - _last_distance) > _raise_amount) {
      _distance = _last_distance + _raise_amount;
    }
  }
  _distance = constrain(_distance, _min_limit, _max_limit);
  _last_distance = _distance;
  return _distance;
}
