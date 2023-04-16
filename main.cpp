#include "headers.hpp"
#include "server.hpp"

void    welcome_message(int fd, Client &client)
{
    std::string message = ":localhost 001 " + client.get_nick() + " :Welcome to IRC Network " + client.get_nick() + " \r\n";
    send(fd, (char *)message.c_str(), message.length(), 0);
    message = ":localhost 002 " + client.get_nick() + " :Your host is localhost, running version 1.0\r\n";
    send(fd, (char *)message.c_str(), message.length(), 0);
    message = ":localhost 003 " + client.get_nick() + " :This server was created 2023-03-25\r\n";
    send(fd, (char *)message.c_str(), message.length(), 0);
}


void ft_replace(std::string &str, char c, std::string rep)
{
    size_t pos = str.find(c);
	while(pos != std::string::npos)
	{
		str.replace(pos, 1, rep);
		pos = str.find('\t');
	}
}

std::string to_upper(std::string str)
{
    for(int i = 0; str[i]; i++)
        str[i] = std::toupper(str[i]);

    return str;
}

std::vector<std::string> modifier(std::string str)
{
    std::vector<std::string> split;
    ft_replace(str, '\t', " ");
    ft_replace(str, '\r', " ");
    ft_replace(str, '\n', " ");
    split = ft_split(str, ' ');

    return split;
}

void    server::parse_request(char *read, int fd, fd_set *master)
{
    // std::cout << read << std::endl;
    Client client(fd);
    std::string request(read);
    std::string response;
    std::vector<std::string> split;

    if(!this->_map.count(fd))
        this->_map.insert(std::make_pair(fd, client));
    split = modifier(request);
    if(split.empty())
        response = "";
    else if(to_upper(split[0]) == "PASS")
        response = pass_response(split, this->_map[fd]);
    else if(to_upper(split[0]) == "USER")
        response = user_response(split, this->_map[fd]);
    else if(to_upper(split[0]) == "NICK")
        response = nick_response(split, this->_map[fd]);
    else if(to_upper(split[0]) == "JOIN" )
        response = join_response(split, this->_map[fd]);
    else if (to_upper(split[0]) == "PART")
        response = part_response(split, this->_map[fd]);
    else if (to_upper(split[0]) == "TOPIC")
        response = topic_response(split, this->_map[fd]);
    else if(to_upper(split[0]) == "INVITE")
        response = invite_response(split, this->_map[fd]);
    else if(to_upper(split[0]) == "KICK")
        response = kick_response(split, this->_map[fd]);
    else if(to_upper(split[0]) == "MODE")
        response = mode_response(split, this->_map[fd]);
    else if (to_upper(split[0]) == "QUIT")
        response = quit_response(split, this->_map[fd], master);
    else if (to_upper(split[0]) == "PRIVMSG")
       response = privmsg_response(request, this->_map[fd]);
    else if(to_upper(split[0]) == "NOTICE")
       response = notice_response(request, this->_map[fd]);
    else if(to_upper(split[0]) == "WEATHER")
        response = weather_response(split, this->_map[fd]);
    else
        response = "";
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