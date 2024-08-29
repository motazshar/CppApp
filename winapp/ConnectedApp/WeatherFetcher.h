#pragma once
#include "WeatherData.h"
#include <string>

class WeatherFetcher
{
public:
    WeatherFetcher();  // Constructor
    bool FetchWeatherData(WeatherData& data, const std::string& city_name);  // Method to fetch weather data

private:
    std::string api_key_ = "2a93574016bad55ef46b8617174f7ce5";  // API key for OpenWeatherMap
    std::string url_encode(const std::string& value); // Utility function to URL encode city names
};
