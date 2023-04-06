/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:15 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/06 08:45:17 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client(): _fd(0), _nick("unknown"),_userName("userName"), _pass(false), _reg(false),_auth(false)
{
}
Client::Client(int fd): _fd(fd), _nick("unknown"),_userName("userName"), _pass(false), _reg(false), _auth(false), _print(false)
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
std::string Client::get_userName() const{

	return this->_userName;
}
bool Client::get_pass() const{

	return this->_pass;
}

bool Client::get_auth() const{

	return this->_auth;
}

bool Client::get_reg() const{

	return this->_reg;
}

bool Client::get_print() const{

	return this->_print;
}

void	Client::set_fd(int fd){

	this->_fd = fd;
}

void	Client::set_nick(std::string nick)
{
	this->_nick = nick;
}

void	Client::set_userName(std::string userName)
{
	this->_userName = userName;
}

void Client::set_pass(bool pass)
{
	this->_pass = pass;
}

void Client::set_reg(bool reg)
{
	this->_reg = reg;
}
void	Client::set_auth(bool auth)
{
	this->_auth = auth;
}
void	Client::set_print(bool print)
{
	this->_print = print;
}


/* ************************************************************************** */

/* ************************************************************************** */