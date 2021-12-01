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
                                    _buffersize,MSG_DONTWAIT,
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

int UDP_SOCKET::Receive_Data(std::queue<BUFFER_DATA> &receive_data)
{
    int received_size = -1;
    if(_is_bind)
    {
        received_size = recvfrom(_socket_fd,
                                    _received_buffer,
                                    _buffersize,MSG_DONTWAIT,
                                    (struct sockaddr*)&_socket_address,
                                    &_socket_address_length);
        if(received_size>0)
        {
            BUFFER_DATA data;
            data.length = received_size;
            data.buffer = new uint8_t[data.length];
            memcpy(data.buffer,_received_buffer,data.length);
            receive_data.push(data);
        }
    }
    return received_size;
}

int UDP_SOCKET::Receive_Data()
{
    int received_size = -1;
    if(_is_bind)
    {
        received_size = recvfrom(_socket_fd,
                                    _received_buffer,
                                    _buffersize,MSG_DONTWAIT,
                                    (struct sockaddr*)&_socket_address,
                                    &_socket_address_length);
        if(received_size>0)
        {
            BUFFER_DATA data;
            data.length = received_size;
            data.buffer = new uint8_t[data.length];
            memcpy(data.buffer,_received_buffer,data.length);
            receive_queue.push(data);
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
        }
    }    
    return transmitted_size;
}


int UDP_SOCKET::Write_Data(std::queue<BUFFER_DATA> &write_data)
{
    int transmitted_size = -1;
    if(_is_bind)
    {
        while(!write_data.empty())
        {
            BUFFER_DATA data = write_data.front();
            if(data.length>0)
            {
                transmitted_size=sendto(_socket_fd,data.buffer,data.length,0,
                                    (struct sockaddr*)&_socket_address,sizeof(_socket_address)); 
            }
            write_data.pop();
        }
    }
    return transmitted_size;
}

int UDP_SOCKET::Write_Data()
{
    int transmitted_size = 0;
    int transmitted_size_temp = 0;
    if(_is_bind)
    {
        while(!transmit_queue.empty())
        {
            BUFFER_DATA data = transmit_queue.front();
            if(data.length>0)
            {
                transmitted_size_temp=sendto(_socket_fd,data.buffer,data.length,0,
                                    (struct sockaddr*)&_socket_address,sizeof(_socket_address)); 
                cout<<"[UDP] Tx Data : ";
                for(int i=0;i<data.length;i++)
                {
                    printf("%x ",data.buffer[i]);
                }
                printf("\r\n");
            }
            delete data.buffer;
            transmit_queue.pop();
        }
        transmitted_size = transmitted_size+transmitted_size_temp;
    }
    else
    {
        transmitted_size = -1;
        return -1;
    }
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