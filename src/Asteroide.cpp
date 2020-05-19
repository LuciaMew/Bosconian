#include "Asteroide.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>
#include <Nave.h>

using namespace sf;
using namespace std;

Asteroide::Asteroide(int asteroide_x, int asteroide_y, Nave* n)
{
    //ctor
    nave = n;
    balasNave = n->getBalas();
    bonificacion = 10;
    explotado = false;
    borrar = false;

    if (!texture.loadFromFile("resources/elementos.png"))
    {
        std::cerr << "Error cargando la imagen resources/elementos.png en Asteroide";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(1*66, 0*66, 67, 67));
    sprite.setPosition(asteroide_x, asteroide_y);

    Vector2i* peq = new Vector2i();
    Vector2i* grnd = new Vector2i();
    peq->x = sprite.getPosition().x-6;
    peq->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ+60;
    grnd->x = sprite.getPosition().x-40;
    grnd->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ+25;
    explosion = new Explosion(peq, grnd);
}

Asteroide::~Asteroide()
{
    //dtor
}

void Asteroide::update(sf::Time timeElapsed)
{
    RenderWindow *window = Bosconian::Instance()->getWindow();
    //mostrarColision = true;
    //CUADRADO DE COLISION DEL ASTEROIDE
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::Yellow);

    //Colision con la Nave
    if(nave->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado)
    {
        nave->setVida(-1);
        nave->setScore(bonificacion);
        explotado = true;
    }

    //Colision con las Balas de la Nave
    if(balasNave != nullptr && !balasNave->empty() && balasNave->size() >=1 )
    {
        for (int cont = 0; cont < balasNave->size(); cont++)
        {
            if((balasNave->at(cont))->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado)
            {
                //std::cout << "Me disparan asteroide!!! " << std::endl;
                nave->setScore(bonificacion);
                (balasNave->at(cont))->setBorrar(true);
                explotado = true;
            }
        }
    }

    if(!explosion->getTermina() && explotado)
    {
        explosion->update(timeElapsed);
    }
    else if(explosion->getTermina())
    {
        borrar = true;
    }

}

void Asteroide::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if(mostrarColision)
    {
        window->draw(rectColision);
    }

    if(!explotado){
        window->draw(sprite);
    } else if(!explosion->getTermina() && explotado)
    {
        explosion->render(percentTick);
    }

}
