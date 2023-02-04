#ifndef ESP32_H
#define ESP32_H

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
        
        class _getDeviceName______String_Handler : public BaseHandler {
        public:
            String name() override { return "_getDeviceName():String"; };
            String procedure(JsonArray params) override;
        };
        
        class GetFreeHeapHandler : public BaseHandler {
        public:
            String name() override { return "getFreeHeap"; };
            String procedure(JsonArray params) override;
        };
        
        class TemperatureReadHandler : public BaseHandler {
        public:
            String name() override { return "temperatureRead"; };
            String procedure(JsonArray params) override;
        };
        
        class RestartHandler : public BaseHandler {
        public:
            String name() override { return "restart"; };
            String procedure(JsonArray params) override;
        };
        
        class DelayHandler : public BaseHandler {
        public:
            String name() override { return "delay"; };
            String procedure(JsonArray params) override;
        };
        
        class AnalogReadHandler : public BaseHandler {
        public:
            String name() override { return "analogRead"; };
            String procedure(JsonArray params) override;
        };
        
        class DigitalReadHandler : public BaseHandler {
        public:
            String name() override { return "digitalRead"; };
            String procedure(JsonArray params) override;
        };
        
        class DigitalWriteHandler : public BaseHandler {
        public:
            String name() override { return "digitalWrite"; };
            String procedure(JsonArray params) override;
        };
        
        class LedcWriteHandler : public BaseHandler {
        public:
            String name() override { return "ledcWrite"; };
            String procedure(JsonArray params) override;
        };
        
        class PinModeHandler : public BaseHandler {
        public:
            String name() override { return "pinMode"; };
            String procedure(JsonArray params) override;
        };
        
        
        
        class RebootWhenHeapEmitter : public BaseEmitter {
        public:
            boolean canEmit() override;
            String emit() override;
        };
    };
}

#endif
