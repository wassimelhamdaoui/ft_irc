/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:05:10 by waelhamd          #+#    #+#             */
/*   Updated: 2023/04/16 15:12:53 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"headers.hpp"

std::string make_time(void)
{
	time_t curr_time;
	curr_time = time(NULL);
	return std::to_string(curr_time);
}


std::string server::join_response(std::vector<std::string> split, Client &client)
{
	Channel mychannel;

	if(!client.get_print())
		return (":localhost 451 * JOIN :You must finish connecting with nickname first.\r\n");
	if(split.size() == 1 || (split.size() == 2 && split[1] == "#"))
		return(":localhost 461 " + client.get_nick() + " " + split[0] + " :Not enough parameters\r\n");
	else if(split.size() >= 2)
	{
		std::vector<std::string> names;
		std::vector<std::string> key;
		names = ft_split(split[1], ',');
		if(split.size() > 2)
			key = ft_split(split[2], ',');
		for(size_t i = 0; i < names.size(); i++)
		{
			if(names[i][0] != '#')
				mysend(client.get_fd(), ":localhost 403 " + client.get_nick() + " " + names[i] + " :No such channel\r\n");
			else if(client.check_member(names[i]))
				mysend(client.get_fd(), ":localhost 443 " + client.get_nick() + " " + names[i] + ":is already on channel\r\n");
			else
			{
				if(!this->_channels.count(names[i]))
				{//if channel does not exist
					client.set_channel(names[i]);
					if(key.size() > i)
						mychannel = Channel(names[i], key[i]);
					else 
						mychannel = Channel(names[i], "");

					mychannel.add_member(client.get_fd());
					mychannel.add_moderator(client.get_fd());
					mychannel.set_creation_time(make_time());
					this->_channels.insert(make_pair(names[i], mychannel));

					mysend(client.get_fd(), ":" + client.get_nick() + "!" + client.get_userName() + "@" + get_adderss() + " JOIN :" + names[i] + "\r\n");
				}
				else
				{//if channel exists
					if(this->_channels[names[i]].get_limitMode() && this->_channels[names[i]].get_limit() <= (int)this->_channels[names[i]].get_members().size())
						mysend(client.get_fd(), ":localhost 471 " + client.get_nick() + " " + names[i] + " :Cannot join channel (+l)\r\n");
					else if(this->_channels[names[i]].get_inviteMode())
					{
						if(this->_channels[names[i]].is_invited(client.get_nick()))
						{
							client.set_channel(names[i]);
							this->_channels[names[i]].add_member(client.get_fd());
							this->_channels[names[i]].broadcast_message(":" + client.get_nick() + "!~" + client.get_userName() + "@"+ get_adderss() + " JOIN :" + names[i] + "\r\n", 0);
						}
						else
							mysend(client.get_fd(), ":localhost 473 " + client.get_nick() + " " + names[i] + " :Cannot join channel (+i)\r\n");
					}
					else
					{
						if(key.size() > i)
						{//if key is provided
							if(this->_channels[names[i]].get_pass() == key[i])
							{
								client.set_channel(names[i]);
								this->_channels[names[i]].add_member(client.get_fd());
								this->_channels[names[i]].broadcast_message(":" + client.get_nick() + "!~" + client.get_userName() + "@"+ get_adderss() + " JOIN :" + names[i] + "\r\n", 0);
							}
							else
								mysend(client.get_fd(), ":localhost 475 " + client.get_nick() + " " + names[i] + " :Cannot join channel (+k)\r\n");
						}
						else
						{//if key is not provided
							if(this->_channels[names[i]].get_pass() == "")
							{
								client.set_channel(names[i]);
								this->_channels[names[i]].add_member(client.get_fd());
								this->_channels[names[i]].broadcast_message(":" + client.get_nick() + "!~" + client.get_userName() + "@"+ get_adderss() + " JOIN :" + names[i] + "\r\n", 0);
							}
							else
								mysend(client.get_fd(), ":localhost 475 " + client.get_nick() + " " + names[i] + " :Cannot join channel (+k)\r\n");
						}
					}
				}
			}
		}
	}
	return ("");
}