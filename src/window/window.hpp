#include <GLFW/glfw3.h>
#include "iostream"

class Engine {
private:
    bool tFPS = false;
    bool cFPS = false;
    double uFPS = 0.3; //Update FPS time
    bool VSYNC = true;
public:
    void FPS(bool FPS_in_title = true, bool FPS_in_console = true);
    void UpdateFPS(double time_for_update_FPS = 0.3);
    void VSync(bool VSync = true);
    int Window(const char* windowTitle = "Simple title", int width = 500, int height = 500, bool resize = true);
};
