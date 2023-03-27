#include "ft_irc.hpp"

/*** implmentation of irc server side ****/

void server::run()
{
    int socket_listen;
    std::string port;
    struct addrinfo hints;

    std::stringstream ss;  
    ss<< _port;  
    ss>>port; 

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_adress;
    getaddrinfo(0, port.c_str(), &hints, &bind_adress);

    std::cout << "Creating a socker..." << std::endl;

    socket_listen = socket(bind_adress->ai_family, bind_adress->ai_socktype, bind_adress->ai_protocol);
    if (socket_listen < 0)
    {
        std::cout << "Creating socket failed!" << std::endl;
        return;
    }

    // bind and listening
    std::cout << "Binding socket to local address..." << std::endl;
    if (bind(socket_listen, bind_adress->ai_addr, bind_adress->ai_addrlen))
    {
        std::cout << "Binding socket is failed!" << std::endl;
        return;
    }
    freeaddrinfo(bind_adress);
    std::cout << "listening..." << std::endl;
    if (listen(socket_listen, 10) < 0)
    {
        std::cout << "listen failed!" << std::endl;
        return;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    int max_socket = socket_listen;

    //  set up our call to select():

    std::cout << "Waiting for connections...\n" << std::endl;
    while (true)
    {
        fd_set reads;
        reads = master;
        if (select(max_socket +1, &reads, 0, 0, 0) < 0){
            std::cout << "select failed!" << std::endl;
            return;
        }
        for (int i = 0; i <= max_socket; i++) {
            if (FD_ISSET(i, &reads)){
                if (i == socket_listen)
                {
                    struct sockaddr_storage client_adress;
                    socklen_t client_len = sizeof(client_adress);
                    int socket_client = accept(socket_listen, (struct sockaddr*) &client_adress, &client_len);
                    if (socket_client < 0)
                    {
                        std::cout << "accept failed!" << std::endl;
                        return;
                    }
                    FD_SET(socket_client, &master);
                    if (socket_client > max_socket)
                        max_socket = socket_client;
                    char address_buffer[100];
                    getnameinfo((struct sockaddr*)&client_adress, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
                    std::cout << "New connection from: " << address_buffer << std::endl;
                }
                else{
                    char read[512];
                    int bytes_received = recv(i, read, 512, 0);
                    if (bytes_received < 1){
                        FD_CLR(i, &master);
                        close(i);
                        continue;
                    }

                    for (int j = 0; j < bytes_received; j++)
                        read[j] = toupper(read[j]);
                    send(i, read, bytes_received, 0);
                }
            }
        } 
    }
    std::cout << "Closing listening socket..." << std::endl;
    close(socket_listen);
    std::cout << "Finished." << std::endl;
    return;
}

int main(void)
{
    server s(6667);
    s.run();
    return 0;
}