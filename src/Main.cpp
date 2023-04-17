//Jakob Jeraj R2D Jakob je bil tukaj in je pisal v to datoteko.
//DANES SEM JEDEL SIR
//jakob je bil tretjic tukaj samo za test
//jaz pa denes nisem jedel sira

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

int main()
{
    std::cout << "Pozdravljen svet!\n";

    glfwInit();

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glm::vec3 a;
    a.x = 5;
    std::cout << a.x;
}
