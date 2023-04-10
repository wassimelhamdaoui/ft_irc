# include "headers.hpp"

void server::quit_response(std::vector<std::string> split, Client &client, fd_set *master)
{
    std::string response;
    std::string message;

    if (split.size() == 1)
        message = "Client Quit";
    else
        message = split[1];
    response = "<" + client.get_nick() + "> "  + " close connection\r\n";
    send(client.get_fd(), response.c_str(), response.size(), 0);
    close(client.get_fd());
    FD_CLR(client.get_fd(), master);
    // this->_map.erase(client.get_fd());
    // this->_channels.erase(client.get_nick());
}