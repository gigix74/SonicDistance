/*
  SonicDistance.h - Library for UltraSonic sensor
  Created by Gheorghe Nedelcu, April 8, 2019.
  g_nedelcu@yahoo.com
*/

#ifndef SonicDistance_h
#define SonicDistance_h

#include "Arduino.h"

class SonicDistance
{
  public:
    SonicDistance(int trig, int echo, unsigned long min_limit, unsigned long max_limit);
    unsigned long getDuration();
    unsigned long getDistance();
    unsigned long getFilteredDistance(int filter_close = 3000, int filter_far = 30);
  private:
    int _trig;
    int _echo;
    int _filter;
    unsigned long _min_limit;
    unsigned long _max_limit;
    unsigned long _duration;
    unsigned long _distance;
    unsigned long _last_distance;
    unsigned long _raise_amount;
    unsigned long _time_ms;
};

#endif
