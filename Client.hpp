/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:12 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/02 20:22:13 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>

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


	private:
		int 		_fd;
		std::string _nick;
		bool		_pass;
		bool 		_auth;


};

#endif /* ********************************************************** CLIENT_H */