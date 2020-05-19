#include "Canyon.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>
#include <Explosion.h>
#include <BalaCanyon.h>
#include <Nave.h>

using namespace sf;
using namespace std;

Canyon::Canyon(int canyon_x, int canyon_y, Nave* n, int tipo_c)
{
    //ctor
    nave = n;
    balasNave = n->getBalas();
    tipoCanyon = tipo_c;
    bonificacion = 200;
    explotado = false;
    borrar = false;
    tiempoDisp = 0;

    if (!texture.loadFromFile("resources/canyon.png"))
    {
        std::cerr << "Error cargando la imagen resources/canyon.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0*66, 0*66, 67, 67));

    switch(tipoCanyon)
    {
        case 1:
        {
            sprite.setPosition(canyon_x+((67/2)+14), canyon_y+6);
            break;
        }
        case 2:
        {
            sprite.setPosition(canyon_x+((67/2)+14*8), canyon_y+6);
            break;
        }
        case 3:
        {
            sprite.setPosition(canyon_x+((67/2)-40), canyon_y+((67/2)+62));
            break;
        }
        case 4:
        {
            sprite.setPosition(canyon_x+((67/2)+42*4), canyon_y+((67/2)+64));
            break;
        }
        case 5:
        {
            sprite.setPosition(canyon_x+((67/2)+14), canyon_y+((67/2)+76*2));
            break;
        }
        case 6:
        {
            sprite.setPosition(canyon_x+((67/2)+14*8), canyon_y+((67/2)+76*2));
            break;
        }
        default:
        {
            std::cout << "Este tipo de canyon no existe posicion" << std::endl;
            break;
        }
    }

    Vector2i* peq = new Vector2i();
    Vector2i* grnd = new Vector2i();
    peq->x = sprite.getPosition().x+(67/2)-40;
    peq->y = sprite.getPosition().y+(67/2)-40;
    grnd->x = sprite.getPosition().x+(67/2)-70;
    grnd->y = sprite.getPosition().y+(67/2)-70;
    explosion = new Explosion(peq, grnd);
}

Canyon::~Canyon()
{
    //dtor
}

void Canyon::update(sf::Time timeElapsed)
{
    RenderWindow *window = Bosconian::Instance()->getWindow();

    colisionCanyon(timeElapsed);
    updateBalas(timeElapsed);
}

void Canyon::colisionCanyon(sf::Time timeElapsed)
{
    //mostrarColision = true;
    //CUADRADO DE COLISION DEL CANYON
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::White);

    //SI CHOCA CON UN CANYON EXPLOTA LA ESTACION ENTERA
    /*
    //Colision con la Nave
    if(nave->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado)
    {
        nave->setVida(-1);
        nave->setScore(bonificacion);
        explotado = true;
    }
    */

    //Colision con las Balas de la Nave
    if(balasNave != nullptr && !balasNave->empty() && balasNave->size() >=1 )
    {
        for (int cont = 0; cont < balasNave->size(); cont++)
        {
            if((balasNave->at(cont))->getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()) && !explotado)
            {
                //std::cout << "Me disparan estacion centro!!! " << std::endl;
                nave->setScore(bonificacion);
                (balasNave->at(cont))->setBorrar(true);
                if(!borrar)
                {
                    explotado = true;
                }
            }
        }
    }

    //Colision Nave con las Balas del Canyon
    if(!balas.empty() && balas.size() >=1 )
    {
        for (int cont = 0; cont < balas.size(); cont++)
        {
            if((balas.at(cont))->getSprite().getGlobalBounds().intersects(nave->getSprite().getGlobalBounds()) && !borrar )
            {
                nave->setVida(-1);
                (balas.at(cont))->setBorrar(true);
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
        bonificacion = 0;
        explotado = false;
        // switch(tipoCanyon) para poner el sprite EXPLOTADO que toque
        switch(tipoCanyon)
        {
            case 1:
            {
                sprite.setTextureRect(IntRect(0*66, 1*66, 67, 67));
                break;
            }
            case 2:
            {
                sprite.setTextureRect(IntRect(0*66, 1*66, 67, 67));
                break;
            }
            case 3:
            {
                sprite.setTextureRect(IntRect(1*66, 1*66, 67, 67));
                break;
            }
            case 4:
            {
                sprite.setTextureRect(IntRect(1*66, 0*66, 67, 67));
                break;
            }
            case 5:
            {
                sprite.setTextureRect(IntRect(2*66, 0*66, 67, 67));
                break;
            }
            case 6:
            {
                sprite.setTextureRect(IntRect(2*66, 0*66, 67, 67));
                break;
            }
            default:
            {
                std::cout << "Este tipo de canyon no existe sprite" << std::endl;
                break;
            }
        }
    }

}

void Canyon::updateBalas(sf::Time timeElapsed)
{
    // Si no he explotado ya, puedo disparar
    if(!borrar)
    {
        //std::cout << tiempoDisp << std::endl;
        if( tiempoDisp == 0 )
        {
            //std::cout << "2 nueva bala estacion" << std::endl;
            balas.push_back(new BalaCanyon((&sprite), rand() % 8+1, tipoCanyon));
            tiempoDisp = rand() % 150+50;// rango de 50 a 150
        }
        if(tiempoDisp > 0)
        {
            tiempoDisp--;
        }
    }

    //Si quedan balas
    if(!balas.empty())
    {
        //Llamo al update de cada bala
        View *viewJuego = Bosconian::Instance()->getViewJuego();
        int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*1));
        int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*1));
        int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*1));
        int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*1));
        for (int cont = 0; cont < balas.size(); cont++)
        {

            if((balas.at(cont))->getSprite().getPosition().y > Configuracion::MIN_POS_Y ||
                (balas.at(cont))->getSprite().getPosition().y < Configuracion::MAX_POS_Y ||
                (balas.at(cont))->getSprite().getPosition().x < Configuracion::MAX_POS_X ||
                (balas.at(cont))->getSprite().getPosition().x > Configuracion::MIN_POS_X)
            {
                //std::cout << "UPDATE bala canyon" << std::endl;
                (balas.at(cont))->update(timeElapsed);
            }

            //Borro las balas que han chocado con la nave o las que ese canyon no puede disparar en esas direcciones
            if( (balas.at(cont))->getBorrar() )
            {
                //std::cout << "borro bala de canyon que choca o direccion erronea" << std::endl;
                delete(balas.at(cont));
                balas.erase(balas.begin()+cont);
            }
            // Borro las balas cuando estan a una distancia de 1 sprite pequenyo fuera de la vista
            else if((balas.at(cont))->getSprite().getPosition().y < min_pos_y_view ||
                (balas.at(cont))->getSprite().getPosition().y > max_pos_y_view ||
                (balas.at(cont))->getSprite().getPosition().x > max_pos_x_view ||
                (balas.at(cont))->getSprite().getPosition().x < min_pos_x_view )
            {
                //std::cout << "borro bala lejena de canyon" << std::endl;
                delete(balas.at(cont));
                balas.erase(balas.begin()+cont);
            }
        }
    }

}

void Canyon::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if(mostrarColision)
    {
        window->draw(rectColision);
    }

    //Si quedan balas
    if(!balas.empty())
    {
        for (int cont = 0; cont < balas.size(); cont++)
        {
            //std::cout << "disparoo canyon!!" << std::endl;
            (balas.at(cont))->render(percentTick);
        }
    }

    if(!explotado){
        window->draw(sprite);
    } else if(!explosion->getTermina() && explotado)
    {
        explosion->render(percentTick);
    }

}

