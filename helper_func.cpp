#include "headers.hpp"

bool is_valid_arg(int ac, char **av)
{
    if (ac != 3 || av[1][0] == '\0' || av[2][0] == '\0')
    {
        std::cout << "number of argument invalid: try <port> <password>" << std::endl;
        return false;
    }
    return (true);
}

bool has_comma(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == ',')
            return true;
    }
    return false;
}