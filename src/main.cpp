#include <core/window.hpp>
#include <core/application.hpp>
#include<utils/logger.hpp>
int main() {
    // Create and run the application
    log_info("Started");
    Application app;
    return app.run();
}