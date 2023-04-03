/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:15 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/02 20:22:16 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client(): _fd(0), _nick(""), _pass(false),_auth(false)
{
}
Client::Client(int fd): _fd(fd), _nick(""), _pass(false), _auth(false)
{
}
Client::Client( const Client & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Client::~Client()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Client &				Client::operator=( Client const & rhs )
{
	this->_fd = rhs._fd;
	this->_nick = rhs._nick;
	this->_pass = rhs._pass;
	this->_auth = rhs._auth;
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int Client::get_fd() const{

	return this->_fd;
}

std::string Client::get_nick() const{

	return this->_nick;
}
bool Client::get_pass() const{

	return this->_pass;
}

bool Client::get_auth() const{

	return this->_auth;
}

void	Client::set_fd(int fd){

	this->_fd = fd;
}

void	Client::set_nick(std::string nick)
{
	this->_nick = nick;
}

void Client::set_pass(bool pass)
{
	this->_pass = pass;
}

void	Client::set_auth(bool auth)
{
	this->_auth = auth;
}


/* ************************************************************************** */

/* ************************************************************************** */