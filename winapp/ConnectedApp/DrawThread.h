#pragma once
#include <vector>
#include <string>

// DrawThread is responsible for rendering the UI.
class DrawThread
{
public:
    // Overload the function call operator to start the drawing thread
    void operator()(void* data);

    // Function to update search history
    void AddToSearchHistory(const std::string& city);

    // Public members to store favorite cities and search history
    std::vector<std::string> favorite_cities;   // List of favorite cities
    std::vector<std::string> search_history;    // List to store the last 3 searched cities
};

