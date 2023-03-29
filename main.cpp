#include "server.hpp"

char *parse_request(char *read)
{
    int len = strlen(read);
    char *request = new char[len];
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
    if (!is_valid_pass(ac, av))
        return 1;
    server s(atoi(av[1]));
    s.run();
    return 0;
}