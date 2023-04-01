#include "server.hpp"

void    parse_request(char *read, int fd)
{
    std::string request;
    request = read;
    int i = 0;
    while (read[i])
    {
        request[i] = toupper(read[i]);
        i++;
    }
    request += "\n";
    send(fd, request.c_str(), request.size(), 0);
        //return (-1);
}

int main(int ac, char **av)
{
    try
    {
        if (!is_valid_arg(ac, av))
            return 1;
        std::string str(av[2]);
        server s(atoi(av[1]), str);
        s.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}