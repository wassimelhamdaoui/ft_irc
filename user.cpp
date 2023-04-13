/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:33:30 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/13 09:57:28 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"


std::string server::user_response(std::vector<std::string> split, Client &client)
{
	if(client.get_pass())
	{
		std::string nick = client.get_nick();
		if (nick.empty())
			nick = "*";
		if(client.get_auth())
			return(":localhost 462 " + nick + " USER :You may not reregister\r\n");
		if(split.size() < 5) // || split[1].length() != USERLEN
			return(":localhost 461 " + nick + " USER :Not enough parameters\r\n");
		client.set_userName(split[1]);
		client.set_auth(true);
		if(client.get_reg() && !client.get_print())
		{
			client.set_print(true);
			welcome_message(client.get_fd() , client);;
		}
	}
	return("");
}
