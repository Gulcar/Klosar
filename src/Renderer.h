#pragma once

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

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

    static void Draw(const Tekstura& tekstura, glm::vec2 pos, glm::vec2 velikost, float rot = 0.0f);
    static Tekstura NaloziTeksturo(const char* filename);

    // klice glClear in glfwPollEvent
    static void NovFrame();
    // klice glfwSwapBuffers
    static void KonecFrama();

    // vrne glfwWindowShouldClose
    static bool JeOknoOdprto();

public:
    static inline glm::vec2 Kamera = { 0.0f, 0.0f };

private:
    static void UstvariBufferje();
    static void UstvariShader();
    static void OnWindowResize(struct GLFWwindow* window, int width, int height);

private:
    static inline struct GLFWwindow* window = nullptr;

    static inline uint32_t vao;
    static inline uint32_t vbo;
    static inline uint32_t ebo;

    static inline uint32_t shaderProgram;

    static inline glm::mat4 projectionMat;
};

