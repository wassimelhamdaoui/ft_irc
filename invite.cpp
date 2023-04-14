/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 06:32:27 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/14 09:52:03 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"
#include "server.hpp"


bool check_inVect(std::vector<int> vect, int value)
{
	std::vector<int>::iterator it;

	it = std::find(vect.begin(), vect.end(), value);
	if(it != vect.end())
		return true;
	return false;
}

int getClientFd(std::map<int, Client> map, std::string nickname)
{
	std::map<int, Client>::iterator it;

	for(it = map.begin(); it != map.end(); it++)
	{
		if(it->second.get_nick() == nickname)
			return (it->first);
	}
	return 0;
}

std::string	server::invite_response(std::vector<std::string> split, Client &client)
{
	int		Clientfd;
	Channel channel;

	if(client.get_print())
	{
		if(split.size() < 3)
			return(":localhost 461 " + client.get_nick() + " INVITE :Not enough parameters\r\n");
		if(!this->_channels.count(split[2]))
			return (":localhost 403 " + client.get_nick() + " " + split[2] + " :No such channel\r\n");
		channel = this->_channels[split[2]];
		if(channel.get_inviteMode() && !check_inVect(channel.get_moderators(), client.get_fd()))
			return (":localhost 482 " + client.get_nick() + " " + split[2] + " :You're not channel operator\r\n");
		if(!check_inVect(channel.get_members(), client.get_fd()))
			return (":localhost 442 " + client.get_nick() + " " + split[2] + " :You're not on that channel\r\n");
		Clientfd = getClientFd(this->_map, split[1]);
		if(check_inVect(channel.get_members(), Clientfd))
			return (":localhost 443 " + client.get_nick() + " " + split[1] + " " + split[2] +  " :is already on channel\r\n");
		if(Clientfd)
		{
			this->_channels[split[2]].add_invited_list(split[1]);
			std::string msg = client.get_nick() + " invited you to " + split[2] + "\r\n";
			send(Clientfd, msg.c_str(), msg.size(), 0);
			return (client.get_nick() + " :Invited " + split[1] + " to " + split[2] + "\r\n");
		}			
	}
	return "";
}