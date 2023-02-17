#ifndef OPNIZ_JSON_PARSER_H
#define OPNIZ_JSON_PARSER_H

#include <ArduinoJson.h>

class JsonParser {
private:
    DynamicJsonDocument _jsonDoc;
    uint16_t _size = 256;
    
public:
    JsonParser();
    JsonParser(uint16_t size);
    ~JsonParser() {};
    
    JsonObject parse(String jsonStr);
    JsonArray parseArray(String jsonStr);
    String stringify(DynamicJsonDocument jsonDoc);
    JsonObject createJson();
    JsonObject createJson(uint16_t size);
    JsonArray createJsonArray();
    JsonArray createJsonArray(uint16_t size);
    void setSize(uint16_t size);
};

#endif
