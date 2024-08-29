#include "DrawThread.h"
#include "GuiMain.h"
#include "../../shared/ImGuiSrc/imgui.h"
#include "WeatherFetcher.h"
#include "WeatherData.h"
#include <algorithm>
#include <cstring> // For strncpy

// Function to add a city to the search history
void DrawThread::AddToSearchHistory(const std::string& city)
{
    // Remove the city if it already exists in history (to avoid duplicates)
    auto it = std::remove(search_history.begin(), search_history.end(), city);
    search_history.erase(it, search_history.end());

    // Add the city to the front of the history
    search_history.insert(search_history.begin(), city);

    // Keep only the last 3 searches
    if (search_history.size() > 3)
    {
        search_history.pop_back();
    }
}

// Function responsible for drawing the application window
void DrawAppWindow(void* data_ptr)
{
    DrawThread* draw_thread = static_cast<DrawThread*>(data_ptr);
    static std::string displayed_info = "";
    static char buff[200];
    static bool data_retrieved = false;

    WeatherData data;
    WeatherFetcher fetcher_;

    ImGui::Begin("Weather Forecast");

    // Section for favorite cities
    ImGui::Text("Favorite Cities:");
    if (draw_thread->favorite_cities.empty())
    {
        ImGui::Text("No favorite cities added.");
    }
    else
    {
        for (const auto& city : draw_thread->favorite_cities)
        {
            if (ImGui::Button(city.c_str()))
            {
                strncpy_s(buff, city.c_str(), sizeof(buff) - 1);
                buff[sizeof(buff) - 1] = '\0'; // Ensure null termination
                ImGui::SameLine();
                if (ImGui::Button("Search"))
                {
                    if (fetcher_.FetchWeatherData(data, city))
                    {
                        displayed_info = "Weather Information For: " + data.city + "\n";
                        displayed_info += "Description: " + data.description + "\n";
                        displayed_info += "Temperature: " + std::to_string(data.temperature) + " C\n";
                        displayed_info += "Feels Like: " + std::to_string(data.feels_like) + " C\n";
                        displayed_info += "Humidity: " + std::to_string(data.humidity) + " %\n";
                        displayed_info += "Wind Speed: " + std::to_string(data.wind_speed) + " m/s\n";
                        data_retrieved = true;

                        draw_thread->AddToSearchHistory(city);
                    }
                    else
                    {
                        data_retrieved = false;
                    }
                }
            }
        }
    }


    // Section to add a city to favorites
    ImGui::InputText("City_Name", buff, sizeof(buff));
    ImGui::SameLine();
    if (ImGui::Button("Search"))
    {
        std::string city_name = buff;
        if (fetcher_.FetchWeatherData(data, city_name))
        {
            displayed_info = "Weather Information For: " + data.city + "\n";
            displayed_info += "Description: " + data.description + "\n";
            displayed_info += "Temperature: " + std::to_string(data.temperature) + " C\n";
            displayed_info += "Feels Like: " + std::to_string(data.feels_like) + " C\n";
            displayed_info += "Humidity: " + std::to_string(data.humidity) + " %\n";
            displayed_info += "Wind Speed: " + std::to_string(data.wind_speed) + " m/s\n";
            data_retrieved = true;

            draw_thread->AddToSearchHistory(city_name);
        }
        else
        {
            data_retrieved = false;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Add to Favorites"))
    {
        if (std::find(draw_thread->favorite_cities.begin(), draw_thread->favorite_cities.end(), buff) == draw_thread->favorite_cities.end())
        {
            draw_thread->favorite_cities.push_back(buff);
        }
    }

    // Section for search history
    ImGui::Text("Last 3 Searched Cities:");
    if (draw_thread->search_history.empty())
    {
        ImGui::Text("No search history available.");
    }
    else
    {
        for (const auto& city : draw_thread->search_history)
        {
            if (ImGui::Button(city.c_str()))
            {
                strncpy_s(buff, city.c_str(), sizeof(buff) - 1);
                buff[sizeof(buff) - 1] = '\0'; // Ensure null termination
                ImGui::SameLine();
                if (ImGui::Button("Search"))
                {
                    if (fetcher_.FetchWeatherData(data, city))
                    {
                        displayed_info = "Weather Information For: " + data.city + "\n";
                        displayed_info += "Description: " + data.description + "\n";
                        displayed_info += "Temperature: " + std::to_string(data.temperature) + " C\n";
                        displayed_info += "Feels Like: " + std::to_string(data.feels_like) + " C\n";
                        displayed_info += "Humidity: " + std::to_string(data.humidity) + " %\n";
                        displayed_info += "Wind Speed: " + std::to_string(data.wind_speed) + " m/s\n";
                        data_retrieved = true;

                        draw_thread->AddToSearchHistory(city);
                    }
                    else
                    {
                        displayed_info = "Failed to retrieve weather data. Please try again.";
                        data_retrieved = false;
                    }
                }
            }
        }
    }



    if (data_retrieved)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 255, 255));  
        ImGui::TextUnformatted(displayed_info.c_str());
        ImGui::PopStyleColor();  
    }
    else
    {
        ImGui::Text("No data available.");
    }

    ImGui::End();
}

// Operator overloading to start the DrawThread
void DrawThread::operator()(void* data)
{
    GuiMain(DrawAppWindow, this);
}