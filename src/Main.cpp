//Jakob Jeraj R2D Jakob je bil tukaj in je pisal v to datoteko.
//DANES SEM JEDEL SIR
//jakob je bil tretjic tukaj samo za test
//jaz pa denes nisem jedel sira

#include <iostream>
#include <glm/glm.hpp>
#include "Renderer.h"

int main()
{
    std::cout << "Pozdravljen svet!\n";

    float r = 0.0f;

    Renderer::Init();

    while (!Renderer::JeOknoOdprto())
    {
        r += 0.05f;

        Renderer::NovFrame();

        Renderer::Draw(Tekstura{}, { 0.0f, 0.0f }, { 5.0f, 5.0f }, r);

        Renderer::KonecFrama();
    }

    Renderer::Unici();
}
