#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h> // gives access to networking functions
#include <arpa/inet.h>  // assists in translating IP addresses

int main(int argc, char *argv[]){
    
    // Checks if user inputs IP and PORT
    if (argc != 3){ // Ensures the user types <IP> <PORT>
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        return 1;
    }

    char *ip_address = argv[1]; 
    int port = atoi(argv[2]); // Converts string to integer

    // Socket File Descriptor
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //AF_INET specifies IPV4
    //SOCK_STREAM specifies TCP
    //0 specifies protocol
    
    if (sock < 0){
        perror("Socket creation Failed");
        return 1;
    }

    //Target Address Structure
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address, &server_addr.sin_addr);

    //Attempt to Connect
    int result = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (result == 0) {
        printf("[+] Port %d is OPEN\n", port);
    } else {
        printf("[-] Port %d is CLOSED\n", port);
    }

    close(sock);
    return 0;
}