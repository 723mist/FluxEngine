#include "engine.h"

int main() {
    Engine engine;

    engine.Init("VE", 500, 500);

    TextureManager tm;
    Debug dbtool;

    tm.LoadTexture();
    dbtool.FPSCounter();

    engine.BackgroundColor(0.2, 0.3, 0.3);

    engine.Run();
    engine.Destroy();

    return 0;
}
