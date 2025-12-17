#include "flux_engine.h"

int main() {
    Window Window;
    Map Map;

    Window.Create();

    Object cube1("Cube1");
    Object cube2("Cube2");
    Object cube3("Cube3");
    Object cube4("Cube4");
    Object cube5("Cube5");
    Object cube6("Cube6");
    Object cube7("Cube7");
    Object cube8("Cube8");
    Object cube9("Cube9");

    cube1.position = glm::vec3(-1.0f, -1.0f, -2.0f);
    cube2.position = glm::vec3(0.0f, -1.0f, -2.0f);
    cube3.position = glm::vec3(1.0f, -1.0f, -2.0f);
    cube4.position = glm::vec3(-1.0f, 0.0f, -2.0f);
    cube5.position = glm::vec3(0.0f, 0.0f, -2.0f);
    cube6.position = glm::vec3(1.0f, 0.0f, -2.0f);
    cube7.position = glm::vec3(-1.0f, 1.0f, -2.0f);
    cube8.position = glm::vec3(0.0f, 1.0f, -2.0f);
    cube9.position = glm::vec3(1.0f, 1.0f, -2.0f);

    Map.AddObject(cube1);
    Map.AddObject(cube2);
    Map.AddObject(cube3);
    Map.AddObject(cube4);
    Map.AddObject(cube5);
    Map.AddObject(cube6);
    Map.AddObject(cube7);
    Map.AddObject(cube8);
    Map.AddObject(cube9);

    Window.SetMap(&Map);

    Window.Render();
    Window.Close();

    return 0;
}
