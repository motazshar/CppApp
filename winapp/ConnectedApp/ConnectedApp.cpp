#include "DrawThread.h"
#include <iostream>
#include <thread> // Include the thread header

int main()
{
    // Start the drawing thread with the UI
    DrawThread draw_thread;
    std::thread draw_th([&] { draw_thread(nullptr); }); // Pass nullptr since we're not using shared state

    std::cout << "Running...\n";

    // Join the thread before exiting to ensure proper cleanup

    draw_th.join();


    return 0;
}


