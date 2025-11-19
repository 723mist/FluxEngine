#include "engine.h"

int main() {
    Engine engine;

    engine.Init("VE", 500, 500);

    TextureManager tm;
    tm.LoadTexture();

    engine.BackgroundColor(1.0, 1.0, 1.0);

    engine.Run();
    engine.Destroy();

    return 0;
}
