#include "server.hpp"

// void check_pass(char **tokens, int fd)
// {
//     std::string msg;
//     server obj;
//     int i = 0;
//     while (tokens[i])
//         i++;
//     if (i != 2 || tokens[1] == NULL){
//         msg = "invalid password arguments: try PASS <server password>\n";
//         send(fd, msg.c_str(), msg.size(), 0);
//         return;
//     }
//     std::string pass(tokens[1]);
//     if (pass == obj.get_pass())
//     {
//         obj.set_authentication(true);
//         msg = "Successful authentication...\n";
//         send(fd, msg.c_str(), msg.size(), 0);
//     }
//     else
//     {
//         msg = "Invalid Password!\n";
//         send(fd, msg.c_str(), msg.size(), 0);
//     }
    
// }

void    server::parse_request(char *read, int fd)
{
    Client client(fd);
    std::string request(read);
    std::string response;

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