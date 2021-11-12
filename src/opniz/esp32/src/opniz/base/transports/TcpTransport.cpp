#include "./TcpTransport.h"

TcpTransport::TcpTransport(const char* address, const uint16_t port) : Transport(address, port) {}

TcpTransport::~TcpTransport() {
    close();
};

void TcpTransport::connect() {
    connect(_timeoutCallback, _connectingSignal);
}
void TcpTransport::connect(const std::function<void()> timeoutCallback) {
    connect(timeoutCallback, _connectingSignal);
}
void TcpTransport::connect(const std::function<void(boolean)> connectingSignal) {
    connect(_timeoutCallback, connectingSignal);
}
void TcpTransport::connect(const std::function<void()> timeoutCallback, const std::function<void(boolean)> connectingSignal) {
    if (_server.operator bool() && _client.connected()) return;
    
    // connecting
    _startTime = millis();
    while (!_server.operator bool() || !_client.connected()) {
        if (!_server.operator bool()) _server.begin(_port);
        if (!_client.connected()) _client.connect(_address, _port);
        
        // Serial.println(errno);
        // MEMO: errno: 104, "Connection reset by peer" -> 119
        // MEMO: errno: 113, "Software caused connection abort" -> 119
        // MEMO: errno: 118, "Host is unreachable" -> 118
        
        if((millis() - _startTime) > _timeout) {
            _startTime = millis();
            timeoutCallback();
            return;
        }
        
        _connectingSignalState = !_connectingSignalState;
        connectingSignal(_connectingSignalState);
        
        delay(250);
    }
    
    connectingSignal(false); // 接続中表示関数実行
}

void TcpTransport::close() {
    _server.close();
    _socket.stop();
    _client.stop();
}

boolean TcpTransport::send(const String rpcRequests) {
    if (!_client.connected()) return false;
    
    jdlog("send", rpcRequests); // DEBUG:
    
    // MEMO: デバイスからのイベントを瞬間的に同時に受け取ることがあり、その場合`{...}{...}`のようなメッセージとなりJSON.parseでエラーとなる。
    // MEMO: それを回避するため必ずオブジェクト末尾に`,`を付与し`{...},`の形でデバイスからメッセージを送り、Server側にて`[]`で括り配列にする。
    String tcpRequest = rpcRequests + ",";
    _client.print(tcpRequest);
    
    // レスポンスのタイムアウト
    uint32_t _startTime = millis();
    uint16_t _timeout = 5 * 1000;
    while (_client.available() == 0) {
        if (millis() - _startTime > _timeout) {
            _client.stop();
            return false;
        }
        delay(10);
    }
    
    return true;
    
    // MEMO: とりあえずの実装としてレスポンスの値自体は特に見ない
    // while(_client.available()) {
    //     Serial.println(_client.readStringUntil('\r'));
    // }
}

void TcpTransport::receive() {
    if (!_socket.connected()) {
        _socket.stop();
        _socket = _server.available();
        
    } else {
        _socket.setTimeout(0);
        String request = _socket.readString();
        if (request == "") return;
        
        jdlog("request", request); // DEBUG:
        String response = _rpcHandlerFunction(request);
        jdlog("response", response); // DEBUG:
        if (response == "[\0]") return;
        
        _socket.print(response);
        
        dlog(esp_get_minimum_free_heap_size()); // DEBUG:
        dlog(uxTaskGetStackHighWaterMark(NULL)); // DEBUG:
        dlog(temperatureRead()); // DEBUG:
    }
}

boolean TcpTransport::isConnected() {
    return _server.operator bool() && _client.connected();
}

void TcpTransport::keepAlive() {
    connect();
}

