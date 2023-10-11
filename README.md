# opniz Arduino Library for M5ATOM

<div align="center"><img src="https://user-images.githubusercontent.com/22117028/150321839-e1e73dcb-d4b6-4bac-92b9-b1501ff3b092.png" alt="logo"></div>

> **❗ このライブラリの使用は非推奨です！**  
> **❗ [opniz Arduino Library for M5Unified](https://github.com/miso-develop/opniz-arduino-m5unified)をご使用ください！**  

opnizとはM5StackデバイスをNode.js（JavaScript / TypeScript）からobnizライクに実装できるオープンソースフレームワークです。  
Node.js SDKおよびArduinoライブラリがあり、WebSocketで相互通信を行います。  

しくみとしてはM5StackデバイスおよびNode.js SDK間にてJSON形式のRPCメッセージをやりとりし、相互に定義されたメソッドを呼び合います。  

![overview](https://user-images.githubusercontent.com/22117028/274111780-1f1e22ec-66ac-4cd0-bee3-1a19ee2eb65c.png)



## Arduinoライブラリ

本リポジトリはM5ATOM向けのopniz Arduinoライブラリ リポジトリとなります。  
Node.js SDKからのRPCリクエストを処理するハンドラと、ESP32デバイスからのRPCイベントを発火するエミッタを実装したデバイスクラスを提供します。  
Arduino IDEおよびPlatformIOに対応しています。  



## 対応デバイス

* M5ATOM Matrix
* M5ATOM Lite
* M5ATOM Echo
* M5ATOM U
* その他ESP32、ESP32-PICO-D4、ESP32-S3デバイス



## インストール方法

opniz CLIを使用する方法と、Arduinoを使用する方法があります。  

### [opniz CLI](https://github.com/miso-develop/opniz-cli)でのインストール

opniz CLIとはopniz Arduino LibraryのBasicスケッチをコマンドから簡単に書き込めるCLIツールです。  
npmにリリースされているので、以下の`npm install`コマンドでインストールできます。  

```sh
npm install -g opniz-cli
```

opniz CLIインストール後に以下のコマンドを実行するとBasicスケッチをデバイスへ書き込みます。  
デバイスのシリアルポートやWi-FiのSSID/パスワードといった情報が必要ですが、対話モードで動的に選択肢を取得し表示してくれます。  

```sh
opniz upload
```

<img src="https://user-images.githubusercontent.com/22117028/148371155-569e2ae3-7655-4c5c-a38f-4d13dd1ada4b.gif" width="640">

### Arduinoでのインストール

まだArduinoライブラリマネージャーにはリリースしていないため、GitHubリポジトリよりZIPをダウンロードのうえ、Arduino IDEにて「.ZIP形式のライブラリをインストール...」を選択しダウンロードしたZIPをライブラリへ追加してください。

### GitHubリポジトリからのZIPダウンロード

「Code」ボタンを押すと表示されるメニューより「Download ZIP」を選択しダウンロードします。  

![github-download](https://user-images.githubusercontent.com/22117028/150333710-67249a99-37c0-42b6-8efb-a320ec6147e5.png)

### Arduino IDEでの.ZIP形式ライブラリのインストール

Arduinoのメニューより「スケッチ」→「ライブラリをインクルード」→「.ZIP形式のライブラリをインストール...」と選択し、ダウンロードしたZIPを選択します。  

![arduino-library-include](https://user-images.githubusercontent.com/22117028/150333713-5757f724-0590-4cc6-ad15-9e51a94f6cb5.png)

### 依存ライブラリのインストール

[ArduinoJson](https://github.com/bblanchon/ArduinoJson)、[WebSockets](https://github.com/Links2004/arduinoWebSockets)、[M5Atom](https://github.com/m5stack/M5Atom)、[FastLED](https://github.com/FastLED/FastLED)ライブラリが別途必要となります。  



## 使い方

以下のコードは`Opniz::M5ATOM`クラスを使用した最小限のコードです。  
Arduino IDEメニューの「スケッチ例」→「opniz」→「Basic」にあるコードと同等です。  

opnizインスタンスの生成、Wi-Fi接続、Node.js SDKへの接続、そして`loop`関数内の`opniz->loop()`にてNode.js SDKからのRPCリクエストの待ち受け・ハンドリングと、デバイスへ実装されているRPCイベントの発火を行っています。  

M5ATOMのLED制御やボタンイベントは`Opniz::M5Atom`クラスにて実装されているので、このコードをデバイスへ書き込むだけでNode.js SDKから制御可能となります。  
`ssid`、`password`をお使いのWi-Fiのものに、`address`、`port`をそれぞれNode.js SDKを実行する端末のものに書き換え、デバイスにスケッチを書き込んでみてください。  
opniz Node.js SDKのサンプルコードと連携可能になります。  

```cpp
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
    
    wifiConnector.setTimeoutCallback([]() { esp_restart(); }); // WiFi接続タイムアウト時にリブート
    wifiConnector.connect(); // WiFi接続
    
    Serial.printf("opniz server address: %s\nopniz server port: %u\n\n", opniz->getAddress(), opniz->getPort()); // Node.js SDK接続情報を表示
    opniz->connect(); // Node.js SDKへ接続
}

void loop() {
    opniz->loop(); // opnizメインループ
    wifiConnector.watch(); // WiFi接続監視
}
```

### ハンドラ、エミッタの拡張

実装を追加して独自に拡張できます。  
ハンドラやエミッタの追加は[`examples/AddHandler/AddHandler.ino`](./examples/AddHandler/AddHandler.ino)（以下のコード）が参考になると思います。  
このコードではEsp32クラスをもとにM5ATOMのLED制御ハンドラーとボタンイベントエミッターを拡張し追加しています。  

```cpp
#include <OpnizM5Atom.h>
#include <lib/WiFiConnector.h>
#include <M5Atom.h>

const char* ssid = "<SSID>";         // WiFiのSSIDに書き換え
const char* password = "<PASSWORD>"; // WiFiのパスワードに書き換え
WiFiConnector wifiConnector(ssid, password); // WiFi接続ヘルパーインスタンス生成

const char* address = "192.168.0.1"; // Node.js SDKを実行する端末のIPアドレスを指定
const uint16_t port = 3000;          // Node.js SDKを実行する端末のポート番号を指定
Opniz::Esp32* opniz = new Opniz::Esp32(address, port); // M5AtomクラスではなくEsp32クラスでopnizインスタンス生成



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
    M5.begin(true, false, true); // M5ATOM初期化
    M5.dis.setBrightness(10); // LED輝度調整
    
    wifiConnector.setTimeoutCallback([]() { esp_restart(); }); // WiFi接続タイムアウト時にリブート
    wifiConnector.connect(); // WiFi接続
    
    opniz->addHandler({ new DrawpixHandler }); // 独自ハンドラーを登録
    opniz->addEmitter({ new ButtonEmitter }); // 独自エミッターを登録
    
    Serial.printf("opniz server address: %s\nopniz server port: %u\n\n", opniz->getAddress(), opniz->getPort()); // Node.js SDK接続情報を表示
    opniz->connect(); // Node.js SDKへ接続
}

void loop() {
    opniz->loop(); // opnizメインループ
    wifiConnector.watch(); // WiFi接続監視
}
```



## 利用可能な通信プロトコル

opniz Arduinoライブラリでは以下の通信プロトコルを実装しています。  
デフォルトでは`WebSocket (Client)`が使用されます。  

* WebSocket (Client)
* TCP (Server/Client同居)

opniz Node.js SDKでは以下の通信プロトコルを実装しています。  
デフォルトでは`WebSocket (Server)`が使用されます。  

* WebSocket (Server)
* WebSocket (Client)
* TCP (Server/Client同居)

使用するプロトコルによりopnizのコンストラクタパラメータが変わってきます。  

|プロトコル|コンストラクタパラメータ|パラメータ内容|
|---|---|---|
|WebSocket (Client)|`Opniz::M5Atom(address, port, id)`|`address`: 接続先のopnizのIPアドレスまたはhostnameを指定します<br>`port`: 接続先のopnizのWebSocket Serverポート番号を指定します<br>`id`: [opniz Server](https://github.com/miso-develop/opniz-server)を経由してopniz Node.js SDKと接続する場合に、opniz Node.js SDKで指定した`id`と同じ値を指定します（省略可）|
|TCP (Server/Client同居)|`Opniz::M5Atom(address, port, protocol)`|`address`: 接続先のopnizのIPアドレスを指定します<br>`port`: 接続先のopnizのTCP Serverポート番号を指定します<br>`protocol`: Protocol::TCPを指定します（文字列ではありません。enumを用意しています）|



## 関連リポジトリ

* [opniz SDK for Node.js](https://github.com/miso-develop/opniz-sdk-nodejs)
	* opnizデバイスをNode.jsから遠隔制御するためのSDK
* [opniz Arduino Library for M5Unified](https://github.com/miso-develop/opniz-arduino-m5unified)
	* M5Unified向けArduinoライブラリ
* [opniz Arduino Library for ESP32](https://github.com/miso-develop/opniz-arduino-esp32)
	* ESP32向けArduinoライブラリ
* [opniz CLI](https://github.com/miso-develop/opniz-cli)
	* opniz Arduino LibraryのBasicスケッチをコマンドから簡単に書き込めるCLIツール
* [opniz Server](https://github.com/miso-develop/opniz-server)
	* opniz Node.js SDKやopnizデバイスからのJSON RPCメッセージを中継するWebSocketサーバ



## ライセンス

[MIT](./LICENSE)
