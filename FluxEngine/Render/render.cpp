#include "../Window/window.hpp"

float FOV = 90;

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        FOV = 45;
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        FOV = 90;
}

void Window::render() {
    vec3 coral(1.0f, 0.5f, 0.31f);
    vec3 lightColor(1.0f, 1.0f, 1.0f);
    vec3 toyColor(1.0f, 0.5f, 0.31f);
    vec3 result = lightColor * toyColor;
    //texture.LoadTexture("Content/water.jpg");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader->use();

        const float radius = 3.0f;
        float camX = sin(glfwGetTime() * 0.5f) * radius;
        float camY = cos(glfwGetTime() * 0.5f) * radius;
        float camZ = cos(glfwGetTime() * 0.5f) * radius;

        //std::cout << camX << "x" << camY << "x" << camZ << std::endl;

        //mat4 view = fluxmath::lookAt(vec3(camPosX, camPosY, camPosZ), vec3(camTarPosX, 0.0f, camTarPosZ), vec3(0.0f, 1.0f, 0.0f)); //vec3(camPosX, camPosY, camPosZ) vec3(0.0f, 1.0f, 0.0f) vec3(-2.0f , 0.9f, 0.9f),

        mat4 view = fluxmath::lookAt(vec3(camX, camY, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

        //mat4 view = fluxmath::lookAt();

        mat4 projection = fluxmath::perspective(fluxmath::radians(FOV), (float)width/(float)height, 0.1f, 100.0f);;

        //mat4 view = camera.GetViewMatrix();
        //mat4 projection = camera.GetProjectionMatrix((float)width/(float)height);

        ourShader->setMat4("view", view);
        ourShader->setMat4("projection", projection);

        glBindVertexArray(VAO);

        if (currentMap) {
            for (auto& obj : currentMap->GetObjects()) {
                if (obj.texture) {
                    obj.bindTexture(0);
                } else {
                    texture.bindTexture(0);
                }
                mat4 model = obj.getModelMatrix();
                ourShader->setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        } else {
            texture.bindTexture(0);
            ourShader->setInt("ourTexture", 0);
            mat4 model;
            model = fluxmath::rotate(model, (float)glfwGetTime(), vec3(1.0f, 1.0f, 1.0f));
            ourShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        drawSpriteList();
        glfwSwapBuffers(window);
    }
}
void Window::close() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    delete ourShader;
    glfwDestroyWindow(window);
    glfwTerminate();
}
