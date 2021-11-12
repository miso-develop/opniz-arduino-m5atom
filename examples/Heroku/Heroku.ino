#include <OpnizM5Atom.h>
#include <lib/WiFiConnector.h>

const char* ssid = "<SSID>";         // WiFiのSSIDに書き換え
const char* password = "<PASSWORD>"; // WiFiのパスワードに書き換え

WiFiConnector wifiConnector(ssid, password); // WiFi接続ヘルパーインスタンス生成
Opniz::M5Atom* opniz = new Opniz::M5Atom("glacial-caverns-42373.herokuapp.com", 80); // opnizインスタンス生成（テスト用Herokuサーバへ接続）

void setup() {
    initM5(); // M5ATOM初期化
    wifiConnector.connect(); // WiFi接続
    opniz->connect();        // Node.js SDKへ接続
}

void loop() {
    opniz->loop();         // opnizメインループ
    wifiConnector.watch(); // WiFi接続監視
}
