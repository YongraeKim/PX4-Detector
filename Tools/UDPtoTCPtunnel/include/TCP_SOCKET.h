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
        TCP_CONNECTION(){};
        virtual ~TCP_CONNECTION(){
            if(transmit_buffer!=nullptr)
            {
                delete transmit_buffer;
                transmit_buffer = nullptr;
            }
            if(receive_buffer!=nullptr)
            {
                delete receive_buffer;
                receive_buffer = nullptr;
            }
            if(socket_fd!=-1)
            {
                close(socket_fd);
            }
        };
        struct sockaddr_in address;
        int socket_fd=-1;
        // bool operator()(TCP_CONNECTION *connection)
        // {
        //      return (connection->address.sin_addr.s_addr == address.sin_addr.s_addr &&
        //          connection->address.sin_port == address.sin_port);
        // }
        // bool operator()(TCP_CONNECTION *connection)
        // {
        //      return (connection == this);
        // }
        void Start_Communication(void (*callback_function)(void*,void*),void* arg0)
        {
            // callback_registered = callback_function;
            // thread_id = pthread_create(&thread_handle,0,data_thread_member,this);
            // ptcp_socket = this;
            // callback_class = arg0;
            Register_Callback_Info(callback_function,arg0);
            buffer_size = 4096;
            transmit_buffer = new uint8_t[4096];
            receive_buffer = new uint8_t[4096];
        }
        void Start_Communication(void (*callback_function)(void*,void*),void* arg0,int32_t buffer_size)
        {
            // callback_registered = callback_function;
            // thread_id = pthread_create(&thread_handle,0,data_thread_member,this);
            // ptcp_socket = this;
            // callback_class = arg0;
            Register_Callback_Info(callback_function,arg0);
            this->buffer_size = buffer_size;
            transmit_buffer = new uint8_t[this->buffer_size];
            receive_buffer = new uint8_t[this->buffer_size];
        }
        void End_Communication()
        {
            exit_code = 1;
        }
        bool Transmit_UDP_Data(uint8_t* udp_data, int32_t length)
        {
            bool is_valid = false;
            pthread_mutex_lock(&mutex_transmit);
            if(length<buffer_size)
            {
                memcpy(transmit_buffer,udp_data,length);
                transmit_buffer_length = length;
                is_valid = true;
            }
            else
            {
                memcpy(transmit_buffer,udp_data,buffer_size);
                transmit_buffer_length = buffer_size;
                is_valid = false;
            }
            pthread_mutex_unlock(&mutex_transmit);
            return is_valid;
        }
        int Transmit_TCP_Data(uint8_t* tcp_to_udp, int32_t length)
        {
            int return_len = receive_buffer_length;
            if(return_len<=0)
            {
                return return_len;
            }
            pthread_mutex_lock(&mutex_receive);
            if(length>receive_buffer_length)
            {
                memcpy(tcp_to_udp,receive_buffer,receive_buffer_length);
            }
            else
            {
                memcpy(tcp_to_udp,receive_buffer,length);
            }
            receive_buffer_length = 0;
            memset(receive_buffer,0,buffer_size);
            pthread_mutex_unlock(&mutex_receive);
            return return_len;
        }
    private:
        uint8_t *transmit_buffer = nullptr;
        uint8_t *receive_buffer = nullptr;
        int32_t transmit_buffer_length = 0;
        int32_t receive_buffer_length = 0;
        int32_t buffer_size = -1;
        pthread_mutex_t mutex_transmit;
        pthread_mutex_t mutex_receive;
        pthread_mutex_t mutex_ping;
        int exit_code = -1;
        int thread_id;
        int ping_thread_id;
        pthread_t thread_handle;
        pthread_t ping_thread_handle;
        void * ptcp_socket = nullptr;
        void (*callback_registered)(void *,void *);
        void* callback_class = nullptr;
        
        void Register_Callback_Info(void (*callback_function)(void*,void*),void* arg0)
        {

            //for non-blocking tcp socket
            int flag;
            flag = fcntl(socket_fd, F_GETFL, 0 );
            fcntl(socket_fd, F_SETFL, flag | O_NONBLOCK );
            // struct timeval tv;
            // tv.tv_sec = 0;
            // tv.tv_usec = 10000;
            // setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO | SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
            callback_registered = callback_function;
            thread_id = pthread_create(&thread_handle,0,data_thread_member,this);
            ping_thread_id = pthread_create(&ping_thread_handle,0,ping_thread_member,this);
            ptcp_socket = this;
            callback_class = arg0;
            pthread_mutex_init(&mutex_ping,NULL);
            pthread_mutex_init(&mutex_receive,NULL);
            pthread_mutex_init(&mutex_transmit,NULL);
            
        }

        static void* ping_thread_member(void* arg)
        {
            TCP_CONNECTION* ptcp_connection = (TCP_CONNECTION*)arg;
            return ptcp_connection->ping_thread(arg);
        }
        void* ping_thread(void *arg)
        {
            const char ping_buffer[] = "~^PING\n"; //7e 81 50 49 4e 47 in hex
            int is_written = -1;
            while(exit_code!=1)
            {
                pthread_mutex_lock(&mutex_ping);
                is_written = write(socket_fd,ping_buffer,sizeof(ping_buffer));
                pthread_mutex_unlock(&mutex_ping);
                
                if(is_written<0)
                {
                    exit_code = 1;
                }
                sleep(1);
            }
        }

        static void* data_thread_member(void* arg)
        {
            TCP_CONNECTION* ptcp_connection = (TCP_CONNECTION*)arg;
            return  ptcp_connection->data_thread(arg);
        }
        void* data_thread(void* arg)
        {
            int is_written = -1;
            int counter = 0;
            receive_buffer_length = 0;
            while(exit_code !=1)
            {
                pthread_mutex_lock(&mutex_transmit);
                pthread_mutex_lock(&mutex_ping);
                //write received data to tcp client
                is_written = write(socket_fd,transmit_buffer,transmit_buffer_length);
                pthread_mutex_unlock(&mutex_ping);
                pthread_mutex_unlock(&mutex_transmit);    
                usleep(1000);

                pthread_mutex_lock(&mutex_receive);
                receive_buffer_length = read(socket_fd,receive_buffer,buffer_size);
                pthread_mutex_unlock(&mutex_receive);
                usleep(1000);
            }
            exit_code = 2;
            callback_registered(callback_class,(void*)this);
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
    std::vector<tcp_connection::TCP_CONNECTION*> _connection;
    int exit_code = -1;
};