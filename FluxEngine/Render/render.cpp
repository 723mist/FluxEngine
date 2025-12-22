#include "../Window/window.hpp"
#include "../Objects/object.hpp"
#include "../Map/map.hpp"
#include "../Vector/vec.h"
#include "../Matrix/matrix.h"
#include "../Math/math.h"

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::Render() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader->use();

        const float radius = 3.0f;
        float camX = sin(glfwGetTime() * 0.5f) * radius;
        float camZ = cos(glfwGetTime() * 0.5f) * radius;

        mat4 view = fluxmath::lookAt(vec3(camX, 0.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

        mat4 projection = fluxmath::perspective(fluxmath::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);;

        ourShader->setMat4("view", view);
        ourShader->setMat4("projection", projection);

        glBindVertexArray(VAO);

        if (currentMap) {
            for (auto& obj : currentMap->GetObjects()) {
                if (obj.texture) {
                    obj.BindTexture(0);
                    ourShader->setInt("ourTexture", 0);
                }
                mat4 model = obj.GetModelMatrix();
                ourShader->setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        } else {
            texture.BindTexture(0);
            ourShader->setInt("ourTexture", 0);
            mat4 model;
            model = fluxmath::rotate(model, (float)glfwGetTime(), vec3(1.0f, 1.0f, 1.0f));
            ourShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
    }
}
void Window::Close() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    delete ourShader;
    glfwDestroyWindow(window);
    glfwTerminate();
}
