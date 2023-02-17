#ifndef OPNIZ_BASE_HANDLER_H
#define OPNIZ_BASE_HANDLER_H

#include <ArduinoJson.h>

extern DynamicJsonDocument jsonDoc;

class BaseHandler {
public:
    virtual ~BaseHandler() = default;
    virtual String name() = 0;
    virtual String procedure(JsonArray params) = 0;
};

#endif
