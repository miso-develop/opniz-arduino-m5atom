#ifndef BASE_DEVICE_H
#define BASE_DEVICE_H

#include <unordered_map>

#include "./BaseTransport.h"
#include "./BaseHandler.h"
#include "./BaseEmitter.h"

class BaseDevice : public BaseTransport {
private:
    JsonParser _jsonParser;
    
    std::unordered_map<std::string, BaseHandler*> _handlers;
    std::vector<BaseEmitter*> _emitters;
    
    String _rpcHandler(String rpcRequest);
    std::function<String(String)> _rpcHandlerFunction = [this](String rpcRequest) -> String { return _rpcHandler(rpcRequest); };
    
public:
    BaseDevice(const char* address, const uint16_t port, const String id, const Protocol protocol);
    virtual ~BaseDevice() = default;
    
    void handleRpc();
    void emitRpc();
    void loop();
    
    void addHandler(std::vector<BaseHandler*> handlers);
    void addEmitter(std::vector<BaseEmitter*> emitters);
};

#endif
