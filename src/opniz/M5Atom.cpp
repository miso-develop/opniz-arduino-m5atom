#include "./M5Atom.h"

Opniz::M5Atom::M5Atom(const char* address, uint16_t port, const Protocol protocol) : Esp32(address, port, protocol) {
    addHandler({
        new _getDeviceName______String_Handler,
        new _M5_begin___bool_bool_bool___void_Handler,
        new _M5_update______void_Handler,
        new _M5_dis_setBrightness___uint8_t___void_Handler,
        new _M5_dis_drawpix___uint8_t_uint8_t_CRGB___void_Handler,
        new _M5_dis_drawpix___uint8_t_CRGB___void_Handler,
        new _M5_dis_clear______void_Handler,
        new _M5_Btn_read______uint8_t_Handler,
        new _M5_Btn_isPressed______uint8_t_Handler,
        new _M5_Btn_isReleased______uint8_t_Handler,
        new _M5_Btn_wasPressed______uint8_t_Handler,
        new _M5_Btn_wasReleased______uint8_t_Handler,
        new _M5_Btn_pressedFor___uint32_t___uint8_t_Handler,
        new _M5_Btn_releasedFor___uint32_t___uint8_t_Handler,
        new _M5_Btn_wasReleasefor___uint32_t___uint8_t_Handler,
        new _M5_Btn_lastChange______uint32_t_Handler,
        new _M5_IMU_Init______int_Handler,
        new _M5_IMU_getAccelAdc___int16_t__int16_t__int16_t____void_Handler,
    });
    
    addEmitter({
        new _M5_button___shinglePush_Emitter,
    });
};



String Opniz::M5Atom::_getDeviceName______String_Handler::procedure(JsonArray params) {
    return "m5atom";
}

String Opniz::M5Atom::_M5_begin___bool_bool_bool___void_Handler::procedure(JsonArray params) {
    bool SerialEnable = (bool)params[0];
    bool I2CEnable = (bool)params[1];
    bool DisplayEnable = (bool)params[2];
    M5.begin(SerialEnable, I2CEnable, DisplayEnable);
    return "true";
}

String Opniz::M5Atom::_M5_update______void_Handler::procedure(JsonArray params) {
    M5.update();
    return "true";
}

String Opniz::M5Atom::_M5_dis_setBrightness___uint8_t___void_Handler::procedure(JsonArray params) {
    uint8_t brightness = (uint8_t)params[0];
    M5.dis.setBrightness(brightness);
    return "true";
}

String Opniz::M5Atom::_M5_dis_drawpix___uint8_t_uint8_t_CRGB___void_Handler::procedure(JsonArray params) {
    uint8_t xpos = (uint8_t)params[0];
    uint8_t ypos = (uint8_t)params[1];
    CRGB Color = str2crgb(params[2]);
    M5.dis.drawpix(xpos, ypos, Color);
    return "true";
}

String Opniz::M5Atom::_M5_dis_drawpix___uint8_t_CRGB___void_Handler::procedure(JsonArray params) {
    uint8_t Number = (uint8_t)params[0];
    CRGB Color = str2crgb(params[1]);
    M5.dis.drawpix(Number, Color);
    return "true";
}

String Opniz::M5Atom::_M5_dis_clear______void_Handler::procedure(JsonArray params) {
    M5.dis.clear();
    return "true";
}

String Opniz::M5Atom::_M5_Btn_read______uint8_t_Handler::procedure(JsonArray params) {
    return (String)M5.Btn.read();
}

String Opniz::M5Atom::_M5_Btn_isPressed______uint8_t_Handler::procedure(JsonArray params) {
    return (String)M5.Btn.isPressed();
}

String Opniz::M5Atom::_M5_Btn_isReleased______uint8_t_Handler::procedure(JsonArray params) {
    return (String)M5.Btn.isReleased();
}

String Opniz::M5Atom::_M5_Btn_wasPressed______uint8_t_Handler::procedure(JsonArray params) {
    return (String)M5.Btn.wasPressed();
}

String Opniz::M5Atom::_M5_Btn_wasReleased______uint8_t_Handler::procedure(JsonArray params) {
    return (String)M5.Btn.wasReleased();
}

String Opniz::M5Atom::_M5_Btn_pressedFor___uint32_t___uint8_t_Handler::procedure(JsonArray params) {
    uint32_t ms = (uint32_t)params[0];
    return (String)M5.Btn.pressedFor(ms);
}

String Opniz::M5Atom::_M5_Btn_releasedFor___uint32_t___uint8_t_Handler::procedure(JsonArray params) {
    uint32_t ms = (uint32_t)params[0];
    return (String)M5.Btn.releasedFor(ms);
}

String Opniz::M5Atom::_M5_Btn_wasReleasefor___uint32_t___uint8_t_Handler::procedure(JsonArray params) {
    uint32_t ms = (uint32_t)params[0];
    return (String)M5.Btn.wasReleasefor(ms);
}

String Opniz::M5Atom::_M5_Btn_lastChange______uint32_t_Handler::procedure(JsonArray params) {
    return (String)M5.Btn.lastChange();
}



String Opniz::M5Atom::_M5_IMU_Init______int_Handler::procedure(JsonArray params) {
    return (String)M5.IMU.Init();
}

String Opniz::M5Atom::_M5_IMU_getAccelAdc___int16_t__int16_t__int16_t____void_Handler::procedure(JsonArray params) {
    int16_t ax;
    int16_t ay;
    int16_t az;
    M5.IMU.getAccelAdc(&ax, &ay, &az);
    return "[" + (String)ax + "," + (String)ay + "," + (String)az + "]";
}



boolean Opniz::M5Atom::_M5_button___shinglePush_Emitter::canEmit() {
    M5.Btn.read();
    return M5.Btn.wasPressed();
}
String Opniz::M5Atom::_M5_button___shinglePush_Emitter::emit() {
    std::vector<String> params;
    params.emplace_back("singlePush");
    return createRpcRequest("button", params);
}
