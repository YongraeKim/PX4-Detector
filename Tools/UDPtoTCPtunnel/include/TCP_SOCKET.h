#pragma once
#include <vector>
#include "ISOCKET_INT.h"
#include "TCP_CONNECTION.h"

enum class TCP_SOCKET_TYPE
{
    TCP_SOCKET_SERVER,
    TCP_SOCKET_CLIENT
};


class TCP_SOCKET : public ISOCKET_INT
{
public:
    TCP_SOCKET(const char *ipv4_address, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE socket_type);
    TCP_SOCKET(const char *ipv4_address, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE socket_type, int max_connection_number);
    virtual ~TCP_SOCKET();
    void Initialize(const char *ipv4_address, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE socket_type);
    virtual int Create_Socket() override;
    virtual bool Bind() override;
    virtual bool Accept() override;
    virtual bool Listen() override;
    virtual int Receive_Data(uint8_t* buffer, int32_t read_size) override;
    virtual int Receive_Data(std::queue<BUFFER_DATA>&queue_data) override;
    virtual int Write_Data(uint8_t* buffer, int32_t write_size) override;
    virtual int Write_Data(std::queue<BUFFER_DATA>&queue_data) override;
    virtual void Close_Socket() override;
    virtual void* Connection_Thread(void *arg) override;
    static void* Connection_Thread_Member(void* arg);
    static void Connection_Callback_Member(void* class_prt, void* connection_ptr);
    void Connection_Callback(void* arg);
    
    
private:
    int _max_connection_number;
    std::vector<tcp_connection::TCP_CONNECTION*> _connection;
    int exit_code = -1;
};