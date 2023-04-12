/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:01:49 by waelhamd          #+#    #+#             */
/*   Updated: 2023/04/12 08:37:55 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

void 	split_command(std::string buff, std::vector<std::string> &split)
{
	std::vector<std::string> tmp;
		
	tmp = ft_split(buff, ':');
	//change split with substr to avoid if msg has :
	split = ft_split(tmp[0], ' ');
	if (tmp.size() > 1)
		split.push_back(tmp[1]);
}

std::string		server::privmsg_response(std::string buff, Client &client)
{
	std::vector<std::string>	split;
	std::vector<std::string>	recipient;
	//send message to channel
	//send message to user

	split_command(buff, split);
	if (split.size() == 1)
		return (client.get_fd(), ":" + client.get_nick() + " 461 PRIVMSG :Not enough parameters\n");
	else if (split.size() == 2)
		return (client.get_fd(), ":" + client.get_nick() + " 412 PRIVMSG :No text to send\n");
	else
	{
		recipient = ft_split(split[1], ','); //split recipient
		std::vector<std::string>::iterator it = recipient.begin();
		for(; it != recipient.end(); it++)
		{
			if (this->_channels.find(*it) != this->_channels.end())//if recipient is a channel
			{
				this->_channels[*it].broadcast_message(split[2], client.get_nick(), client.get_fd());
			}
			else if (getClinetfd(this->_map, *it))//if recipient is a user
			{
				std::string tmp = ":" + client.get_nick() + " PRIVMSG " + *it + " :" + split[2] + "\r\n";
				send(getClinetfd(this->_map, *it), tmp.c_str(), tmp.size(), 0);
			}
			else
				return ("401 " + client.get_nick() + " " + *it + " :No such nick/channel");
		}
	}
	return ("");
	
}