/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:03 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/07 06:09:42 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

bool check_double(std::map<int, Client> Map, std::string str)
{
	std::map<int, Client>::iterator it;
	if(Map.size() > 0)
	{
		for(it = Map.begin(); it != Map.end(); it++)
		{
			if(it->second.get_nick() == str)
				return true;
		}
	}
	return false;
}

bool check_nickname(std::string nick)
{
	for(size_t i = 0; nick[i]; i++)
	{
		if(!std::isalnum(nick[i]) && nick[i] != '_' && nick[i] != '-' && nick[i] != '.' && nick[i] != '~')
			return false;
	}
	return true;
}

std::string server::nick_response(std::string buff, Client &client)
{
	std::vector<std::string> split;
	
	split = ft_split(buff, ' ');
	if(client.get_pass() && !split.empty())
	{
		if(!client.get_auth() && split[0] != "USER" && split[0] != "NICK")
			return (client.get_nick() + " :You must enter <NICK> <USER>\n");
		if(split[0] == "NICK")
		{
			if(split.size() < 2)
				return(ft_message("NICK", client.get_nick(), "No nickname given", 1));
			if(!check_nickname(split[1]))
				return (ft_message(client.get_nick(), split[1], "Erroneus nickname", 1));
			if(check_double(this->_map, split[1]))
				return (ft_message(client.get_nick(), split[1], "Nickname is already in use", 1));
			// if(check_double(this->_map, split[1]))
			// 	return(client.get_nick() + " " + split[1] + " :Nickname collision\n");
			client.set_nick(split[1]);
			client.set_reg(true);
			if(!client.get_print() && client.get_auth())
			{
				client.set_print(true);
				return(client.get_nick() +  ": You are successfully regeistred\n");
			}
		} 
	}
	return (this->user_response(buff, client));
}