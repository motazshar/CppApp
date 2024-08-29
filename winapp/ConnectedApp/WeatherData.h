#pragma once
#include <string>

// WeatherData is a structure to hold weather information.
struct WeatherData
{
    std::string city;         // City name
    std::string description;  // Weather description
    float temperature = 0.0f; // Current temperature in Celsius
    float feels_like = 0.0f;  // Feels like temperature in Celsius
    int humidity = 0;         // Humidity percentage
    float wind_speed = 0.0f;  // Wind speed in meters per second
};
