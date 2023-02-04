#include "./log.h"

void dlog(String v) { Serial.printf("%s %s \n\r", getTime().c_str(), v.c_str()); }
void dlog(char* v) { Serial.printf("%s %s \n\r", getTime().c_str(), v); }
void dlog(int v) { Serial.printf("%s %i \n\r", getTime().c_str(), v); }
void dlog(float v) { Serial.printf("%s %f \n\r", getTime().c_str(), v); }
void dlog(uint32_t v) { Serial.printf("%s %i \n\r", getTime().c_str(), v); }
void dlog(boolean v) { Serial.printf("%s %s \n\r", getTime().c_str(), v ? "true" : "false"); }

void jdlog(String v, String json) { Serial.print(getTime()); Serial.printf(" [%s] ", v.c_str()); Serial.println(json); }
