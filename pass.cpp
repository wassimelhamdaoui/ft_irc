/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:52:15 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/02 06:34:42 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::vector<std::string> ft_split(std::string str, char sep)
{
    std::vector<std::string> res;
    std::string word;
    std::stringstream stream(str);

    for(; std::getline(stream, word, sep); ){
        if (!word.empty())
            res.push_back(word);
    }
    return (res);
}

void    erase_charcter(std::string& str, char c)
{
    size_t pos = str.find(c);
    while(pos != std::string::npos)
    {
        str.erase(pos, 1);
        pos = str.find(c);
    }
}

std::string pass_response(std::string buff, Client &client)
{
	server myserver;
	if(!client.get_pass())
	{
		std::vector<std::string> Vect;
		Vect = ft_split(buff, ' ');
		if(Vect[0] != "PASS")
			return("You must enter the password <PASS>\n");
		size_t param = Vect.size();
		if(param < 2)
			return ("<client> <command> :Not enough parameters\n");
		if(Vect[1] != myserver.get_pass())
			return("<client> :Password incorrect\n");
		client.set_pass(true);
		return("<client> : welcome\n");
	}
	else
		return "<client> :You may not reregister\n";
}


