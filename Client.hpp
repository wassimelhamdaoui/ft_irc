/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:12 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/16 18:38:14 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#define MAX_CLIENTS 1024
#define MAX_CHANNELS 20
# include "headers.hpp"


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
		std::string get_userName() const;
		bool	get_pass() const;
		bool	get_reg() const;
		bool get_auth() const;
		bool get_print() const;

		void	set_nick(std::string nick);
		void	set_userName(std::string userName);
		void	set_pass(bool pass);
		void	set_reg(bool reg);
		void	set_auth(bool auth);
		void	set_channel(std::string channel);
		std::vector<std::string>	&get_channel();
		bool	check_member(std::string memeber);	
		void	remove_channel(std::string channel);
		void	set_print(bool print);


	private:
		int 		_fd;
		std::string _nick;
		std::string _userName;
		bool		_pass;
		bool		_reg;
		bool 		_auth;
		std::vector<std::string> _channels;//
		bool 		_print;
};

#endif /* ********************************************************** CLIENT_H */