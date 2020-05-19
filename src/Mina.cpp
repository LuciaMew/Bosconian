#include "Mina.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>
//#include <Explosion.h>
#include <Nave.h>

using namespace sf;
using namespace std;

Mina::Mina(int mina_x, int mina_y, Nave* n)
{
    //ctor
    nave = n;
    balasNave = n->getBalas();
    bonificacion = 20;
    explotada = false;
    borrar = false;

    if (!texture.loadFromFile("resources/elementos.png"))
    {
        std::cerr << "Error cargando la imagen resources/elementos.png en Mina";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0*66, 1*66, 67, 67));
    sprite.setPosition(mina_x, mina_y);

    Vector2i* peq = new Vector2i();
    Vector2i* grnd = new Vector2i();
    peq->x = sprite.getPosition().x-6;
    peq->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ+60;
    grnd->x = sprite.getPosition().x-40;
    grnd->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ+25;
    explosion = new Explosion(peq, grnd);
}

Mina::~Mina()
{
    //dtor
}

void Mina::update(sf::Time timeElapsed)
{
    RenderWindow *window = Bosconian::Instance()->getWindow();
    //mostrarColision = true;
    //CUADRADO DE COLISION DE LA MINA
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::Yellow);

    //Colision con la Nave
    if(nave->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotada)
    {
        nave->setVida(-1);
        nave->setScore(bonificacion);
        explotada = true;
    }
    //Colision con las Balas de la Nave
    if(balasNave != nullptr && !balasNave->empty() && balasNave->size() >=1 )
    {
        for (int cont = 0; cont < balasNave->size(); cont++)
        {
            if((balasNave->at(cont))->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotada)
            {
                //std::cout << "Me disparan mina!!! " << std::endl;
                nave->setScore(bonificacion);
                (balasNave->at(cont))->setBorrar(true);
                explotada = true;
            }
        }
    }

    if(!explosion->getTermina() && explotada)
    {
        explosion->update(timeElapsed);
    }
    else if(explosion->getTermina())
    {
        borrar = true;
    }

}

void Mina::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if(mostrarColision)
    {
        window->draw(rectColision);
    }

    if(!explotada){
        window->draw(sprite);
    } else if(!explosion->getTermina() && explotada)
    {
        explosion->render(percentTick);
    }

}
