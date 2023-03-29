#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <poll.h>
# include <sys/select.h>
# include <string.h>
# include <string>
# include<sstream>  

class server
{
    private:
        int _port;
    public:
        server(/* args */);
        server(int port);
        void run();
        struct addrinfo *get_address();
        ~server();
};

bool    is_digit(char *str);
bool is_valid_pass(int ac, char **av);

# endif