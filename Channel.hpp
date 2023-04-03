#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{
	private:
	std::string _name;
	std::string _pass;
	bool  _aut_key;
	std::map<std::string, int> cannels;

	public:

		Channel();
		Channel(std::string name, std::string pass)
		Channel( Channel const & src );
		~Channel();

};

#endif 