//Jakob Jeraj R2D Jakob je bil tukaj in je pisal v to datoteko.
//DANES SEM JEDEL SIR
//jakob je bil tretjic tukaj samo za test
//jaz pa denes nisem jedel sira

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Renderer.h"

int main()
{
    std::cout << "Pozdravljen svet!\n";

    Renderer::Init();

    while (!Renderer::JeOdprto())
    {
        Renderer::NovFrame();

        Renderer::KonecFrama();
    }

    Renderer::Unici();
}
