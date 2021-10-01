#pragma once
#include "ISOCKET_INT.h"

namespace tcp_connection
{
    class TCP_CONNECTION
    {
    public:
        TCP_CONNECTION();
        virtual ~TCP_CONNECTION();
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
        void Start_Communication(void (*callback_function)(void*,void*),void* arg0);
        void Start_Communication(void (*callback_function)(void*,void*),void* arg0,int32_t buffer_size);
        void End_Communication();
        bool Transmit_UDP_Data(uint8_t* udp_data, int32_t length);
        int Transmit_TCP_Data(uint8_t* tcp_to_udp, int32_t length);
        bool Transmit_UDP_Data(std::queue<BUFFER_DATA> &queue_udp_data);
        int Transmit_TCP_Data(std::queue<BUFFER_DATA> &queue_tcp_data);

    private:
        uint8_t *transmit_buffer = nullptr;
        uint8_t *receive_buffer = nullptr;
        int32_t transmit_buffer_length = 0;
        int32_t receive_buffer_length = 0;
        int32_t buffer_size = -1;
        std::queue<BUFFER_DATA> transmit_queue;
        std::queue<BUFFER_DATA> receive_queue;
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
        void Register_Callback_Info(void (*callback_function)(void*,void*),void* arg0);

        static void* ping_thread_member(void* arg);
        void* ping_thread(void *arg);

        static void* data_thread_member(void* arg);
        void* data_thread(void* arg);
    };
}
