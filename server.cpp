#include "server.hpp"

int request_handler(int i, fd_set *master)
{
    char read[4608];
    int bytes_received = recv(i, read, 4608, 0);
    if (bytes_received < 1){
        FD_CLR(i, master);
        close(i);
        return (-1);
    }

    char *response = parse_request(read);
    if (send(i, response, bytes_received, 0) < 0 || response == NULL)
    {
        delete[] response;
        return (-1);
    }
    delete[] response;
    return (1);
}

struct addrinfo *server::get_address()
{
    std::string port;
    struct addrinfo hints;
    std::stringstream ss;
    struct addrinfo *bind_adress;

    ss<< _port;
    ss >> port;
    std::cout << "configuring local adress..." << std::endl;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(0, port.c_str(), &hints, &bind_adress);
    return (bind_adress);
}

int create_socket(struct addrinfo *bind_adress)
{
    int socket_listen;
    std::cout << "Creating a socker..." << std::endl;
    socket_listen = socket(bind_adress->ai_family, bind_adress->ai_socktype, bind_adress->ai_protocol);
    if (socket_listen < 0)
    {
        std::cout << "Creating socket failed!" << std::endl;
        return -1;
    }
    return (socket_listen);
}

bool    bind_and_listen(int socket_listen, struct addrinfo *bind_adress)
{
    std::cout << "Binding socket to local address..." << std::endl;
    if (bind(socket_listen, bind_adress->ai_addr, bind_adress->ai_addrlen))
    {
        freeaddrinfo(bind_adress);
        std::cout << "Binding socket is failed!" << std::endl;
        return false;
    }
    freeaddrinfo(bind_adress);
    std::cout << "listening..." << std::endl;
    if (listen(socket_listen, SOMAXCONN) < 0)
    {
        std::cout << "listen failed!" << std::endl;
        return false;
    }
    return (true);
}

int accept_connection(int socket_listen, fd_set *master, int *max_socket)
{
    struct sockaddr_storage client_adress;
    socklen_t client_len = sizeof(client_adress);
    int socket_client = accept(socket_listen, (struct sockaddr*) &client_adress, &client_len);
    if (socket_client < 0)
    {
        std::cout << "accept failed!" << std::endl;
        return -1;
    }
    FD_SET(socket_client, master);
    if (socket_client > *max_socket)
        *max_socket = socket_client;
    char address_buffer[100];
    getnameinfo((struct sockaddr*)&client_adress, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    std::cout << "New connection from: " << address_buffer << std::endl;
    return(socket_client);
}


void server::run()
{
    int socket_listen;
    struct addrinfo *bind_adress = this->get_address();
    
    if ((socket_listen = create_socket(bind_adress)) < 0)
        return;
    if (!bind_and_listen(socket_listen, bind_adress))
        return;
    fcntl(socket_listen, F_SETFL, O_NONBLOCK);
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
                if (i == socket_listen) {
                    int socket_client = accept_connection(socket_listen, &master, &max_socket);
                    if ( socket_client< 0)
                        return;
                    fcntl(socket_client, F_SETFL, O_NONBLOCK);  
                }
                else{
                    if (request_handler(i, &master) < 0)
                        continue;
                }
            }
        } 
    }
    close(socket_listen);
    return;
}


/***** Class Methodes ****/

const std::string server::pass = "123";
server::server(/* args */)
: _port(0)
{
}

server::server(int port)
: _port(port)
{
}

std::string server::get_pass()
{
    return (pass);
}

// void server::run()
// {
//     std::cout << "server running on port " << _port << std::endl;
// }

server::~server()
{
}