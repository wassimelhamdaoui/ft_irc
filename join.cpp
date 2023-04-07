/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:05:10 by waelhamd          #+#    #+#             */
/*   Updated: 2023/04/06 10:24:25 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"server.hpp"

std::vector<std::string> split_buff(std::string str, char sep)
{
	std::vector<std::string> res;
	std::string word;
	std::stringstream stream(str);
	size_t pos;
	getline(stream, word, sep);
	res.push_back(word);
	res.push_back(str.substr(word.size() + 1));
	return (res);
}

std::string join_request(std::string buff, Client &client)
{
	std::vector<std::string> split;
	std::string channel;
	std::string response;
	// std::stringstream stream;

	split = split_buff(buff, ' ');
	if(split.size() < 2)
		return ("461 JOIN :Not enough parameters\n");
	else if(split.size() == 2)
	{
		split = ft_split(split[1], ' ');
		std::vector<std::string> names;
		std::vector<std::string> key;
		names = ft_split(split[0], ',');
		if(split.size() > 1)
			key = ft_split(split[1], ',');
		for(size_t i = 0; i < names.size(); i++)
		{
			if(names[i][0] != '#')
				return ("403 " + names[i] + " :No such channel\n");
			else if(client.get_channel(names[i]))
				return ("443 " + names[i] + " :is already on channel\n");
			else
			{
				client.set_channel(names[i]);
				this->channels[names[i]].push_back(client);
				response += "JOIN " + names[i] + " " + client.get_nick();
				if(key.size() > i)
					response += " " + key[i];
				response += " " + client.get_user();
				
			}
		}
	}
}