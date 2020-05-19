#include "Explosion.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>

using namespace sf;
using namespace std;

Explosion::Explosion(Vector2i* peq, Vector2i* grnd)
{
    //ctor
    pequenyo = new Vector2i();
    grande = new Vector2i();
    pequenyo->x = peq->x;
    pequenyo->y = peq->y;
    grande->x = grnd->x;
    grande->y = grnd->y;

    tiempoSprite = 0;
    numExplosion = 0;
    termina = false;

    if (!texture.loadFromFile("resources/explosion.png"))
    {
        std::cerr << "Error cargando la imagen resources/explosion.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0*83, 0*83, 83, 83));
    sprite.setPosition(pequenyo->x, pequenyo->y);
}

Explosion::~Explosion()
{
    //dtor
}

void Explosion::setPosicion(Vector2i* peq, Vector2i* grnd)
{
    pequenyo->x = peq->x;
    pequenyo->y = peq->y;
    grande->x = grnd->x;
    grande->y = grnd->y;
}

void Explosion::update(sf::Time timeElapsed)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    cambiarSprite();
}

void Explosion::cambiarSprite()
{
    if(tiempoSprite == 0)
    {
        //std::cout << "Num explosion " << numExplosion << std::endl;
        switch(numExplosion)
        {
            case 0:
            {
                sprite.setTextureRect(IntRect(0*83, 0*83, 83, 83));
                sprite.setPosition(pequenyo->x, pequenyo->y);
                break;
            }
            case 1:
            {
                sprite.setTextureRect(IntRect(1*83, 0*83, 83, 83));
                sprite.setPosition(pequenyo->x, pequenyo->y);
                break;
            }
            case 2:
            {
                sprite.setTextureRect(IntRect(2*83, 0*83, 152, 152));
                sprite.setPosition(grande->x, grande->y);
                break;
            }
            case 3:
            {
                sprite.setTextureRect(IntRect(0*83, 1*83, 152, 152));
                sprite.setPosition(grande->x, grande->y);
                break;
            }
            case 4:
            {
                sprite.setTextureRect(IntRect(2*83+152, 0*83, 83, 83));
                sprite.setPosition(pequenyo->x, pequenyo->y);
                break;
            }
            case 5:
            {
                sprite.setTextureRect(IntRect(2*83+152, 1*83, 83, 83));
                sprite.setPosition(pequenyo->x, pequenyo->y);
                break;
            }
            default:
            {
                //std::cout << "No hay mas sprites de explosion" << std::endl;
                termina = true;
                break;
            }
        }
        tiempoSprite = 10;
        if(numExplosion < 6)
        {
            numExplosion++;
        }
    }
    if(tiempoSprite > 0)
    {
        tiempoSprite--;
    }

}

void Explosion::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    window->draw(sprite);

}
