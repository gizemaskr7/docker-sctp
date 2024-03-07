#include <iostream>
#include <chrono>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // IPv4 ve IPv6 adreslerini metinden ikili forma dönüştürme
    if(inet_pton(AF_INET, "172.17.0.2", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int loop_count = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        valread = read(sock, buffer, MAX_BUFFER_SIZE);
        std::cout << "Client " << loop_count * 3 << " saniyedir ayakta. Server: " << buffer << std::endl;
        loop_count++;
    }
    return 0;
}
