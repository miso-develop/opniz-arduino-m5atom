#ifndef OPNIZ_TRANSPORT_CREATOR_H
#define OPNIZ_TRANSPORT_CREATOR_H

#include "./Transport.h"
#include "./TcpTransport.h"
#include "./WebSocketTransport.h"

typedef enum {
    WebSocket,
    TCP,
} Protocol;

class TransportCreator final {
public:
    TransportCreator() = delete;
    ~TransportCreator() = delete;
    
    static Transport* create(const char* address, const uint16_t port, const String id, const Protocol protocol) {
        switch (protocol) {
            case WebSocket:
                return new WebSocketTransport(address, port, id);
                break;
            case TCP:
                return new TcpTransport(address, port);
                break;
            default:
                return new WebSocketTransport(address, port, id);
                break;
        }
    }
};

#endif
