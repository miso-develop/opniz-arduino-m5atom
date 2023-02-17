#ifndef OPNIZ_ESP32_H
#define OPNIZ_ESP32_H

#include <Arduino.h>

#include "./base/BaseDevice.h"

#include "./Esp32Util.h"

namespace Opniz {
    class Esp32 : public BaseDevice {
    private:
        void _constructor();
        
    public:
        Esp32(const char* address, const uint16_t port);
        Esp32(const char* address, const uint16_t port, const String id);
        Esp32(const char* address, const uint16_t port, const Protocol protocol);
        Esp32(const char* address, const uint16_t port, const String id, const Protocol protocol);
        ~Esp32() {};
        
        class _getVersion______String_Handler : public BaseHandler { public: String name() override { return "_getVersion(void):String"; }; String procedure(JsonArray params) override; };
        
        class _esp_get_minimum_free_heap_size___void___uint32_t_Handler : public BaseHandler { public: String name() override { return "_esp_get_minimum_free_heap_size(void):uint32_t"; }; String procedure(JsonArray params) override; };
        class _temperatureRead______float_Handler : public BaseHandler { public: String name() override { return "_temperatureRead():float"; }; String procedure(JsonArray params) override; };
        class _esp_restart___void___void_Handler : public BaseHandler { public: String name() override { return "_esp_restart(void):void"; }; String procedure(JsonArray params) override; };
        class _delay___uint32_t___void_Handler : public BaseHandler { public: String name() override { return "_delay(uint32_t):void"; }; String procedure(JsonArray params) override; };
        class _analogRead___uint8_t___uint16_t_Handler : public BaseHandler { public: String name() override { return "_analogRead(uint8_t):uint16_t"; }; String procedure(JsonArray params) override; };
        class _digitalRead___uint8_t___int_Handler : public BaseHandler { public: String name() override { return "_digitalRead(uint8_t):int"; }; String procedure(JsonArray params) override; };
        class _digitalWrite___uint8_t_uint8_t___void_Handler : public BaseHandler { public: String name() override { return "_digitalWrite(uint8_t,uint8_t):void"; }; String procedure(JsonArray params) override; };
        class _ledcWrite___uint8_t_uint32_t___void_Handler : public BaseHandler { public: String name() override { return "_ledcWrite(uint8_t,uint32_t):void"; }; String procedure(JsonArray params) override; };
        class _pinMode___uint8_t_uint8_t___void_Handler : public BaseHandler { public: String name() override { return "_pinMode(uint8_t,uint8_t):void"; }; String procedure(JsonArray params) override; };
        class _ledcSetup___uint8_t_uint32_t_uint8_t___uint32_t_Handler : public BaseHandler { public: String name() override { return "_ledcSetup(uint8_t,uint32_t,uint8_t):uint32_t"; }; String procedure(JsonArray params) override; };
        class _ledcAttachPin___uint8_t_uint8_t___void_Handler : public BaseHandler { public: String name() override { return "_ledcAttachPin(uint8_t,uint8_t):void"; }; String procedure(JsonArray params) override; };
    };
}

#endif
