#include "server.hpp"

std::string parse_request(char *read)
{
    std::string request;
    request = read;
    int i = 0;
    while (read[i])
    {
        request[i] = toupper(read[i]);
        i++;
    }
    return(request);
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