#ifndef ESP32_UTIL_H
#define ESP32_UTIL_H

#include <esp32-hal.h>

void rebootWhenHeap(int freeHeapThresholdSize);
void rebootWhenHeap();

#endif
