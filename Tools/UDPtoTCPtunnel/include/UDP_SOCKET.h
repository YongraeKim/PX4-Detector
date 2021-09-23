#pragma once
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

enum class UDP_SOCKET_TYPE
{
    UDP_SERVER,
    UDP_CLIENT
};

class UDP_SOCKET
{
public:
    UDP_SOCKET(const char* ipv4_address,uint16_t port, int32_t buffersize, UDP_SOCKET_TYPE socket_type);
    virtual ~UDP_SOCKET();
    int Create_Socket();
    bool Bind_UDP();
    int Receive_UDP_Data(uint8_t* buffer, int32_t read_size);
    bool Write_UDP_Data(uint8_t* buffer, int32_t write_size);
    void Close_UDP();
    void UDP_Receive_Thread();
private:
    int _socket_fd = -1;
    struct sockaddr_in _socket_address;
    struct sockaddr_in _socket_address_my;
    socklen_t _socket_address_length;
    socklen_t _socket_address_my_length;
    uint8_t* _received_buffer = nullptr;
    int32_t _buffersize = -1;
    int32_t _last_error_code = 0;
    bool _is_bind = false;
};