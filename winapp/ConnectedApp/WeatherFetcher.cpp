#include "WeatherFetcher.h"
#include <httplib.h>
#include <nlohmann/json.hpp>

// Constructor
WeatherFetcher::WeatherFetcher() {}

// Method to fetch weather data
bool WeatherFetcher::FetchWeatherData(WeatherData& data, const std::string& city_name)
{
    httplib::Client cli("http://api.openweathermap.org");

    std::string encoded_city_name = url_encode(city_name);
    std::string url = "/data/2.5/weather?q=" + encoded_city_name + "&appid=" + api_key_ + "&units=metric";

    auto res = cli.Get(url.c_str());
    if (res && res->status == 200)
    {
        auto json_result = nlohmann::json::parse(res->body);

        // Populate the WeatherData structure with the fetched data
        data.city = json_result["name"];
        data.description = json_result["weather"][0]["description"];
        data.temperature = json_result["main"]["temp"];
        data.feels_like = json_result["main"]["feels_like"];
        data.humidity = json_result["main"]["humidity"];
        data.wind_speed = json_result["wind"]["speed"];

        return true;
    }
    else
    {
        // Handle failed requests
        std::cerr << "Failed to fetch weather data. Status code: "
            << (res ? std::to_string(res->status) : "No Response") << std::endl;
        return false;
    }
}

// Utility function to URL encode the city name
std::string WeatherFetcher::url_encode(const std::string& value)
{
    std::string encoded;
    char hex_buffer[4];
    for (unsigned char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c;
        }
        else {
            snprintf(hex_buffer, sizeof(hex_buffer), "%%%02X", c);
            encoded += hex_buffer;
        }
    }
    return encoded;
}
