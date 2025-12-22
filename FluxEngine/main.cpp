#include "flux_engine.h"

int main() {
    Window Window;
    Texture texture;
    Map Map("Map");

    Window.Create();

    Object object1("Object1");
    object1.position = vec3(1.0f, 1.0f, 1.0f);
    object1.rotation = vec3(0.0f, 0.0f, 0.0f);
    object1.scale = vec3(1.0f, 1.0f, 1.0f);
    object1.LoadTexture("Content/wall.jpg");
    Map.AddObject(object1);

    Object object2("Object2");
    object2.position = vec3(1.0f, 1.0f, -1.0f);
    object2.rotation = vec3(0.0f, 0.0f, 0.0f);
    object2.scale = vec3(1.0f, 1.0f, 1.0f);
    object2.LoadTexture("Content/placeholder.jpg");
    Map.AddObject(object2);

    Object object3("Object3");
    object3.position = vec3(-1.0f, 1.0f, -1.0f);
    object3.rotation = vec3(0.0f, 0.0f, 0.0f);
    object3.scale = vec3(1.0f, 1.0f, 1.0f);
    object3.LoadTexture("Content/Defult.jpg");
    Map.AddObject(object3);

    Object object4("Object4");
    object4.position = vec3(-1.0f, 1.0f, 1.0f);
    object4.rotation = vec3(0.0f, 0.0f, 0.0f);
    object4.scale = vec3(1.0f, 1.0f, 1.0f);
    Map.AddObject(object4);

    Object object5("Object5");
    object5.position = vec3(0.0f, 0.0f, 0.0f);
    object5.rotation = vec3(0.0f, 0.0f, 0.0f);
    object5.scale = vec3(1.0f, 1.0f, 1.0f);
    Map.AddObject(object5);

    Object object6("Object6");
    object6.position = vec3(1.0f, -1.0f, 1.0f);
    object6.rotation = vec3(0.0f, 0.0f, 0.0f);
    object6.scale = vec3(1.0f, 1.0f, 1.0f);
    Map.AddObject(object6);

    Object object7("Object7");
    object7.position = vec3(1.0f, -1.0f, -1.0f);
    object7.rotation = vec3(0.0f, 0.0f, 0.0f);
    object7.scale = vec3(1.0f, 1.0f, 1.0f);
    Map.AddObject(object7);

    Object object8("Object8");
    object8.position = vec3(-1.0f, -1.0f, 1.0f);
    object8.rotation = vec3(0.0f, 0.0f, 0.0f);
    object8.scale = vec3(1.0f, 1.0f, 1.0f);
    Map.AddObject(object8);

    Object object9("Object9");
    object9.position = vec3(-1.0f, -1.0f, -1.0f);
    object9.rotation = vec3(0.0f, 0.0f, 0.0f);
    object9.scale = vec3(1.0f, 1.0f, 1.0f);
    Map.AddObject(object9);

    Window.SetMap(&Map);
    Window.Render();
    Window.Close();

    return 0;
}
