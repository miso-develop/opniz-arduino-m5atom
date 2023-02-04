#ifndef M5ATOM_H
#define M5ATOM_H

#include <M5Atom.h>

#include "./esp32/src/opniz/Esp32.h"

#include "./M5AtomUtil.h"

namespace Opniz { // MEMO: 本家M5Atomと名前衝突してしまったのでnamespaceで回避
    class M5Atom : public Esp32 {
    private:
        void _constructor();
    public:
        M5Atom(const char* address, const uint16_t port);
        M5Atom(const char* address, const uint16_t port, const String id);
        M5Atom(const char* address, const uint16_t port, const Protocol protocol);
        M5Atom(const char* address, const uint16_t port, const String id, const Protocol protocol);
        ~M5Atom() {};

        class _getDeviceName______String_Handler : public BaseHandler {
        public:
            String name() override { return "_getDeviceName():String"; };
            String procedure(JsonArray params) override;
        };

        class _M5_begin___bool_bool_bool___void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.begin(bool,bool,bool):void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_update______void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.update():void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_dis_setBrightness___uint8_t___void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.dis.setBrightness(uint8_t):void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_dis_drawpix___uint8_t_uint8_t_CRGB___void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.dis.drawpix(uint8_t,uint8_t,CRGB):void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_dis_drawpix___uint8_t_CRGB___void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.dis.drawpix(uint8_t,CRGB):void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_dis_fillpix___CRGB___void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.dis.fillpix(CRGB):void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_dis_clear______void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.dis.clear():void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_dis_setWidthHeight___uint16_t_uint16_t___void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.dis.setWidthHeight(uint16_t,uint16_t):void"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_read______uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.read():uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_isPressed______uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.isPressed():uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_isReleased______uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.isReleased():uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_wasPressed______uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.wasPressed():uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_wasReleased______uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.wasReleased():uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_pressedFor___uint32_t___uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.pressedFor(uint32_t):uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_releasedFor___uint32_t___uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.releasedFor(uint32_t):uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_wasReleasefor___uint32_t___uint8_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.wasReleasefor(uint32_t):uint8_t"; };
            String procedure(JsonArray params) override;
        };

        class _M5_Btn_lastChange______uint32_t_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.Btn.lastChange():uint32_t"; };
            String procedure(JsonArray params) override;
        };



        class _M5_IMU_Init______int_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.IMU.Init():int"; };
            String procedure(JsonArray params) override;
        };

        class _M5_IMU_getAccelAdc___int16_t__int16_t__int16_t____void_Handler : public BaseHandler {
        public:
            String name() override { return "_M5.IMU.getAccelAdc(int16_t*,int16_t*,int16_t*):void"; };
            String procedure(JsonArray params) override;
        };



        class _M5_button___shinglePush_Emitter : public BaseEmitter {
        public:
            boolean canEmit() override;
            String emit() override;
        };
    };
}

#endif
