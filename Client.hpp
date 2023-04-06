/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:12 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/06 08:44:04 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "server.hpp"


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

		void	set_fd(int fd);
		void	set_nick(std::string nick);
		void	set_userName(std::string userName);
		void	set_pass(bool pass);
		void	set_reg(bool reg);
		void	set_auth(bool auth);
		void	set_print(bool print);


	private:
		int 		_fd;
		std::string _nick;
		std::string _userName;
		bool		_pass;
		bool		_reg;
		bool 		_auth;
		bool 		_print;
};

#endif /* ********************************************************** CLIENT_H */