#include "./BaseDevice.h"

BaseDevice::BaseDevice(const char* address, const uint16_t port, const Protocol protocol) : BaseTransport(address, port, protocol) {
    BaseTransport::init(_rpcHandlerFunction); // MEMO: Transport method
}

String BaseDevice::_rpcHandler(String rpcRequests) {
    Serial.println(rpcRequests);
    DynamicJsonDocument _rpcResponseJson(1024);
    JsonArray rpcRequestArray = _jsonParser.parseArray(rpcRequests);
    JsonArray rpcResponseArray = _rpcResponseJson.to<JsonArray>();
    for (JsonObject rpcRequest : rpcRequestArray) {
        BaseHandler* handler = _handlers[rpcRequest["method"]];
        String response = (boolean)handler ? handler->procedure(rpcRequest["params"]) : "notmatch";
        rpcResponseArray.add(response);
    }
    return _jsonParser.stringify(_rpcResponseJson);
};

void BaseDevice::handleRpc() {
    receive(); // MEMO: Transport method
}

void BaseDevice::emitRpc() {
    for (BaseEmitter* emitter : _emitters) {
        if (emitter->canEmit()) {
            send("[" + emitter->emit() + "]"); // MEMO: Transport method
        }
    }
}

void BaseDevice::loop() {
    handleRpc();
    emitRpc();
    keepAlive();
}

void BaseDevice::addHandler(std::vector<BaseHandler*> handlers) {
    for (BaseHandler* handler : handlers) _handlers[handler->name().c_str()] = handler;
}

void BaseDevice::addEmitter(std::vector<BaseEmitter*> emitters) {
    copy(emitters.begin(), emitters.end(), back_inserter(_emitters));
}
