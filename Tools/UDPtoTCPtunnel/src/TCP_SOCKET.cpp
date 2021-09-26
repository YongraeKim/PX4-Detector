#include "TCP_SOCKET.h"
#include <iostream>
#include <algorithm>

using namespace std;

TCP_SOCKET::TCP_SOCKET(const char *ipv4_address, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE socket_type)
{
    Initialize(ipv4_address,port,buffersize,socket_type);
}

TCP_SOCKET::TCP_SOCKET(const char *ipv4_address, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE socket_type, int max_connection_number)
{
    Initialize(ipv4_address,port,buffersize,socket_type);
    _max_connection_number = max_connection_number;
    _connection.clear();
    _connection.empty();
}

TCP_SOCKET::~TCP_SOCKET()
{
    Close_Socket();
    exit_code = 1;
}


void TCP_SOCKET::Initialize(const char *ipv4_address, int32_t port, int32_t buffersize, TCP_SOCKET_TYPE socket_type)
{
    memset(&_socket_address,0,sizeof(_socket_address));
    if(socket_type == TCP_SOCKET_TYPE::TCP_SOCKET_CLIENT)
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

int TCP_SOCKET::Create_Socket()
{
    _socket_fd = socket(PF_INET,SOCK_STREAM,0);
    _last_error_code = _socket_fd;
    return _last_error_code;
}

bool TCP_SOCKET::Bind()
{
    _last_error_code = bind(_socket_fd,(struct sockaddr*)&_socket_address,sizeof(_socket_address));
    if(_last_error_code>-1)
    {
        cout <<"[TCP_INFO] Bind succeeded" <<endl;
        _is_bind = true;
    }
    else
    {
        cout <<"[TCP_ERROR] Bind failed" <<endl;
        _is_bind = false;
    }
    return _is_bind;
}


bool TCP_SOCKET::Listen()
{
    _last_error_code = listen(_socket_fd,1);
    if(_last_error_code<0)
    {
        cout << "[TCP_ERROR] linten failed"<<endl;
        _is_listen = false;
    }
    else
    {
        cout <<"[TCP_INFO] Listen socket opened"<<endl;
        connection_thread_id = pthread_create(&connection_thread_handle,0,Connection_Thread_Member,this);
        _is_listen = true;
    }
    return _is_listen;
}

void* TCP_SOCKET::Connection_Thread_Member(void* arg)
{
    TCP_SOCKET *ptcp_socket = (TCP_SOCKET*)arg;
    return (void*)ptcp_socket->Connection_Thread(arg);
}

void* TCP_SOCKET::Connection_Thread(void *arg)
{
    cout << "[TCP_INFO] Start linten"<<endl;

    while(exit_code!=1)
    {
        if(Accept()==true)
        {
            cout << "client connected"<<endl;
        }
        else
        {
            cout <<"accept failed"<<endl;
        }
    }
    exit_code = 2;
    cout << "[TCP_INFO] lintening thread terminated"<<endl;
}

void TCP_SOCKET::Connection_Callback_Member(void* class_ptr, void* connection_ptr)
{
    TCP_SOCKET* ptcp_socket = (TCP_SOCKET*)class_ptr;
    return ptcp_socket->Connection_Callback(connection_ptr);
}

void TCP_SOCKET::Connection_Callback(void* pconnection_arg)
{
    tcp_connection::TCP_CONNECTION *connection_registered = (tcp_connection::TCP_CONNECTION *)pconnection_arg;
    connection_registered->End_Communication();
    vector<tcp_connection::TCP_CONNECTION*>::iterator iter = find_if(_connection.begin(),_connection.end(),[&](tcp_connection::TCP_CONNECTION* ptr_elem){return ptr_elem==connection_registered;});
    if(iter!=_connection.end())
    {
        _connection.erase(iter);
    }
    cout <<"[TCP_INFO] Delete TCP connection"<<endl;
    delete connection_registered;
}
void TCP_SOCKET::Close_Socket()
{
    if(_socket_fd !=-1)
    {
        close(_socket_fd);
        _socket_fd = -1;
    }
    if(_received_buffer !=nullptr)
    {
        delete _received_buffer;
        _received_buffer = nullptr;
        _buffersize = -1;
    }
}


bool TCP_SOCKET::Accept()
{
    cout <<"[TCP_INFO] Wait for accept clinets..."<<endl;
    _socket_cs = accept(_socket_fd,(struct sockaddr*)&_socket_cs_address,&_socket_address_cs_length);
    cout <<"[TCP_INFO] Detect accessing to server..."<<endl;
    tcp_connection::TCP_CONNECTION *connection_candidate = new tcp_connection::TCP_CONNECTION;
    connection_candidate->address = _socket_cs_address;
    connection_candidate->socket_fd = _socket_cs;
    char connection_string[INET_ADDRSTRLEN];
    inet_ntop(AF_INET,&connection_candidate->address.sin_addr,connection_string,INET_ADDRSTRLEN);
    cout<<"[TCP_INFO] Connection request from "<<connection_string<<endl;
    _last_error_code = _socket_cs;
    if(_last_error_code <0)
    {
        _is_accept = false;
        cout <<"[TCP_ERROR] TCP socket acceptance failed to "<<connection_string<<endl;
    }
    else
    {
        _is_accept = true;
    }
    if(_connection.size()<_max_connection_number && _is_accept == true)
    {
        vector<tcp_connection::TCP_CONNECTION*>::iterator iter = find_if(_connection.begin(),_connection.end(),[&](tcp_connection::TCP_CONNECTION* ptr_elem){return ptr_elem==connection_candidate;});
        
        if(iter != _connection.end())
        {
            close(connection_candidate->socket_fd);
            delete connection_candidate;
            cout <<"[TCP_ERROR] Socket already opened"<<endl;
            _is_accept = false;
        }
        else
        {
            connection_candidate->Start_Communication(Connection_Callback_Member,this);
            _connection.push_back(connection_candidate);
            _is_accept = true;
            cout <<"[TCP_INFO] Connection established to "<<connection_string<<endl;
        }
    }
    else
    {
        close(connection_candidate->socket_fd);
        delete connection_candidate;
        cout <<"[TCP_ERROR] Maximum number of connection reached"<<endl;
        _is_accept = false;
    }
    return _is_accept;
}

int TCP_SOCKET::Receive_Data(uint8_t* buffer, int32_t read_size)
{
    return -1;
}

int TCP_SOCKET::Write_Data(uint8_t* buffer, int32_t write_size)
{
    return -1;
}