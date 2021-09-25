#pragma once
#include <vector>
#include "ISOCKET_INT.h"


enum class TCP_SOCKET_TYPE
{
    TCP_SOCKET_SERVER,
    TCP_SOCKET_CLIENT
};

struct TCP_CONNECTION
{
    struct sockaddr_in address;
    int socket_fd;
    bool operator()(TCP_CONNECTION connection)
    {
        return (connection.address.sin_addr.s_addr == address.sin_addr.s_addr &&
            connection.address.sin_port == address.sin_port);
    }
    
};


class TCP_SOCKET : public ISOCKET_INT
{
public:
    TCP_SOCKET(const char *ipv4, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE type);
    TCP_SOCKET(const char *ipv4, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE type, int max_connection_number);
    virtual ~TCP_SOCKET();
    virtual int Create_Socket() override;
    virtual bool Bind() override;
    virtual bool Accept() override;
    virtual bool Listen() override;
    virtual int Receive_Data(uint8_t* buffer, int32_t read_size) override;
    virtual int Write_Data(uint8_t* buffer, int32_t write_size) override;
    virtual void Close_Socket() override;
    
private:
    int _max_connection_number;
    std::vector<TCP_CONNECTION> _connection;
};