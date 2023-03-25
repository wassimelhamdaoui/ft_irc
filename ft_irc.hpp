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
#include <poll.h>
 #include <sys/select.h>

class ft_irc
{
private:
    /* data */
public:
    ft_irc(/* args */);
    ~ft_irc();
};


# endif