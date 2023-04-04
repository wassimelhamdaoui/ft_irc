#include "server.hpp"

void    server::parse_request(char *read, int fd)
{
    Client client(fd);
    std::string request(read);
    std::string response;

    if(this->_map.count(fd) <= 0)
        this->_map.insert(std::make_pair(fd, client));
    response = pass_response(request, this->_map[fd]);
    // if(response == "")
    //     response = nick_response(request, this->_map[fd]);
    // if(this->_map.count(fd) <= 0)
    //     this->_map.insert(std::make_pair(fd, client));
    response = pass_response(request, client);
    send(fd, response.c_str(), response.size(), 0);
}

int main(int ac, char **av)
{
    try
    {
        if (!is_valid_arg(ac, av))
            return 1;
        std::string str(av[2]);
        server ser(atoi(av[1]), str);
        ser.set_pass(str);
        ser.set_port(atoi(av[1]));
        ser.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}