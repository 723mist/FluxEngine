#include "engine.h"

int main() {
    Engine engine;

    engine.Init("Flux Engine TEST 3D", 500, 500);

    TextureManager tm;
    tm.LoadTexture();

    engine.BackgroundColor(0.2f, 0.3f, 0.3f);

    engine.Run();
    engine.Destroy();

    return 0;
}
