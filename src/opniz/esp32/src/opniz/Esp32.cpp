#include "./Esp32.h"

const String id = "___default___";
const Protocol protocol = WebSocket;

Opniz::Esp32::Esp32(const char* address, const uint16_t port) : BaseDevice(address, port, id, protocol) {
    _constructor();
}
Opniz::Esp32::Esp32(const char* address, const uint16_t port, const String id) : BaseDevice(address, port, id, protocol) {
    _constructor();
}
Opniz::Esp32::Esp32(const char* address, const uint16_t port, const Protocol protocol) : BaseDevice(address, port, id, protocol) {
    _constructor();
}
Opniz::Esp32::Esp32(const char* address, const uint16_t port, const String id, const Protocol protocol) : BaseDevice(address, port, id, protocol) {
    _constructor();
}

void Opniz::Esp32::_constructor() {
    addHandler({
        new _getVersion______String_Handler,
        
        new _esp_get_minimum_free_heap_size___void___uint32_t_Handler,
        new _temperatureRead______float_Handler,
        new _esp_restart___void___void_Handler,
        new _delay___uint32_t___void_Handler,
        new _analogRead___uint8_t___uint16_t_Handler,
        new _digitalRead___uint8_t___int_Handler,
        new _digitalWrite___uint8_t_uint8_t___void_Handler,
        new _ledcWrite___uint8_t_uint32_t___void_Handler,
        new _pinMode___uint8_t_uint8_t___void_Handler,
        new _ledcSetup___uint8_t_uint32_t_uint8_t___uint32_t_Handler,
        new _ledcAttachPin___uint8_t_uint8_t___void_Handler,
    });
    
    addEmitter({
    });
}



String Opniz::Esp32::_getVersion______String_Handler::procedure(JsonArray params) {
    return "OpnizEsp32@0.4.0";
}



String Opniz::Esp32::_esp_get_minimum_free_heap_size___void___uint32_t_Handler::procedure(JsonArray params) {
    return (String)esp_get_minimum_free_heap_size();
}

String Opniz::Esp32::_temperatureRead______float_Handler::procedure(JsonArray params) {
    return (String)temperatureRead();
}

String Opniz::Esp32::_esp_restart___void___void_Handler::procedure(JsonArray params) {
    esp_restart();
    return "true";
}

String Opniz::Esp32::_delay___uint32_t___void_Handler::procedure(JsonArray params) {
    uint32_t ms = (uint32_t)params[0];
    delay(ms);
    return "true";
}

String Opniz::Esp32::_analogRead___uint8_t___uint16_t_Handler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    pinMode(pin, INPUT);
    return (String)analogRead(pin);
}

String Opniz::Esp32::_digitalRead___uint8_t___int_Handler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    pinMode(pin, INPUT);
    return (String)digitalRead(pin);
}

String Opniz::Esp32::_digitalWrite___uint8_t_uint8_t___void_Handler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint8_t val = (uint8_t)params[1];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, val);
    return "true";
}

String Opniz::Esp32::_ledcWrite___uint8_t_uint32_t___void_Handler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint32_t duty = (uint32_t)params[1];
    uint8_t channel = (uint8_t)params[2];
    double freq = (double)params[3];
    uint8_t resolution_bits = (uint8_t)params[4];
    
    pinMode(pin, OUTPUT);
    if (!params[2].isNull() && !params[3].isNull() && !params[4].isNull()) ledcSetup(channel, freq, resolution_bits);
    if (!params[2].isNull()) ledcAttachPin(pin, channel);
    ledcWrite(channel, duty);
    return "true";
}

String Opniz::Esp32::_pinMode___uint8_t_uint8_t___void_Handler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint8_t mode = (uint8_t)params[1];
    pinMode(pin, mode);
    return "true";
}

String Opniz::Esp32::_ledcSetup___uint8_t_uint32_t_uint8_t___uint32_t_Handler::procedure(JsonArray params) {
    uint8_t chan = (uint8_t)params[0];
    uint32_t freq = (uint32_t)params[1];
    uint8_t bit_num = (uint8_t)params[2];
    return (String)ledcSetup(chan, freq, bit_num);
}

String Opniz::Esp32::_ledcAttachPin___uint8_t_uint8_t___void_Handler::procedure(JsonArray params) {
    uint8_t pin = (uint8_t)params[0];
    uint8_t chan = (uint8_t)params[1];
    ledcAttachPin(pin, chan);
    return "true";
}
