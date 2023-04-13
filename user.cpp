/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:33:30 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/08 06:25:51 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

void    welcome_message(int fd, Client &client)
{
    std::string message = ":localhost 001 " + client.get_nick() + " :Welcome to IRC Network " + client.get_nick() + " \r\n";
    send(fd, (char *)message.c_str(), message.length(), 0);
    message = ":localhost 002 " + client.get_nick() + " :Your host is localhost, running version 1.0\r\n";
    send(fd, (char *)message.c_str(), message.length(), 0);
    message = ":localhost 003 " + client.get_nick() + " :This server was created 2023-03-25\r\n";
    send(fd, (char *)message.c_str(), message.length(), 0);
}

std::string server::user_response(std::vector<std::string> split, Client &client)
{
	if(client.get_pass())
	{
		if(client.get_auth())
			return(":localhost 462 USER :You may not reregister\r\n");
		if(split.size() < 5) // || split[1].length() != USERLEN
			return(":localhost 461 USER :Not enough parameters\r\n");
		// if(split[1][0] != '~')
		// 	return(":localhost USER :Invalid username you must start with (~)\r\n");
		client.set_userName(split[1]);
		client.set_auth(true);
		if(client.get_reg() && !client.get_print())
		{
			client.set_print(true);
			welcome_message(client.get_fd(), client);
		}
	}
	return("");
}
