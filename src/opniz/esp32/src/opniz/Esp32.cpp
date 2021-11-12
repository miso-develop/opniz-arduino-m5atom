#include "./Esp32.h"

Opniz::Esp32::Esp32(const char* address, const uint16_t port, const Protocol protocol) : BaseDevice(address, port, protocol) {
    addHandler({
        new _getDeviceName______String_Handler,
        new GetFreeHeapHandler,
        new TemperatureReadHandler,
        new RestartHandler,
        new DelayHandler,
        new AnalogReadHandler,
        new DacWriteHandler,
        new DigitalReadHandler,
        new DigitalWriteHandler,
        new LedcWriteHandler
    });
    
    addEmitter({
        new RebootWhenHeapEmitter,
    });
}



String Opniz::Esp32::_getDeviceName______String_Handler::procedure(JsonArray params) {
    return "esp32";
}

String Opniz::Esp32::GetFreeHeapHandler::procedure(JsonArray params) {
    return (String)esp_get_minimum_free_heap_size();
}

String Opniz::Esp32::TemperatureReadHandler::procedure(JsonArray params) {
    return (String)temperatureRead();
}

String Opniz::Esp32::RestartHandler::procedure(JsonArray params) {
    esp_restart();
    return "true";
}

String Opniz::Esp32::DelayHandler::procedure(JsonArray params) {
    uint32_t ms = (uint32_t)params[0];
    delay(ms);
    return "true";
}

String Opniz::Esp32::AnalogReadHandler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    pinMode(pin, INPUT);
    return (String)analogRead(pin);
}

String Opniz::Esp32::DacWriteHandler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint8_t value = (uint8_t)params[1];
    pinMode(pin, OUTPUT);
    dacWrite(pin, value);
    return "true";
}

String Opniz::Esp32::DigitalReadHandler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    pinMode(pin, INPUT);
    return (String)digitalRead(pin);
}

String Opniz::Esp32::DigitalWriteHandler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint8_t val = (uint8_t)params[1];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    return "true";
}

String Opniz::Esp32::LedcWriteHandler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint32_t duty = (uint32_t)params[1];
    uint8_t channel = (uint8_t)params[2];
    double freq = (double)params[3];
    uint8_t resolution_bits = (uint8_t)params[4];
    pinMode(pin, OUTPUT);
    ledcSetup(channel, freq, resolution_bits);
    ledcAttachPin(pin, channel);
    ledcWrite(channel, duty);
    return "true";
}

String Opniz::Esp32::PinModeHandler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint8_t mode = (uint8_t)params[1];
    pinMode(pin, mode);
    return "true";
}



boolean Opniz::Esp32::RebootWhenHeapEmitter::canEmit() {
    return esp_get_minimum_free_heap_size() < 25600;
}
String Opniz::Esp32::RebootWhenHeapEmitter::emit() {
    std::vector<String> params;
    esp_restart();
    return createRpcRequest(".", params);
}
