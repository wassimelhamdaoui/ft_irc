#include "headers.hpp"

// void    server::bot() {
//     std::cout << "\033[1;31m" << "╔══════════════════════════════════════════╗\n"
//               << "║              Channel Rules               ║\n"
//               << "╠══════════════════════════════════════════╣\n"
//               << "║ \033[0;36m1. Be respectful and courteous to others \033[1;31m║\n"
//               << "║ \033[0;36m2. No spamming, trolling, or hate speech \033[1;31m║\n"
//               << "║ \033[0;36m3. Keep discussions on-topic             \033[1;31m║\n"
//               << "║ \033[0;36m4. No NSFW content or discussions        \033[1;31m║\n"
//               << "║ \033[0;36m5. Follow the instructions of the mods   \033[1;31m║\n"
//               << "╚══════════════════════════════════════════╝\n"
//               << "\033[0m";
// }


std::string get_weather_info(std::string json)
{
    std::string weather_key = "\"weather\":";
    std::size_t weather_pos = json.find(weather_key);
    std::string weather_info;
    if (weather_pos != std::string::npos) {
        std::size_t weather_end_pos = json.find_first_of(']', weather_pos);
        if (weather_end_pos != std::string::npos) {
            weather_info = json.substr(weather_pos + weather_key.length(), weather_end_pos - weather_pos - weather_key.length() + 1);
            return weather_info;
        }
    }
    return "";
}

std::string get_value(std::string token)
{
    std::string weather;
    std::size_t weather_pos = token.find(':');
    if (weather_pos != std::string::npos) {
        weather = token.substr(weather_pos + 1);
    }
    return weather;
}

// A helper function to extract the weather information from the API response
std::string parse_weather(std::string json, Client &client)
{
    (void)(client);
    std::string weather_info = get_weather_info(json);
    
    std::vector<std::string> tokens = ft_split(weather_info, ',');
    std::string weather = get_value(tokens[0]);
    std::string main = get_value(tokens[1]);
    std::string description = get_value(tokens[2]);
    
    std::string header = "----------------------------------------------\r\n|           CURRENT WEATHER REPORT           |\r\n----------------------------------------------\r\n";
    std::string weather_str = "|  Weather:      " + weather + "                         |\r\n";
    std::string main_str = "|  Main:         " + main + "                    |\r\n";
    std::string description_str = "|  Description:  " + description + "          |\r\n";
    std::string footer = "----------------------------------------------\r\n";

    std::string response = header + weather_str + main_str + description_str + footer;
    return (response);
}

// A helper function to handle the data received from the API
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*) userp)->append((char*) contents, size * nmemb);
    return size * nmemb;
}

std::string weather(std::string city, Client &client) {
    // The URL of the weather API endpoint
const std::string WEATHER_API_URL = "http://api.openweathermap.org/data/2.5/weather?q=";

// Your OpenWeatherMap API key
const std::string API_KEY = "13fa4f69de439413060d5076a7fbcd43";
   std::string response = "";
    // Construct the API URL with the user's input and the API key
    std::string url = WEATHER_API_URL + city + "&appid=" + API_KEY;

    // Initialize libcurl
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the API URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the function to handle the data received from the API
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // Fetch the data from the API
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else {
            if (response_string.empty() || response_string == "{\"cod\":\"404\",\"message\":\"city not found\"}")
            {
                curl_global_cleanup();
                curl_easy_cleanup(curl);
                return ":localhost 461 " + client.get_nick() + " WEATHER " + " :City not found\r\n";
            }
            else
                response = parse_weather(response_string, client);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return (response);
}

std::string server::weather_response(std::vector<std::string> tokens, Client &client)
{
    if ((tokens.size() == 2 && tokens[1] == ":") || tokens.size() < 2)
        return (":localhost 461 " + client.get_nick() + " WEATHER " + " :Not enough parameters\r\n");
    std::string response = weather(tokens[1], client);
    std::cout << response << std::endl;
    return (response);
}