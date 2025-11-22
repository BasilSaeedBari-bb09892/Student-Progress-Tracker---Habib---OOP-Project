#include "App.hpp"

int main() {
    // Set the visual scheme to look modern
    Fl::scheme("gtk+");
    
    // Create the App Controller
    App app;
    
    // Assign the singleton pointer for static callbacks
    App::instance = &app;
    
    // Run the FLTK main loop
    return app.run();
}