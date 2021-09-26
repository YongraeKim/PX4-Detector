#pragma once
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>

#define socket_interface class

socket_interface ISOCKET_INT
{
public:
    virtual int Create_Socket(){return -1;};
    virtual bool Bind(){return false;};
    virtual bool Accept(){return false;};
    virtual bool Listen(){return false;};
    virtual int Receive_Data(uint8_t* buffer, int32_t read_size){return -1;};
    virtual int Write_Data(uint8_t* buffer, int32_t write_size){return -1;};
    virtual void Close_Socket(){};
    virtual void* Connection_Thread(void *arg){};

protected:
    int _socket_fd = -1;
    int _socket_cs = -1;
    struct sockaddr_in _socket_address;
    struct sockaddr_in _socket_cs_address;
    socklen_t _socket_address_length;
    socklen_t _socket_address_cs_length;
    uint8_t* _received_buffer = nullptr;
    int32_t _buffersize = -1;
    int32_t _last_error_code = 0;
    bool _is_bind = false;
    bool _is_listen = false;
    bool _is_accept = false;
    pthread_t connection_thread_handle;
    int connection_thread_id;
};
