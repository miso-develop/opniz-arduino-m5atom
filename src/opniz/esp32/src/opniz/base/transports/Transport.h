#ifndef OPNIZ_TRANSPORT_H
#define OPNIZ_TRANSPORT_H

#include "Arduino.h"
#include <memory>

class Transport {
protected:
    const char* _address;
    const uint16_t _port;
    
    std::function<String(String)> _rpcHandlerFunction;
    
public:
    Transport(const char* address, const uint16_t port) : _address(address), _port(port) {}
    virtual ~Transport() = default;
    
    void init(std::function<String(String)> rpcHandlerFunction) { _rpcHandlerFunction = rpcHandlerFunction; };
    
    const char* getAddress() { return _address; };
    const uint16_t getPort() { return _port; };
    
    virtual void connect() = 0;
    virtual void close() = 0;
    
    virtual boolean send(const String rpcRequest) = 0;
    virtual void receive() = 0;
    
    virtual boolean isConnected() = 0;
    virtual void keepAlive() = 0;
};

#endif
