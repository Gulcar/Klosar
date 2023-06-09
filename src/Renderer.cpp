#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Ostalo.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
    TexCoords = aTexCoords;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

void main()
{
    FragColor = vec4(TexCoords.xy, 0.1, 1.0);
}
)";

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

    glfwSetFramebufferSizeCallback(window, Renderer::OnWindowResize);
    Renderer::OnWindowResize(window, 1600, 900);

    UstvariBufferje();
    UstvariShader();
}

void Renderer::Unici()
{
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void Renderer::Draw(const Tekstura& tekstura, glm::vec2 pos, glm::vec2 velikost, float rot)
{
    static int modelLoc = glGetUniformLocation(shaderProgram, "model");
    static int viewLoc = glGetUniformLocation(shaderProgram, "view");
    static int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
    model = glm::scale(model, glm::vec3(velikost.x, velikost.y, 1.0f));
    model = glm::rotate(model, rot, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(-Kamera.x, -Kamera.y, 0.0f));

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projectionMat[0][0]);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Tekstura Renderer::NaloziTeksturo(const char* filename)
{
    return {};
}

void Renderer::NovFrame()
{
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::KonecFrama()
{
    glfwSwapBuffers(window);
}

bool Renderer::JeOknoOdprto()
{
    return glfwWindowShouldClose(window);
}

void Renderer::UstvariBufferje()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float vertices[] = {
        // vec2 pos,     vec2 texCoords
        -0.5f, -0.5f,    0.0f, 0.0f,
        0.5f, -0.5f,     1.0f, 0.0f,
        0.5f, 0.5f,      1.0f, 1.0f,
        -0.5f, 0.5f,     0.0f, 1.0f
    };

    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Renderer::UstvariShader()
{
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexShader);

    int ok;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        int logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetShaderInfoLog(vertexShader, logLength, 0, log);

        Error("ni uspelo narediti vertex shaderja:\n%s", log);
    }

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        int logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetShaderInfoLog(fragmentShader, logLength, 0, log);

        Error("ni uspelo narediti fragment shaderja:\n%s", log);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        int logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetProgramInfoLog(shaderProgram, logLength, 0, log);

        Error("ni uspelo narediti shader programa:\n%s", log);
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
}

void Renderer::OnWindowResize(struct GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    float razmerje = (float)width / (float)height;
    projectionMat = glm::ortho(-5.0f * razmerje, 5.0f * razmerje, -5.0f, 5.0f);
}
