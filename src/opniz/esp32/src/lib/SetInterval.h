#ifndef SET_INTERVAL_H
#define SET_INTERVAL_H

#include <Arduino.h>

class SetInterval {
private:
    uint32_t _execTime = 0;
    uint16_t _interval = 5000;
    
public:
    SetInterval() {};
    SetInterval(uint16_t interval);
    ~SetInterval() {};
    
    boolean canExec();
};

#endif
