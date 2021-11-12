#include "./JsonParser.h"

JsonParser::JsonParser() : _jsonDoc(_size) {}
JsonParser::JsonParser(uint16_t size) : _jsonDoc(size), _size(size) {}

JsonObject JsonParser::parse(String jsonStr) {
    deserializeJson(_jsonDoc, jsonStr);
    return _jsonDoc.as<JsonObject>();
}

JsonArray JsonParser::parseArray(String jsonStr) {
    deserializeJson(_jsonDoc, jsonStr);
    return _jsonDoc.as<JsonArray>();
}

String JsonParser::stringify(DynamicJsonDocument jsonDoc) {
    String jsonStr;
    serializeJson(jsonDoc, jsonStr);
    return jsonStr;
}

JsonObject JsonParser::createJson() { return createJson(_size); }
JsonObject JsonParser::createJson(uint16_t size) {
    DynamicJsonDocument jsonDoc(size);
    return jsonDoc.to<JsonObject>();
}

JsonArray JsonParser::createJsonArray() { return createJsonArray(_size); }
JsonArray JsonParser::createJsonArray(uint16_t size) {
    DynamicJsonDocument jsonDoc(size);
    return jsonDoc.to<JsonArray>();
}

void JsonParser::setSize(uint16_t size) { _size = size; }
