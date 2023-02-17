#include "./WebSocketTransport.h"

WebSocketTransport::WebSocketTransport(const char* address, const uint16_t port, const String id = "") : Transport(address, port), _id(id) {}

WebSocketTransport::~WebSocketTransport() {}

void WebSocketTransport::connect() {
    if (_socketIO.isConnected()) return;
    _socketIO.onEvent(_createSocketIOEvent());
    
    const String url = "/socket.io/?EIO=4&opnizId=" + _id;
    _socketIO.begin(_address, _port, url);
}

void WebSocketTransport::close() {
    // _socketIO.disconnect(); // MEMO: SocketIOclientクラスに継承されてない
}

boolean WebSocketTransport::send(const String rpcRequests) {
    if (!_socketIO.isConnected()) return false;
    
    // jdlog("send", rpcRequests); // DEBUG:
    
    // MEMO: 先頭に付与した`0`はackのダミーID。これがあることでNode.js側のon("request")がcallback付きでもエラーにならなくなる。
    // MEMO: 基本的にNode.js側からの値を受けてデバイスでなにかすることはない想定なので、ひとまずデバイス側のcallback実装はなしでいく。
    String socketIORequest = "0[\"request\"," + rpcRequests +"]";
    Serial.println(socketIORequest);
    _socketIO.sendEVENT(socketIORequest);
    
    return true;
}

void WebSocketTransport::receive() {
    _socketIO.loop(); // MEMO: 実質的なreceive処理はonEvent()->_createSocketIOEvent()->_socketIOEventHandler()の_rpcHandlerFunctionで処理される。
}

boolean WebSocketTransport::isConnected() {
    return _socketIO.isConnected();
}

void WebSocketTransport::keepAlive() {
    // MEMO: socket.ioライブラリでよしなにしてくれてるので特に実装せず
}



SocketIOclientEvent WebSocketTransport::_createSocketIOEvent() {
    return [this](socketIOmessageType_t type, uint8_t *payload, size_t length) {
        switch (type) {
            case sIOtype_CONNECT:
                Serial.println("[IOc] [sIOtype_CONNECT]");
                _socketIO.send(sIOtype_CONNECT, "/");
                break;
                
            case sIOtype_EVENT:
                Serial.println("[IOc] [sIOtype_EVENT]");
                _socketIOEventHandler(payload, length);
                break;
                
            case sIOtype_DISCONNECT:
                Serial.println("[IOc] [sIOtype_DISCONNECT]");
                break;
                
            case sIOtype_ACK:
            case sIOtype_ERROR:
            case sIOtype_BINARY_EVENT:
            case sIOtype_BINARY_ACK:
                Serial.println("[IOc] Other event: " + String(type));
                break;
        }
    };
}

void WebSocketTransport::_socketIOEventHandler(uint8_t *payload, size_t length) {
    // Serial.printf("[IOc] payload: %s\n", payload); // DEBUG:
    bool hasId = ((char *)payload)[0] != '[';
    int id = 0;
    if (hasId) {
        char *sptr = NULL;
        id = strtol((char *)payload, &sptr, 10);
        payload = (uint8_t *)sptr;
    }
    // Serial.printf("[IOc] get event: %s id: %d length: %d\n", payload, id, length); // DEBUG:
    
    DynamicJsonDocument payloadJson(1024);
    DeserializationError payloadJsonError = deserializeJson(payloadJson, payload, length);
    if (payloadJsonError) {
        Serial.print(F("payloadJson deserializeJson() failed: "));
        Serial.println(payloadJsonError.c_str());
        return;
    }
    
    String eventName = payloadJson[0];
    String eventParams = payloadJson[1];
    // Serial.printf("[IOc] event name: %s params: %s\n", eventName.c_str(), eventParams.c_str()); // DEBUG:
    
    if (eventName == "request") {
        Serial.println(eventParams);
        String response = _rpcHandlerFunction(eventParams); // MEMO: BaseDevice method
        
        if (hasId) {
            String socketIOResponse = String(id) + "[" + response + "]";
            // Serial.println("socketIOResponse: " + socketIOResponse); // DEBUG:
            _socketIO.send(sIOtype_ACK, socketIOResponse);
        }
    }
}
