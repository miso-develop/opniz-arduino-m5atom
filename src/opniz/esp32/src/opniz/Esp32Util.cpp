#include "./Esp32Util.h"

// ヒープメモリがしきい値を下回ったら再起動
void rebootWhenHeap(int freeHeapThresholdSize) {
    if (esp_get_minimum_free_heap_size() < freeHeapThresholdSize) esp_restart();
}
void rebootWhenHeap() {
    const int freeHeapThresholdSize = 51200;
    rebootWhenHeap(freeHeapThresholdSize);
}
