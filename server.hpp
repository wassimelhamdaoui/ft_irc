#ifndef SERVER_HPP
# define SERVER_HPP
#define USERLEN 12
#include "Client.hpp"

class Client;

class server
{
	private:
		std::unordered_map<int, std::pair<std::string, bool> > client_data;
		static int _port;
		static std::string _pass;
		std::map<int, Client> _map;

		
	public:
		server(/* args */);
		server(int port, std::string pass);

		/**********  server methodes *********/

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
		std::string 	pass_response(std::string buff, Client &client);
		std::string 	nick_response(std::string buff, Client &client);
		std::string 	user_response(std::string buff, Client &client);
		std::string 	check_authentication(std::string, Client &client);
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
std::vector<std::string> ft_split(std::string str, char sep);
std::string ft_message(std::string a, std::string b, std::string c, int flg);


# endif