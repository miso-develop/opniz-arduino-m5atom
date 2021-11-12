#include <OpnizM5Atom.h>
#include <lib/WiFiConnector.h>

const char* ssid = "<SSID>";         // WiFiのSSIDに書き換え
const char* password = "<PASSWORD>"; // WiFiのパスワードに書き換え
WiFiConnector wifiConnector(ssid, password); // WiFi接続ヘルパーインスタンス生成

const char* address = "192.168.0.1"; // Node.js SDKを実行する端末のIPアドレスを指定
const uint16_t port = 3000;          // Node.js SDKを実行する端末のポート番号を指定
Opniz::M5Atom* opniz = new Opniz::M5Atom(address, port); // opnizインスタンス生成



void setup() {
    initM5(); // M5ATOM初期化
    wifiConnector.connect(); // WiFi接続
    opniz->connect();        // Node.js SDKへ接続
}

void loop() {
    opniz->loop();         // opnizメインループ
    wifiConnector.watch(); // WiFi接続監視
}
