#include "./BaseTransport.h"

BaseTransport::BaseTransport(const char* address, const uint16_t port, const String id, const Protocol protocol) : Transport(address, port) {
    _transport = TransportCreator::create(address, port, id, protocol);
}

void BaseTransport::init(std::function<String(String)> rpcHandlerFunction) {
    _transport->init(rpcHandlerFunction);
};

void BaseTransport::connect() {
    _transport->connect();
};

void BaseTransport::close() {
    _transport->close();
};

boolean BaseTransport::send(const String rpcRequest) {
    return _transport->send(rpcRequest);
};

void BaseTransport::receive() {
    _transport->receive();
};

boolean BaseTransport::isConnected() {
    return _transport->isConnected();
}

void BaseTransport::keepAlive() {
    _transport->keepAlive();
}
