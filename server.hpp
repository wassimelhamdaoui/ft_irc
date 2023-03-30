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

class server
{
	private:
		int _port;
		std::string pass;
	public:
		server(/* args */);
		server(int port, std::string pass);

		/**********  sever methodes *********/

		std::string		get_pass();
		int				get_port();
		void        	run();
		struct addrinfo *get_address();
		int             request_handler(int i, fd_set *master);
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
char *parse_request(char *read);

# endif