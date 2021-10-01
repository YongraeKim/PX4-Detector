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
    virtual int Receive_Data(std::queue<BUFFER_DATA> &receive_data) override;
    virtual int Receive_Data() override;
    virtual int Write_Data(uint8_t* buffer, int32_t write_size) override;
    virtual int Write_Data(std::queue<BUFFER_DATA> &write_data) override;
    virtual int Write_Data() override;
    virtual void Close_Socket() override;
    std::queue<BUFFER_DATA> receive_queue;
    std::queue<BUFFER_DATA> transmit_queue;
private:
    
    
};