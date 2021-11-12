#include "./M5AtomUtil.h"

CRGB str2crgb(String color) { return strtoll(&color[1], NULL, 16) & 0xffffff; }

// M5Atom初期化
void initM5() {
    M5.begin(true, false, true);
    M5.dis.setBrightness(10);
    setCpuFrequencyMhz(160);
    
    Serial.println();
    delay(100);
}
