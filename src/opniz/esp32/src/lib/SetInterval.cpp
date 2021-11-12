#include "./SetInterval.h"

SetInterval::SetInterval(uint16_t interval) {
    _interval = interval;
}

boolean SetInterval::canExec() {
    if (millis() - _execTime < _interval) return false;
    _execTime = millis();
    return true;
}
