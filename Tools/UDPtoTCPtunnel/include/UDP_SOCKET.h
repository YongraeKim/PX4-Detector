#pragma once
#include "ISOCKET_INT.h"

enum class UDP_SOCKET_TYPE
{
    UDP_SERVER,
    UDP_CLIENT
};

class UDP_SOCKET : public ISOCKET_INT
{
public:
    UDP_SOCKET(const char* ipv4_address,uint16_t port, int32_t buffersize, UDP_SOCKET_TYPE socket_type);
    virtual ~UDP_SOCKET();
    virtual int Create_Socket() override;
    virtual bool Bind() override;
    virtual int Receive_Data(uint8_t* buffer, int32_t read_size) override;
    virtual int Write_Data(uint8_t* buffer, int32_t write_size) override;
    virtual void Close_Socket() override;
};