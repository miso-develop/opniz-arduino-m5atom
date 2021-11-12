#ifndef LOG_H
#define LOG_H

#include "./getTime.h"

void log(String v);
void log(char* v);
void log(int v);
void log(float v);
void log(uint32_t v);
void log(boolean v);

void dlog(String v);
void dlog(char* v);
void dlog(int v);
void dlog(float v);
void dlog(uint32_t v);
void dlog(boolean v);

void jdlog(String v, String json);

#endif
