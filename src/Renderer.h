#pragma once

#include <glm/vec2.hpp>

struct Tekstura
{
    uint32_t id; // id za opengl
    int sirina, visina; // velikost v pixlih
};

class Renderer
{
public:
    // inicializiraj opengl in glfw
    static void Init();
    // klice glfwTerminate
    static void Unici();

    static void Draw(Tekstura& tekstura, glm::vec2 pos, glm::vec2 velikost, float rot = 0.0f);
    static Tekstura NaloziTeksturo(const char* filename);

    // klice glClear in glfwPollEvent
    static void NovFrame();
    // klice glfwSwapBuffers
    static void KonecFrama();

    // vrne glfwWindowShouldClose
    static bool JeOdprto();

private:
    static inline struct GLFWwindow* window;
};

