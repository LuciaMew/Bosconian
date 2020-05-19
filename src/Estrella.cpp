#include "Estrella.h"

#include <Bosconian.h>
#include <Configuracion.h>

Estrella::Estrella(int x, int y)
{
    //ctor
    if (!texture.loadFromFile("resources/elementos.png"))
    {
        std::cerr << "Error cargando la imagen resources/elementos.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setOrigin(1,1);
    sprite.setTextureRect(IntRect(0*66, 0*66, 67, 67));
    sprite.setPosition(x, y);
}

Estrella::~Estrella()
{
    //dtor
}

void Estrella::render()
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();
    window->draw(sprite);
}

void Estrella::cambiarposicion(int x, int y)
{
    sprite.setPosition(x, y);
    render();
}
