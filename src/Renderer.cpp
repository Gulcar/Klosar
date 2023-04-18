#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Ostalo.h"
#include <cmath>

void Renderer::Init()
{
    if (!glfwInit())
        Error("ni uspelo inicializirati glfw!");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1600, 900, "Klošar", 0, 0);
    if (window == nullptr) Error("ni uspelo narediti glfw okna!");

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, 1600, 900);
}

void Renderer::Unici()
{
    glfwTerminate();
}

void Renderer::Draw(Tekstura& tekstura, glm::vec2 pos, glm::vec2 velikost, float rot)
{

}

Tekstura Renderer::NaloziTeksturo(const char* filename)
{
    return {};
}

void Renderer::NovFrame()
{
    glfwPollEvents();

    glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::KonecFrama()
{
    glfwSwapBuffers(window);
}

bool Renderer::JeOdprto()
{
    return glfwWindowShouldClose(window);
}

