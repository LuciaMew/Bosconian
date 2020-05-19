#include "BalaCanyon.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>

using namespace sf;

BalaCanyon::BalaCanyon(Sprite *spriteCanyon, int direcBala, int numC)
{
    //ctor
    borrar = false;
    tiempoSprite = 10;
    // direct bala es un numero del 1 al 8 --> Up:1, Right-Up:2, Right:3, Right-Down:4, Down:5, Left-Down:6, Left:7, Left-Up:8

    movimiento = new Vector2i();
    movimiento->x = 0;
    movimiento->y = 0;

    if (!texture.loadFromFile("resources/bala.png"))
    {
        std::cerr << "Error cargando la imagen resources/bala en BalaCanyon.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0*66, 0*66, 67, 67));

    sCanyon = spriteCanyon;
    numCanyon = numC;
    // Cogo el sprite de bala que quiero segun el canyon que sea
    if( direcBala == 1 || direcBala == 5 ) // Up  || Down
    {
        sprite.scale(0.1,0.25);
        movimiento->y = 1;
    } else if( direcBala == 3 || direcBala == 7 ) // Right || Left
    {
        sprite.scale(0.25,0.1);
        movimiento->x = 1;
    } else if( (direcBala == 2 || direcBala == 6) && (numCanyon == 2 || numCanyon == 4 || numCanyon == 3 || numCanyon == 5) ) // Right-Up || Left-Down
    {
        sprite.scale(0.1,0.25);
        sprite.setRotation(45);
        movimiento->x = -1; //1 para varias lineas en setPos
        movimiento->y = 1;
    } else if( (direcBala == 4 || direcBala == 8) && (numCanyon == 4 || numCanyon == 6 || numCanyon == 1 || numCanyon == 3) ) // Right-Down || Left-Up
    {
        sprite.scale(0.1,0.25);
        sprite.setRotation(-45);
        movimiento->x = -1;
        movimiento->y = -1;
    } else {
        borrar = true;
    }

    // Pongo directBala a 1 para las que van hacia abajo y -1 para las que van hacia arriba, para que sepa hacia donde debe moverse
    if( direcBala == 1 && (numCanyon == 1 || numCanyon == 2 || numCanyon == 3 || numCanyon == 4) ) // Up
    {
        direcBala = -1;
    } else if( direcBala == 5 && (numCanyon == 3 || numCanyon == 4 || numCanyon == 5 || numCanyon == 6) ) // Down
    {
        direcBala = 1;
    } else if( direcBala == 3 && (numCanyon == 2 || numCanyon == 4 || numCanyon == 6) ) // Right
    {
        direcBala = 1;
    } else if( direcBala == 7 && (numCanyon == 1 || numCanyon == 3 || numCanyon == 5) ) // Left
    {
        direcBala = -1;
    } else if( direcBala == 2 && (numCanyon == 2 || numCanyon == 4) ) // Right-Up
    {
        direcBala = -1;
    } else if( direcBala == 6 && (numCanyon == 3 || numCanyon == 5) ) // Left-Down
    {
        direcBala = 1;
    } else if( direcBala == 4 && (numCanyon == 4 || numCanyon == 6) ) // Right-Down
    {
        direcBala = -1;
    } else if( direcBala == 8 && (numCanyon == 1 || numCanyon == 3) ) // Left-Up
    {
        direcBala = 1;
    } else {
        borrar = true;
    }

    velocidad = 1.5f*direcBala; // Para saber si es la que va para arriba o para abajo le multiplico un -1 o +1

    sprite.setPosition(sCanyon->getPosition().x+(Configuracion::TAMANYO_SPRITE_PEQ/2), sCanyon->getPosition().y+(Configuracion::TAMANYO_SPRITE_PEQ/2));

}

BalaCanyon::~BalaCanyon()
{
    //dtor
}

void BalaCanyon::update(sf::Time timeElapsed)
{
    //Movimiento de la bala de la estacion
    if(tiempoSprite == 0)
    {
        //std::cout << "Roto sprite bala" << centroSprite << std::endl;
        sprite.setRotation(sprite.getRotation()+45);
        tiempoSprite = 10;
    }
    if(tiempoSprite > 0)
    {
        tiempoSprite--;
    }
    // Up || Down || Right || Left || Right-Up || Left-Down || Right-Down || Left-Up
    sprite.setPosition( (sprite.getPosition().x)+(velocidad*movimiento->x), (sprite.getPosition().y)+(velocidad*movimiento->y));

    colisionBalaCanyon(timeElapsed);

}

void BalaCanyon::colisionBalaCanyon(sf::Time timeElapsed)
{
    //mostrarColision = true;
    //CUADRADO DE COLISION DE LA BALA
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::Red);

}

void BalaCanyon::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if(mostrarColision)
    {
        window->draw(rectColision);
    }

    window->draw(sprite);
}
