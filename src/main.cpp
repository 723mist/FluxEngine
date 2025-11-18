#include "engine.h"

int main() {
    Engine engine;

    engine.Init("VE", 500, 500);

    TextureManager tm;

    tm.LoadTexture();

    engine.Run();
    engine.Destroy();

    return 0;
}
