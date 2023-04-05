#include "server.hpp"

void    create_channel(std::string name, std::string pass, Channel &channel,Client client)
{
    channel.set_name(name);
    channel.set_pass(pass);
    channel.add_member(client);
    channel.set_topic("No topic is set");
    channel.set_aut_key(true);
    channel.get_cannels()[name] = 1;
}

std::string join_response(std::string request, Client client, Channel &channel)
{
    std::vector<std::string> tokens;
    std::string response;

    tokens = ft_split(request, ' ');
    if (tokens.size() != 3)
    {
        response = "<" + client.get_nick() + "> <" + tokens[0] + "> :Not enough parameters\r\n";
        return response;
    }
    // if (tokens.size() > 3)
    // {
    //     response = join_multiple_channels(tokens, client);
    //     return response;
    // }
    if (channel.channel_exists(tokens[1]) == false && (tokens.size() == 3))
        create_channel(tokens[1], tokens[2], channel, client);
    else
        response = client.get_nick() + " has joined " + tokens[1] + "\r\n";
    return response;
}

void    server::parse_request(char *read, int fd)
{
    Client client(fd);
    Channel channel;
    std::string request(read);
    std::string response;
    std::vector<std::string> tokens;
    std::string error = "ERROR: Invalid command\r\n";

    if(this->_map.count(fd) <= 0)
        this->_map.insert(std::make_pair(fd, client));
    tokens = ft_split(request, ' ');
    if (tokens[0] == "PASS")
        response = pass_response(request, this->_map[fd]);
    // else if (tokens[0] == "NICK" && response == "" && this->_map[fd].get_auth() == true)
    //     response = nick_response(request, this->_map[fd]);
    else if (tokens[0] == "JOIN" )
        response = join_response(request, this->_map[fd], channel);
    else
        response = error;
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