#include "Enemigo.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>
#include <Nave.h>
#include <Bala.h>

using namespace sf;
using namespace std;

Enemigo::Enemigo(int enemigo_x, int enemigo_y, Nave* n, vector<Mina *> *m, vector<Asteroide *> *a)
{
    //ctor
    velocidad = 4.3f;
    muerto = false;
    explotado = false;
    tiempoMovimiento = 0;
    dirActual = 1;
    nave = n;
    minas = m;
    asteroides = a;
    balasNave = n->getBalas();


    bonificacion = 0;
    explosion = nullptr;
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::update(sf::Time timeElapsed)
{
    RenderWindow *window = Bosconian::Instance()->getWindow();

    if(!explotado)
    {
        moverEnemigo(timeElapsed);
    }

    // Comprobaciones de cuando muero y exploto
    colisionEnemigo(timeElapsed);
}

void Enemigo::moverEnemigo(sf::Time timeElapsed)
{
    //Cambio a una direccion aleatoria cada cierto tiempo aleatorio
    if(tiempoMovimiento == 0)
    {
        dirActual = rand() % 8+1; // rango de 1 a 8
        //std::cout << "Cambio direccion " << dirActual << std::endl;
        switch(dirActual)
        {
            case 1: // Up
            {
                sprite.setTextureRect(IntRect(1*66, 1*66, 67, 67));
                break;
            }
            case 2: // Down
            {
                sprite.setTextureRect(IntRect(0*66, 0*66, 67, 67));
                break;
            }
            case 3: // Right
            {
                sprite.setTextureRect(IntRect(0*66, 2*66, 67, 67));
                break;
            }
            case 4: // Left
            {
                sprite.setTextureRect(IntRect(1*66, 2*66, 67, 67));
                break;
            }
            case 5: // Up-Right
            {
                sprite.setTextureRect(IntRect(2*66, 0*66, 67, 67));
                break;
            }
            case 6: // Up-Left
            {
                sprite.setTextureRect(IntRect(2*66, 1*66, 67, 67));
                break;
            }
            case 7: // Down-Right
            {
                sprite.setTextureRect(IntRect(1*66, 0*66, 67, 67));
                break;
            }
            case 8: // Down-Left
            {
                sprite.setTextureRect(IntRect(0*66, 1*66, 67, 67));
                break;
            }
            default:
            {
                std::cout << "Este cambio de direccion no existe en enemigo" << std::endl;
                break;
            }
        }
        tiempoMovimiento = rand() % 100+30; // rango de 30 a 300
        //std::cout << "Tiempo mov " << tiempoMovimiento << std::endl;
    }
    if(tiempoMovimiento > 0)
    {
        tiempoMovimiento--;
    }


    //Muevo según a la direccion que este
    //std::cout << "Tengo direccion " << dirActual << std::endl;
    switch(dirActual)
    {
        case 1: // Up
        {
            if(sprite.getPosition().y > Configuracion::MIN_POS_Y)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y-velocidad));
            } else
            {
                //std::cout << "INFINITO UP" << std::endl;
                sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MAX_POS_Y));
            }
            break;
        }
        case 2: // Down
        {
            if(sprite.getPosition().y < Configuracion::MAX_POS_Y)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y+velocidad));
            } else
            {
                //std::cout << "INFINITO DOWN" << std::endl;
                sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MIN_POS_Y));
            }
            break;
        }
        case 3: // Right
        {
            if(sprite.getPosition().x < Configuracion::MAX_POS_X)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x+velocidad, sprite.getPosition().y));
            } else
            {
                //std::cout << "INFINITO RIGHT" << std::endl;
                sprite.setPosition(Vector2f(Configuracion::MIN_POS_X, sprite.getPosition().y));
            }
            break;
        }
        case 4: // Left
        {
            if(sprite.getPosition().x > Configuracion::MIN_POS_X)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x-velocidad, sprite.getPosition().y));
            } else
            {
                //std::cout << "INFINITO LEFT" << std::endl;
                sprite.setPosition(Vector2f(Configuracion::MAX_POS_X, sprite.getPosition().y));
            }
            break;
        }
        case 5: // Up-Right
        {
            if(sprite.getPosition().x < Configuracion::MAX_POS_X)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x+velocidad, sprite.getPosition().y));
            } else
            {
                //std::cout << "INFINITO RIGHT-UP right" << std::endl;
                sprite.setPosition(Vector2f(Configuracion::MIN_POS_X, sprite.getPosition().y));
            }

            if(sprite.getPosition().y > Configuracion::MIN_POS_Y)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y-velocidad));
            } else
            {
                //std::cout << "INFINITO RIGHT-UP up" << std::endl;
                sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MAX_POS_Y));
            }
            break;
        }
        case 6: // Up-Left
        {
            if(sprite.getPosition().x > Configuracion::MIN_POS_X)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x-velocidad, sprite.getPosition().y));
            } else
            {
                //std::cout << "INFINITO LEFT-UP left" << std::endl;
                sprite.setPosition(Vector2f(Configuracion::MAX_POS_X, sprite.getPosition().y));
            }
            if(sprite.getPosition().y > Configuracion::MIN_POS_Y)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y-velocidad));
            } else
            {
                //std::cout << "INFINITO LEFT-UP up" << std::endl;
                sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MAX_POS_Y));
            }
            break;
        }
        case 7: // Down-Right
        {
            if(sprite.getPosition().x < Configuracion::MAX_POS_X)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x+velocidad, sprite.getPosition().y));
            } else
            {
                //std::cout << "INFINITO RIGHT-DOWN right" << std::endl;
                sprite.setPosition(Vector2f(Configuracion::MIN_POS_X, sprite.getPosition().y));
            }
            if(sprite.getPosition().y < Configuracion::MAX_POS_Y)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y+velocidad));
            } else
            {
                //std::cout << "INFINITO RIGHT-DOWN down" << std::endl;
                sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MIN_POS_Y));
            }
            break;
        }
        case 8: // Down-Left
        {
            if(sprite.getPosition().x > Configuracion::MIN_POS_X)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x-velocidad, sprite.getPosition().y));
            } else
            {
                //std::cout << "INFINITO LEFT-DOWN left" << std::endl;
                sprite.setPosition(Vector2f(Configuracion::MAX_POS_X, sprite.getPosition().y));
            }
            if(sprite.getPosition().y < Configuracion::MAX_POS_Y)
            {
                sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y+velocidad));
            } else
            {
                //std::cout << "INFINITO LEFT-DOWN down" << std::endl;
                sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MIN_POS_Y));
            }
            break;
        }
        default:
        {
            std::cout << "Esta direccion no existe en enemigo" << std::endl;
            break;
        }
    }

}

void Enemigo::colisionEnemigo(sf::Time timeElapsed)
{
    //mostrarColision = true;
    //CUADRADO DE COLISION DEL ENEMIGO
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::Green);

    // Si se ve en la vista actual puede explotar contra la nave, un asteroide o una mina
    if( nave->getRectInicial().getGlobalBounds().intersects(sprite.getGlobalBounds()) )
    {
        // Nave
        if(nave->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado)
        {
            //std::cout << "Choco!!! " << std::endl;
            nave->setVida(-1);
            nave->setScore(bonificacion);
            explotado = true;
        }

        //Balas de la nave
        if(balasNave != nullptr && !balasNave->empty() && balasNave->size() >=1 )
        {
            for (int cont = 0; cont < balasNave->size(); cont++)
            {
                if((balasNave->at(cont))->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado)
                {
                    //std::cout << "Me disparan enemigo!!! " << std::endl;
                    nave->setScore(bonificacion);
                    (balasNave->at(cont))->setBorrar(true);
                    explotado = true;
                }
            }
        }

        // Minas
        if(minas != nullptr && !minas->empty() && minas->size() >=1 )
        {
            for (int cont = 0; cont < minas->size(); cont++)
            {
                if((minas->at(cont))->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado )
                {
                    explotado = true;
                    (minas->at(cont))->setExplotada(true);
                }
            }
        }

        // Asteroides
        if(asteroides != nullptr && !asteroides->empty() && asteroides->size() >=1 )
        {
            for (int cont = 0; cont < asteroides->size(); cont++)
            {
                if((asteroides->at(cont))->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado )
                {
                    explotado = true;
                    (asteroides->at(cont))->setExplotado(true);
                }
            }
        }
    }

    //Explosion
    if(!explosion->getTermina() && explotado)
    {
        Vector2i* peq = new Vector2i();
        Vector2i* grnd = new Vector2i();
        peq->x = sprite.getPosition().x-8;
        peq->y = sprite.getPosition().y-8;
        grnd->x = sprite.getPosition().x-Configuracion::TAMANYO_SPRITE_PEQ/2;
        grnd->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ/2;
        explosion->setPosicion(peq, grnd);
        explosion->update(timeElapsed);
    }
    else if(explosion->getTermina())
    {
        muerto = true;
    }
}

void Enemigo::render(double percentTick)
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
