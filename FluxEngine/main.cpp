#include "flux_engine.h"

int main() {
    Window Window;
    Texture texture;
    Map map("map");

    Window.create();

    Sprite player;
    player.position = vec2(375, 275);
    player.size = vec2(50, 50);
    player.setTexture("Content/placeholder.jpg");

    Object box("box");
    box.setTexture("Content/wall.jpg");

    map.addObject(box);
    Window.addSprite(player);
    Window.setMap(&map);
    Window.render();
    Window.close();

    return 0;
}
