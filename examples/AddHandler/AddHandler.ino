#include <OpnizM5Atom.h>
#include <lib/WiFiConnector.h>
#include <M5Atom.h>

const char* ssid = "<SSID>";         // WiFiのSSIDに書き換え
const char* password = "<PASSWORD>"; // WiFiのパスワードに書き換え
WiFiConnector wifiConnector(ssid, password); // WiFi接続ヘルパーインスタンス生成

const char* address = "192.168.0.1"; // Node.js SDKを実行する端末のIPアドレスを指定
const uint16_t port = 3000;          // Node.js SDKを実行する端末のポート番号を指定
Opniz::Esp32* opniz = new Opniz::Esp32(address, port); // opnizインスタンス生成



// 独自ハンドラを作成
class DrawpixHandler : public BaseHandler {
public:
    String name() override { return "_M5.dis.drawpix(uint8_t,CRGB):void"; };
    String procedure(JsonArray params) override {
        uint8_t number = (uint8_t)params[0];
        String color = params[1];
        M5.dis.drawpix(number, str2crgb(color));
        return "true";
    }
};

// 独自エミッタを作成
class ButtonEmitter : public BaseEmitter {
public:
    boolean canEmit() override {
        M5.Btn.read();
        return M5.Btn.wasPressed();
    };
    String emit() override {
        std::vector<String> parameters;
        parameters.emplace_back("singlePush");
        return createRpcRequest("button", parameters);
    };
};



void setup() {
    // M5ATOM初期化
    M5.begin(true, false, true);
    M5.dis.setBrightness(10);
    
    // WiFi接続
    wifiConnector.connect();
    
    // 独自ハンドラ/エミッタを登録
    opniz->addHandler({ new DrawpixHandler });
    opniz->addEmitter({ new ButtonEmitter });
    
    // Node.js SDKへ接続
    opniz->connect();
}

void loop() {
    opniz->loop();         // opnizメインループ
    wifiConnector.watch(); // WiFi接続監視
}
