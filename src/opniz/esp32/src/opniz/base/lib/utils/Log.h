#ifndef OPNIZ_LOG_H
#define OPNIZ_LOG_H

#include "./getTime.h"

void dlog(String v);
void dlog(char* v);
void dlog(int v);
void dlog(float v);
void dlog(uint32_t v);
void dlog(boolean v);

void jdlog(String v, String json);

#endif
