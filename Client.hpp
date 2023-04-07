/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:12 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/06 09:58:55 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "server.hpp"
#define MAX_CLIENTS 1024
#define MAX_CHANNELS 20


class Client
{

	public:

		Client();
		Client(int fd);
		Client( Client const & src );
		~Client();

		Client &		operator=( Client const & rhs );
		int	get_fd() const;
		std::string get_nick() const;
		bool	get_pass() const;
		bool get_auth() const;

		void	set_fd(int fd);
		void	set_nick(std::string nick);
		void	set_pass(bool pass);
		void	set_auth(bool auth);
		void	set_channel(std::string channel);
		bool	get_channel(std::string channel);
		// std::string get_user() const;
		

	private:
		int 		_fd;
		std::string _nick;
		bool		_pass;
		bool 		_auth;
		std::vector<std::string> _channels;
};

#endif /* ********************************************************** CLIENT_H */