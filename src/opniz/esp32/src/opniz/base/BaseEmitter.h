#ifndef OPNIZ_BASE_EMITTER_H
#define OPNIZ_BASE_EMITTER_H

#include <vector>
#include "./lib/JsonParser.h"

class BaseEmitter {
private:
    JsonParser _jsonParser;
    uint16_t _size = 256;
    
protected:
    // TODO: ほんとは配列でもちたいけどstd::vector<String>だとemplace_back実行時にリブートしちゃう…
    // std::vector<String> attributes;
    String attribute;
    
    String createRpcRequest(String method) {
        std::vector<String> params;
        return createRpcRequest(method, params);
    }
    String createRpcRequest(String method, std::vector<String> params) {
        return createRpcRequest(method, params, _size);
    }
    String createRpcRequest(String method, uint16_t size) {
        std::vector<String> params;
        return createRpcRequest(method, params, size);
    }
    String createRpcRequest(String method, std::vector<String> params, uint16_t size) {
        DynamicJsonDocument jsonDoc(size);
        JsonObject rpcRequestJson = jsonDoc.to<JsonObject>();
        rpcRequestJson["method"] = method;
        
        if (params.size() > 0) {
            JsonArray paramsJson = rpcRequestJson.createNestedArray("params");
            for (String parameter : params) { paramsJson.add(parameter); }
        }
        
        return _jsonParser.stringify(rpcRequestJson);
    }
    
    void setSize(uint16_t size) { _size = size; }
    
public:
    virtual ~BaseEmitter() = default;
    virtual boolean canEmit() = 0;
    virtual String emit() = 0;
};

#endif
