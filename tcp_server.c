#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main(){

    // Creation of our server socket
    int serverSocket = 0;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Server Address Structure
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1234); // PORT
    inet_pton(AF_INET, "0.0.0.0", &(serverAddress.sin_addr));

    // Bind the socket to our specified IP and Port.
    int bindSocket = 0;
    bindSocket = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bindSocket == -1){
        printf("An error has occurred when trying to bind the socket.\n");
        return 0;
    }

    // Start listening for connections:
    int listenConn = 0;
    listenConn = listen(serverSocket, 1); // Number of connections in queue
    if (listenConn == -1){
        printf("An error has occurred when trying to listen for connections.\n");
    }

    // After the connection is made, we store the client socket
    int clientSocket = 0;
    struct sockaddr clientData = {0};
    int clientAddressLength = sizeof(clientData);
    clientSocket = accept(serverSocket, &clientData, &clientAddressLength);

    // Sending data
    char serverMessage[256] = {0};
    send(clientSocket, serverMessage, sizeof(serverMessage), 0);

    // Strings
    char command[256] = {0};
    char clientResponse[256] = {0};

    // Loop for sending commands remotely
    while (true){
        
        // Printing Interface for sending commands
        printf("MiniC2: ");
        fgets(command, sizeof(command), stdin);
                        
        // IF exit, close the application
        if (strncmp(command,"exit",4) == 0){
            strncpy(serverMessage, "exit", sizeof(serverMessage)); 
            
            // Close the socket
            close(serverSocket);
            close(clientSocket);
            send(clientSocket, serverMessage,sizeof(serverMessage),0);
            
            return 0;
        } else {
            strncpy(serverMessage, command, sizeof(serverMessage));
            send(clientSocket, serverMessage, sizeof(serverMessage), 0);
        }
    
        // Receiving and printing from client
        recv(clientSocket, &clientResponse, sizeof(clientResponse), 0);
        printf("%s",clientResponse);
        printf("\n");
    }

}


