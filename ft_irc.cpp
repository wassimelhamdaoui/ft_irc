#include "ft_irc.hpp"

server::server(/* args */)
: _port(0)
{
}

server::server(int port)
: _port(port)
{
}

// void server::run()
// {
//     std::cout << "server running on port " << _port << std::endl;
// }

server::~server()
{
}