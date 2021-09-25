#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <cstdio>
#include <sys/stat.h>
#include <cstdlib>
#include <unistd.h>
#include "UDP_SOCKET.h"
#include "TCP_SOCKET.h"
// #include <string.h>
// #include <unistd.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>

using namespace std;

#define UDP_PORT 14550
#define BUFFER_SIZE 4096
#define SOCKFD_EMPTY -1

UDP_SOCKET* udp_exit = nullptr;
TCP_SOCKET* tcp_exit = nullptr;

void (*breakCapture)(int);
int exit_code = -1;
void signalingHandler(int signo) 
{
    cout << "Exit code captured"<<endl;
    cout <<"[UDP2TCP INFO] Exit program"<<endl;
    exit_code = 1;
}

int main()
{
    breakCapture = signal(SIGINT, signalingHandler);
    cout <<"UDP to TCP tunneling"<<endl;
    UDP_SOCKET *udp = new UDP_SOCKET("127.0.0.1",UDP_PORT,BUFFER_SIZE,UDP_SOCKET_TYPE::UDP_CLIENT);
    TCP_SOCKET *tcp = new TCP_SOCKET("NULL",1234,BUFFER_SIZE,TCP_SOCKET_TYPE::TCP_SOCKET_SERVER,1);
    udp_exit = udp;
    tcp_exit = tcp;
    udp->Create_Socket();
    udp->Bind();
    tcp->Create_Socket();
    tcp->Bind();
    tcp->Listen();
    uint8_t received_buffer[BUFFER_SIZE]={0,};
    while(exit_code != 1)
    {
        if(tcp->Accept()==true)
        {
            cout << "client connected"<<endl;
        }
        else
        {
            cout <<"accept failed"<<endl;
        }
        // int received = udp->Receive_Data(received_buffer,BUFFER_SIZE);
        // if(received!=-1)
        // {
        //     for(int i=0;i<received;i++)
        //     {
        //         printf("%x ",received_buffer[i]);
        //     }
        //     printf("\r\n");
        // }
        // else
        // {
        //     cout << "nothing recv"<<endl;
        // }
    }
    udp->Close_Socket();
    delete udp;
    delete tcp;
    cout <<"end UDP to TCP tunneling"<<endl;
}


// int main()
// {
//     cout<<"UDP to TCP tunneling"<<endl;
//     int udp2tcp_tunnel_sock_ = SOCKFD_EMPTY;
//     int px4_server_sock_ = SOCKFD_EMPTY;
//     unsigned char receive_buffer[BUFFER_SIZE];
//     int receive_length = -1;
//     struct sockaddr_in px4_server_addr_, udp2tcp_tunnel_addr_;
    
//     socklen_t px4_server_addr_size_ = sizeof(px4_server_addr_);
//     socklen_t udp2tcp_tunnel_addr_size_ = sizeof(udp2tcp_tunnel_addr_);

//     bool exit_code = false;
//     if((udp2tcp_tunnel_sock_ = socket(AF_INET,SOCK_DGRAM,0))<0)
//     {
//         cout << "[UDP2TCP] failed open socket"<<endl;
//     }
//     else
//     {
//         cout << "[UDP2TCP] UDP Socket opend" <<endl;
//         memset(&px4_server_addr_,0,sizeof(px4_server_addr_));
//         px4_server_addr_.sin_family = AF_INET;
//         inet_aton("127.0.0.1", (struct in_addr*) &px4_server_addr_.sin_addr.s_addr);
//         px4_server_addr_.sin_port = htons(UDP_PORT);
//         cout << "bind test without server"<<endl;
//         if(bind(udp2tcp_tunnel_sock_,(struct sockaddr *)&px4_server_addr_,sizeof(px4_server_addr_)) < 0)
//         {
//             cout <<"cannot bind local server"<<endl;
//         }
//         else
//         {
//             cout <<" bind success"<<endl;
//             while(exit_code == false)
//             {
//                 if((receive_length = recvfrom(udp2tcp_tunnel_sock_, receive_buffer, BUFFER_SIZE, 0, (struct sockaddr *)&px4_server_addr_, &px4_server_addr_size_)) >= 0)
//                 {
//                     for(int i=0;i<receive_length;i++)
//                     {
//                         printf("%x ",receive_buffer[i]);
//                     }
//                     printf("\r\n");
//                 }
//                 else
//                 {
//                     cout << "connection failed"<<endl;
//                     exit_code = true;
//                 }
//             }
//         }
//     }
//     if(udp2tcp_tunnel_sock_!=SOCKFD_EMPTY)
//     {
//         close(udp2tcp_tunnel_sock_);
//     }

// }