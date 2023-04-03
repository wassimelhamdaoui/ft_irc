#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <poll.h>
# include <sys/select.h>
# include <string.h>
# include <string>
# include<sstream>
# include <stdexcept>
#include <stdlib.h>
#include <vector>
#include <map>
#include <stack>
#include <unordered_map>
#include "Client.hpp"


class server
{
	private:
		std::unordered_map<int, std::pair<std::string, bool> > client_data;
		static int _port;
		static std::string _pass;
		static std::map<int, Client> _map;
		
	public:
		server(/* args */);
		server(int port, std::string pass);

		/**********  sever methodes *********/

		std::string		get_pass();
		int				get_port();
		bool			get_authentication();
		void			set_pass(std::string pass);
		void			set_port(int port);
		void			set_authentication(bool);
		void        	run();
		struct addrinfo *get_address();
		int             request_handler(int i, fd_set *master);
		void   			parse_request(char *read, int fd);
		int 			create_socket(struct addrinfo *bind_adress);
		bool			bind_and_listen(int socket_listen, struct addrinfo *bind_adress);
		int				accept_connection(int socket_listen, fd_set *master, int *max_socket);

		/**********  destructor *********/
		~server();
};

bool is_valid_arg(int ac, char **av);

/***** SERVER FUNCTIONS ****/
int request_handler(int i, fd_set *master);
int create_socket(struct addrinfo *bind_adress);
bool    bind_and_listen(int socket_listen, struct addrinfo *bind_adress);
int accept_connection(int socket_listen, fd_set *master, int *max_socket);
//std::string parse_request(char *read);
void    parse_request(char *read, int fd);
char	**split(char *str, char delim);
std::string pass_response(std::string buff, Client &client);

# endif