#include "Bala.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>

using namespace sf;

Bala::Bala(Sprite *spriteNave, int direcBala)
{
    //ctor
    borrar = false;
    // direct bala es para que pongan un 1 si es la bala que va hacia abajo, y un -1 si es la que va hacia arriba

    movimiento = new Vector2i();
    movimiento->x = 0;
    movimiento->y = 0;

    if (!texture.loadFromFile("resources/bala.png"))
    {
        std::cerr << "Error cargando la imagen resources/bala en Bala.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0*66, 0*66, 67, 67));

    sNave = spriteNave;
    rectArma = (sNave->getTextureRect()); // rectArma es el IntRect actual de la nave para saber en que direccion va en ese momento

    // Cogo el sprite de bala que quiero segun la posicion de la nave y le digo hacia donde sera su movimiento
    if( (rectArma.left == 0*66 && rectArma.top == 1*66) || (rectArma.left == 0*66 && rectArma.top == 0*66) ) { // Up || Down
        sprite.scale(0.08,0.5);
        movimiento->y = 1;
    }
    if( (rectArma.left == 0*66 && rectArma.top == 2*66) || (rectArma.left == 1*66 && rectArma.top == 2*66) ) { // Right || Left
        sprite.scale(0.5,0.08);
        movimiento->x = 1;
    }
    if( (rectArma.left == 1*66 && rectArma.top == 1*66) || (rectArma.left == 2*66 && rectArma.top == 0*66) ) { // Right-Up || Left-Down
        sprite.scale(0.08,0.5);
        sprite.setRotation(45);
        movimiento->x = -1; //1 para varias lineas en setPos
        movimiento->y = 1;
    }
    if( (rectArma.left == 1*66 && rectArma.top == 0*66) || (rectArma.left == 2*66 && rectArma.top == 1*66) ) { // Right-Down || Left-Up
        sprite.scale(0.08,0.5);
        sprite.setRotation(-45);
        movimiento->x = -1;
        movimiento->y = -1;
    }

    //Para la velocidad, que no se ralentice la bala a la que me dirijo a su posicion
    if( (rectArma.left == 0*66 && rectArma.top == 1*66) || (rectArma.left == 1*66 && rectArma.top == 1*66) ||
        (rectArma.left == 1*66 && rectArma.top == 0*66) || (rectArma.left == 1*66 && rectArma.top == 2*66) ) { // Up || Right-Up || Right-Down || Left
        if(direcBala < 0) //bala hacia arriba
        {
            direcBala = (-1)*2;
        } else  //bala hacia abajo
        {
            direcBala = 1;
        }
    }
    if( (rectArma.left == 0*66 && rectArma.top == 2*66) || (rectArma.left == 0*66 && rectArma.top == 0*66) ||
        (rectArma.left == 2*66 && rectArma.top == 0*66) || (rectArma.left == 2*66 && rectArma.top == 1*66) ) { // Right || Down || Left-Down || Left-Up
        if(direcBala < 0) //bala hacia arriba
        {
            direcBala = (-1);
        } else  //bala hacia abajo
        {
            direcBala = 1*2;
        }
    }
    velocidad = 8.f*direcBala; // Para saber si es la que va para arriba o para abajo le multiplico un -1 o +1

    sprite.setPosition(sNave->getPosition().x+(Configuracion::TAMANYO_SPRITE_PEQ/2), sNave->getPosition().y-(Configuracion::TAMANYO_SPRITE_PEQ/2));

}

Bala::~Bala()
{
    //dtor
}

void Bala::update(sf::Time timeElapsed)
{
    // Up || Down || Right || Left || Right-Up || Left-Down || Right-Down || Left-Up
    //Movimiento de la bala
    sprite.setPosition( (sprite.getPosition().x)+(velocidad*movimiento->x), (sprite.getPosition().y)+(velocidad*movimiento->y));

    colisionBala(timeElapsed);

}

void Bala::colisionBala(sf::Time timeElapsed)
{
    //mostrarColision = true;
    //CUADRADO DE COLISION DE LA BALA
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::Red);

}

void Bala::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if(mostrarColision)
    {
        window->draw(rectColision);
    }

    window->draw(sprite);
}
