#include "server.hpp"

bool    is_digit(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return (false);
        i++;
    }
    return (true);
}

bool is_valid_pass(int ac, char **av)
{
    std::string str;
    int port = atoi(av[1]);
    if (ac != 3 || av[1][0] == '\0' || av[2][0] == '\0')
    {
        std::cout << "number of argument invalid: try <port> <password>" << std::endl;
        return false;
    }
    if (port < 1024 || port > 65533 || !is_digit(av[1]))
    {
        std::cout << "invalid port!" << std::endl;
        return (false);
    }
    str = av[2];
    if (str != "123")
    {
        std::cout << "password invalid" << std::endl;
        return (false);
    }
    return (true);
}