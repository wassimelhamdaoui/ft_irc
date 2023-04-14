/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:03 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/14 08:45:01 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

bool check_nickname(std::string nick)
{
	for(size_t i = 0; nick[i]; i++)
	{
		if(!std::isalnum(nick[i]) && nick[i] != '_' && nick[i] != '-' && nick[i] != '.' && nick[i] != '~')
			return false;
	}
	return true;
}

std::string server::nick_response(std::vector<std::string>  split, Client &client)
{
	if(client.get_pass())
	{
		if(split.size() == 2 && split[1] == ":")
			return(":localhost 431 * NICK :No nickname given\r\n");
		if(!check_nickname(split[1]))
			return (":localhost 432 * NICK :Erroneous nickname\r\n");
		int Clientfd = getClientFd(this->_map, split[1]);
		Client OtherClient = this->_map[Clientfd];
		if(Clientfd && OtherClient.get_print())
			return (":localhost 433 " + split[1] + " NICK :Nickname already in use\r\n");
		if(Clientfd)
			return (":localhost 433 " + split[1] + " NICK :Nickname collision\r\n");
		client.set_nick(split[1]);
		client.set_reg(true);
		if(!client.get_print() && client.get_auth())
		{
			client.set_print(true);
			welcome_message(client.get_fd() , client);
		}
	}
	return ("");
}