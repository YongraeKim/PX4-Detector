#include "UDP_SOCKET.h"
using namespace std;
UDP_SOCKET::UDP_SOCKET(const char* ipv4_address,uint16_t port, int32_t buffersize, UDP_SOCKET_TYPE socket_type)
{
    memset(&_socket_address,0,sizeof(_socket_address));
    if(socket_type == UDP_SOCKET_TYPE::UDP_CLIENT)
    {
        inet_aton(ipv4_address,(struct in_addr*)&_socket_address.sin_addr.s_addr);
    }
    else
    {
        _socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    _socket_address.sin_family = AF_INET;
    _socket_address.sin_port = htons(port);
    _received_buffer = new uint8_t[buffersize];
    this->_buffersize = buffersize;
}

UDP_SOCKET::~UDP_SOCKET()
{
    Close_Socket();
}

int UDP_SOCKET::Create_Socket()
{
    _socket_fd = socket(AF_INET,SOCK_DGRAM,0);
    _last_error_code = _socket_fd;
    if(_last_error_code<0)
    {
        cout <<"[UDP_ERROR] Failed socket creation"<<endl;
    }
    else
    {
        cout <<"[UDP_INFO] Socket created"<<endl;
    }
    return _last_error_code;
}

bool UDP_SOCKET::Bind()
{

    _last_error_code = bind(_socket_fd,(struct sockaddr*)&_socket_address,sizeof(_socket_address));
    if(_last_error_code>-1)
    {
        cout <<"[UDP_INFO] Bind succeeded"<<endl;
        
        _is_bind = true;
    }
    else
    {
        cout <<"[UDP_ERROR] Failed binding UDP"<<endl;
        _is_bind = false;
    }
    return _is_bind;
}


int UDP_SOCKET::Receive_Data(uint8_t* buffer, int32_t read_size)
{
    int received_size = -1;
    if(_is_bind)
    {
        received_size = recvfrom(_socket_fd,
                                    _received_buffer,
                                    _buffersize,0,
                                    (struct sockaddr*)&_socket_address,
                                    &_socket_address_length);
        if(read_size>=received_size && read_size<=_buffersize)
        {
            memcpy(buffer,_received_buffer,received_size);
        }
        else
        {
            memcpy(buffer,_received_buffer,_buffersize);
        }
    }
    return received_size;
}
int UDP_SOCKET::Write_Data(uint8_t* buffer, int32_t write_size)
{
    int transmitted_size = -1;
    if(_is_bind)
    {
        if(write_size>0)
        {
            transmitted_size = sendto(_socket_fd,buffer,write_size,0,
                                    (struct sockaddr*)&_socket_address,sizeof(_socket_address)); 
            if(transmitted_size>0)
            {
                for(int i=0;i<write_size;i++)
                {
                    printf("%x ",buffer[i]);
                }
                printf("\r\n");

            }
            else cout <<"error transmit udp"<<endl;

        }
        
    }    
    return transmitted_size;
}

void UDP_SOCKET::Close_Socket()
{
    if(_socket_fd!=-1)
    {
        close(_socket_fd);
        _socket_fd = -1;
    }
    if(_received_buffer!=nullptr)
    {
        delete _received_buffer;
        _received_buffer = nullptr;
        _buffersize = -1;
    }
}