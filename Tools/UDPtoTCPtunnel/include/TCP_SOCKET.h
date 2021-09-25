#pragma once
#include <vector>
#include "ISOCKET_INT.h"


enum class TCP_SOCKET_TYPE
{
    TCP_SOCKET_SERVER,
    TCP_SOCKET_CLIENT
};

namespace tcp_connection
{
    class TCP_CONNECTION
    {
    public:
        struct sockaddr_in address;
        int socket_fd;
        bool operator()(TCP_CONNECTION connection)
        {
            return (connection.address.sin_addr.s_addr == address.sin_addr.s_addr &&
                connection.address.sin_port == address.sin_port);
        }
        void Start_Communication(void (*callback_function)(void*,void*),void* arg)
        {
            callback_registered = callback_function;
            thread_id = pthread_create(&thread_handle,0,data_thread_member,this);
            ptcp_socket = arg;
        }
        void End_Communication()
        {
            exit_code = 1;
            void *return_val = 0;
            while(*((int*)return_val) !=2) //wait for thread exit
            {
                pthread_join(thread_handle,&return_val);
            }
            callback_registered(ptcp_socket,this);
            
        }
    private:
        int exit_code = -1;
        int thread_id;
        pthread_t thread_handle;
        void * ptcp_socket = nullptr;
        void (*callback_registered)(void *,void *);
        void* callback_class;
        static void* data_thread_member(void* arg)
        {
            TCP_CONNECTION* ptcp_connection = (TCP_CONNECTION*)arg;
            return  ptcp_connection->data_thread(arg);
        }
        void* data_thread(void* arg)
        {
            while(exit_code !=1)
            {

            }
            exit_code = 2;
            pthread_exit(&exit_code);
        }
    };
}


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
    virtual int Write_Data(uint8_t* buffer, int32_t write_size) override;
    virtual void Close_Socket() override;
    virtual void* Connection_Thread(void *arg) override;
    static void* Connection_Thread_Member(void* arg);
    static void Connection_Callback_Member(void* class_prt, void* connection_ptr);
    void Connection_Callback(void* arg);
    
    
private:
    int _max_connection_number;
    std::vector<tcp_connection::TCP_CONNECTION> _connection;
    int exit_code = -1;
};