#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <cstdio>
#include <sys/stat.h>
#include <cstdlib>
#include <unistd.h>
#include "UDP_SOCKET.h"
#include "TCP_SOCKET.h"

using namespace std;

#define BUFFER_SIZE 16384
#define SOCKFD_EMPTY -1

//UDP_SOCKET* udp_exit = nullptr;
//TCP_SOCKET* tcp_exit = nullptr;
//TCP_SOCKET* tcpqgc_exit = nullptr;

void (*breakCapture)(int);
int exit_code = -1;
void signalingHandler(int signo) 
{
    cout << "Exit code captured"<<endl;
    cout <<"[UDP2TCP INFO] Exit program"<<endl;
    exit_code = 1;
    std::terminate();
}

int main(int argc, char* argv[])
{
    breakCapture = signal(SIGINT, signalingHandler);
    signal(SIGPIPE, SIG_IGN);
    cout <<"UDP to TCP tunneling"<<endl;

    int udp_port = 14550;
    int baseport = 1726;
    int number_of_socket = 1;

    //if argc >1, udp2tcp [number of vehicles] [baseport]
    //example : ./udp2tcp 2 1234 ->two of vehicles, 1234 baseport on TCP socket
    if(argc>1)
    {
        switch(argc)
        {
            case 2:
                number_of_socket = atoi(argv[1]);
            break;
            case 3:
                number_of_socket = atoi(argv[1]);
                baseport = atoi(argv[1]);
            break;
        }
    }
    vector<UDP_SOCKET*> udp;
    vector<TCP_SOCKET*> tcp;
    for(int i=0;i<number_of_socket;i++)
    {
        UDP_SOCKET* pudp = new UDP_SOCKET("127.0.0.1",udp_port+i,BUFFER_SIZE,UDP_SOCKET_TYPE::UDP_CLIENT);
        TCP_SOCKET* ptcp = new TCP_SOCKET("NULL",baseport+i,BUFFER_SIZE,TCP_SOCKET_TYPE::TCP_SOCKET_SERVER,1);
        pudp->Create_Socket();
        pudp->Bind();
        ptcp->Create_Socket();
        if(ptcp->Bind()==false)
        {
            cout <<"[TCP_ERROR] Stop executing tunneling"<<endl;
            return 0;
        }
        ptcp->Listen();
        cout <<"[UDP2TCP INFO] start tunneling on TCP port "<<baseport+i<<" UDP port " << udp_port+i<<endl;
        udp.push_back(pudp);
        tcp.push_back(ptcp);
    }
    cout <<"[UDP2TCP INFO] start tunneling"<<endl;
    //UDP_SOCKET *udp = new UDP_SOCKET("127.0.0.1",UDP_PORT,BUFFER_SIZE,UDP_SOCKET_TYPE::UDP_CLIENT);
    //TCP_SOCKET *tcp = new TCP_SOCKET("NULL",baseport,BUFFER_SIZE,TCP_SOCKET_TYPE::TCP_SOCKET_SERVER,1);
    //TCP_SOCKET *tcpqgc = new TCP_SOCKET("NULL",1464,BUFFER_SIZE,TCP_SOCKET_TYPE::TCP_SOCKET_SERVER,1);
    
    //udp_exit = udp;
    //tcp_exit = tcp;
    //tcpqgc_exit = tcpqgc;
    //udp->Create_Socket();
    //udp->Bind();
    //tcp->Create_Socket();
    //if(tcp->Bind()==false)
    //{
    //    cout <<"[TCP_ERROR] Stop executing tunneling"<<endl;
    //    return 0;
    //}
    //tcp->Listen();
    //cout <<"[UDP2TCP INFO] start tunneling"<<endl;

    // uint8_t data_from_udp[BUFFER_SIZE] = {0,};
    int32_t data_from_udp_length = -1;
// uint8_t data_from_tcp[BUFFER_SIZE] = {0,};
    int32_t data_from_tcp_length = -1;
    vector<UDP_SOCKET*>::iterator udp_iter;
    vector<TCP_SOCKET*>::iterator tcp_iter;
    
    while(exit_code != 1)
    {
        //number of udp and tcp must be matched. 1:1 tunneling
        tcp_iter = tcp.begin();
        int count = 0;
        for(udp_iter = udp.begin(); udp_iter!=udp.end(); ++udp_iter)
        {
            UDP_SOCKET* udppt = (UDP_SOCKET*)*udp_iter;
            TCP_SOCKET* tcppt = (TCP_SOCKET*)*tcp_iter;
            data_from_udp_length = udppt->Receive_Data();
            if(data_from_udp_length>0)
            {
                tcppt->Receive_Data(udppt->receive_queue);
            }
            data_from_tcp_length = tcppt->Write_Data(udppt->transmit_queue);
            if(data_from_tcp_length>0)
            {
                udppt->Write_Data();
            }
            tcp_iter++;
            usleep(250);
        }
        usleep(250);
        // usleep(1000);
        // for(tcp_iter = tcp.begin();tcp_iter!=tcp.end();tcp_iter++)
        // {
        //     data_from_tcp_length
        // }
        
        // data_from_udp_length=udp->Receive_Data();
        // usleep(1000);
        // if(data_from_udp_length>0)
        // {
        //     tcp->Receive_Data(udp->receive_queue);
        // }
        // usleep(1000);
        // data_from_tcp_length = tcp->Write_Data(udp->transmit_queue);
        // usleep(1000);
        // if(data_from_tcp_length>0)
        // {
        //     udp->Write_Data();
        // }
    }
    for(udp_iter = udp.begin();udp_iter!=udp.end();udp_iter++)
    {
        UDP_SOCKET* udppt = (UDP_SOCKET*)*udp_iter;
        udppt->Close_Socket();
        delete udppt;
        udppt = nullptr;
    }
    for(tcp_iter = tcp.begin();tcp_iter!=tcp.end();tcp_iter++)
    {
        TCP_SOCKET* tcppt = (TCP_SOCKET*)*tcp_iter;
        tcppt->Close_Socket();
        delete tcppt;
        tcppt = nullptr;
    }
    // delete udp;
    // delete tcp;
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