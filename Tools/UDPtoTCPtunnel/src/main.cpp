#include <iostream>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define UDP_PORT 14550
#define BUFFER_SIZE 4096
#define SOCKFD_EMPTY -1
int main()
{
    cout<<"UDP to TCP tunneling"<<endl;
    int udp2tcp_tunnel_sock_ = SOCKFD_EMPTY;
    int px4_server_sock_ = SOCKFD_EMPTY;
    unsigned char receive_buffer[BUFFER_SIZE];
    int receive_length = -1;
    struct sockaddr_in px4_server_addr_, udp2tcp_tunnel_addr_;
    
    socklen_t px4_server_addr_size_ = sizeof(px4_server_addr_);
    socklen_t udp2tcp_tunnel_addr_size_ = sizeof(udp2tcp_tunnel_addr_);

    bool exit_code = false;
    if((udp2tcp_tunnel_sock_ = socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        cout << "[UDP2TCP] failed open socket"<<endl;
    }
    else
    {
        cout << "[UDP2TCP] UDP Socket opend" <<endl;
        memset(&px4_server_addr_,0,sizeof(px4_server_addr_));
        px4_server_addr_.sin_family = AF_INET;
        inet_aton("127.0.0.1", (struct in_addr*) &px4_server_addr_.sin_addr.s_addr);
        px4_server_addr_.sin_port = htons(UDP_PORT);
        if(bind(udp2tcp_tunnel_sock_,(struct sockaddr *)&px4_server_addr_,sizeof(px4_server_addr_)) < 0)
        {
            cout <<"cannot bind local server"<<endl;
        }
        else
        {
            cout <<" bind success"<<endl;
            while(exit_code == false)
            {
                if((receive_length = recvfrom(udp2tcp_tunnel_sock_, receive_buffer, BUFFER_SIZE, 0, (struct sockaddr *)&udp2tcp_tunnel_addr_, &udp2tcp_tunnel_addr_size_)) >= 0)
                {
                    for(int i=0;i<receive_length;i++)
                    {
                        printf("%x ",receive_buffer[i]);
                    }
                    printf("\r\n");
                }
                else
                {
                    cout << "connection failed"<<endl;
                    exit_code = true;
                }
            }
        }
    }
    if(udp2tcp_tunnel_sock_!=SOCKFD_EMPTY)
    {
        close(udp2tcp_tunnel_sock_);
    }

}