#include <iostream>
#include <chrono>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER_SIZE] = {0};

    // Soket dosyası tanımlama
    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Soketi port ile eşleştirme
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Soketi porta bağlama
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    int loop_count = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::string message = "Server " + std::to_string(loop_count * 3) + " saniyedir ayakta.";
        send(new_socket, message.c_str(), message.length(), 0);
        std::cout << "Server " << loop_count * 3 << " saniyedir ayakta." << std::endl;
        loop_count++;
    }
    return 0;
}
