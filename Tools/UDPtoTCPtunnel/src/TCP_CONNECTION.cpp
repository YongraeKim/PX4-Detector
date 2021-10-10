#include "TCP_CONNECTION.h"
#include <iostream>


namespace tcp_connection
{
        TCP_CONNECTION::TCP_CONNECTION(){};
        TCP_CONNECTION::~TCP_CONNECTION()
        {
            while(!receive_queue.empty())
            {
                delete receive_queue.front().buffer;
                receive_queue.pop();
            }
            while(!transmit_queue.empty())
            {
                delete transmit_queue.front().buffer;
                transmit_queue.pop();
            }
            
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
        void TCP_CONNECTION::Start_Communication(void (*callback_function)(void*,void*),void* arg0)
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
        void TCP_CONNECTION::Start_Communication(void (*callback_function)(void*,void*),void* arg0,int32_t buffer_size)
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
        void TCP_CONNECTION::End_Communication()
        {
            exit_code = 1;
        }
        bool TCP_CONNECTION::Transmit_UDP_Data(uint8_t* udp_data, int32_t length)
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
        int TCP_CONNECTION::Transmit_TCP_Data(uint8_t* tcp_to_udp, int32_t length)
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


        bool TCP_CONNECTION::Transmit_UDP_Data(std::queue<BUFFER_DATA> &queue_udp_data)
        {
            while(!queue_udp_data.empty())
            {
                receive_queue.push(queue_udp_data.front());
                queue_udp_data.pop();
            }
        }
        int TCP_CONNECTION::Transmit_TCP_Data(std::queue<BUFFER_DATA> &queue_tcp_data)
        {
            int data_length = 0;
            while(!transmit_queue.empty())
            {
                BUFFER_DATA data = transmit_queue.front();
                queue_tcp_data.push(data);
                data_length = data_length+data.length;
                std::cout <<"[TCP] Rx Data : ";
                for(int i=0;i<data.length;i++)
                {
                    printf("%x ",data.buffer[i]);
                }
                printf("\r\n");
                transmit_queue.pop();
            }
            return data_length;
        }
        
        void TCP_CONNECTION::Register_Callback_Info(void (*callback_function)(void*,void*),void* arg0)
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

        void* TCP_CONNECTION::ping_thread_member(void* arg)
        {
            TCP_CONNECTION* ptcp_connection = (TCP_CONNECTION*)arg;
            return ptcp_connection->ping_thread(arg);
        }
        void* TCP_CONNECTION::ping_thread(void *arg)
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
                usleep(100000);
            }
        }

        void* TCP_CONNECTION::data_thread_member(void* arg)
        {
            TCP_CONNECTION* ptcp_connection = (TCP_CONNECTION*)arg;
            return  ptcp_connection->data_thread(arg);
        }
        void* TCP_CONNECTION::data_thread(void* arg)
        {
            int is_written = -1;
            int counter = 0;
            receive_buffer_length = 0;
            while(exit_code !=1)
            {
                pthread_mutex_lock(&mutex_transmit);
                pthread_mutex_lock(&mutex_ping);
                //write received data to tcp client
                //is_written = write(socket_fd,transmit_buffer,transmit_buffer_length);
                while(!this->receive_queue.empty())
                {
                    BUFFER_DATA data = receive_queue.front();
                    is_written = write(socket_fd,data.buffer,data.length);
                    delete data.buffer;
                    receive_queue.pop();
                }
                pthread_mutex_unlock(&mutex_ping);
                pthread_mutex_unlock(&mutex_transmit);    
                usleep(1000);

                pthread_mutex_lock(&mutex_receive);
                receive_buffer_length = read(socket_fd,receive_buffer,buffer_size);
                if(receive_buffer_length>0)
                {
                    BUFFER_DATA enqueue_data;
                    enqueue_data.length = receive_buffer_length;
                    enqueue_data.buffer = new uint8_t[enqueue_data.length];
                    memcpy(enqueue_data.buffer,receive_buffer,enqueue_data.length);
                    transmit_queue.push(enqueue_data);

                }
                pthread_mutex_unlock(&mutex_receive);
                usleep(1000);
            }
            exit_code = 2;
            callback_registered(callback_class,(void*)this);
            pthread_exit(&exit_code);
        }
}
