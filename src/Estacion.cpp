#include "Estacion.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>
#include <Explosion.h>
#include <Nave.h>

using namespace sf;
using namespace std;

Estacion::Estacion(int estacion_x, int estacion_y, Nave* n)
{
    //ctor
    nave = n;
    balasNave = n->getBalas();
    bonificacion = 1500;
    explotada = false;
    borrar = false;
    centroSprite = 1;
    tiempoSprite = 0;
    puedoMorir = false;

    if (!texture.loadFromFile("resources/estacion.png"))
    {
        std::cerr << "Error cargando la imagen resources/estacion.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(2*130, 1*130, 256, 256));
    sprite.setPosition(estacion_x, estacion_y);

    spriteCentro.setTexture(texture);
    spriteCentro.setTextureRect(IntRect(1*44, 0*85+15*1, 44, 85));
    spriteCentro.setPosition(estacion_x+((44*5/2)-2), estacion_y+((85*2/2)+4));

    for(int cont = 0; cont < NUM_CANYONES; cont++)
    {
        canyones.push_back(new Canyon(estacion_x, estacion_y, nave, cont+1));
    }

    Vector2i* peq = new Vector2i();
    Vector2i* grnd = new Vector2i();
    peq->x = spriteCentro.getPosition().x+(44/2)-40;
    peq->y = spriteCentro.getPosition().y+(85/2)-40;
    grnd->x = spriteCentro.getPosition().x+(44/2)-70;
    grnd->y = spriteCentro.getPosition().y+(85/2)-70;
    explosion = new Explosion(peq, grnd);
}

Estacion::~Estacion()
{
    //dtor
}


void Estacion::update(sf::Time timeElapsed)
{
    RenderWindow *window = Bosconian::Instance()->getWindow();

    cambiarSpriteCentro();
    colisionEstacion(timeElapsed);
    updateCanyones(timeElapsed);
}

void Estacion::cambiarSpriteCentro()
{
    if(tiempoSprite == 0)
    {
        //std::cout << "Num centro " << centroSprite << std::endl;
        switch(centroSprite)
        {
            case 1:
            {
                spriteCentro.setTextureRect(IntRect(1*44, 0*85+15*1, 44, 85));
                break;
            }
            case 2:
            {
                spriteCentro.setTextureRect(IntRect(4*44, 0*85+15*1, 44, 85));
                break;
            }
            case 3:
            {
                spriteCentro.setTextureRect(IntRect(1*44, 1*85+15*4, 44, 85));
                break;
            }
            case 4:
            {
                spriteCentro.setTextureRect(IntRect(4*44-2, 1*85+15*4+10, 44, 85));
                break;
            }
            case 5:
            {
                spriteCentro.setTextureRect(IntRect(7*44-2, 0*85+15*1+5, 44, 85));
                break;
            }
            default:
            {
                //std::cout << "No hay mas sprites de centro" << std::endl;
                break;
            }
        }
        //Pongo los tiempos de cambio segun el sprite que este
        if(centroSprite < 5)
        {
            tiempoSprite = 20;
        } else
        {
            tiempoSprite = 100;
        }

        // Si estoy en rojo puede morir porque esta abierto
        if(centroSprite == 4 || centroSprite == 5)
        {
            puedoMorir = true;
        } else
        {
            puedoMorir = false;
        }

        // Actualizo al sprite siguiente
        if(centroSprite < 6)
        {
            centroSprite++;
        }
        // Vuelvo al primer sprite
        if(centroSprite == 6)
        {
            centroSprite = 1;
        }
    }
    if(tiempoSprite > 0)
    {
        tiempoSprite--;
    }

}

void Estacion::updateCanyones(sf::Time timeElapsed)
{
    View *viewJuego = Bosconian::Instance()->getViewJuego();
    int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

    int borrados = 0;
    if( !canyones.empty() && canyones.size() >=1 )
    {
        for (int cont = 0; cont < canyones.size(); cont++)
        {

            if((canyones.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (canyones.at(cont))->getSprite().getPosition().y < max_pos_y_view ||
                (canyones.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (canyones.at(cont))->getSprite().getPosition().x > min_pos_x_view )
            {
                (canyones.at(cont))->update(timeElapsed);
            }

            // Cuento los canyones que han explotado
            if( (canyones.at(cont))->getBorrar() )
            {
                //std::cout << "canyon muerto" << std::endl;
                borrados++;

            }
        }
        if(borrados == 6)
        {
            // Borro todos los canyones
            int num = 0;
            while( num <3 )
            {
                if( canyones.size() >=1 )
                {
                    for (int i = 0; i < canyones.size(); i++)
                    {
                        //std::cout << "borro canyon por explosion con nave" << std::endl;
                        delete(canyones.at(i));
                        canyones.erase(canyones.begin()+i);
                    }
                }
                num++;
            }
            nave->setScore(bonificacion);
            if( canyones.size() == 0 )
            {
                explotada = true; // no lo pongo hasta que no se borren todos los canyones
            }
        }
    }
}

void Estacion::colisionEstacion(sf::Time timeElapsed)
{
    //mostrarColision = true;
    //CUADRADO DE COLISION DE LA ESTACION
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width+26, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left-13, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::Cyan);

    //CUADRADO DE COLISION CON EL CENTRO DE LA ESTACION
    rectColisionCentro.setSize(Vector2f(spriteCentro.getGlobalBounds().width, spriteCentro.getGlobalBounds().height));
    rectColisionCentro.setPosition(spriteCentro.getGlobalBounds().left, spriteCentro.getGlobalBounds().top);
    rectColisionCentro.setFillColor(Color::White);

    //Colision con la Nave
    if( !canyones.empty() && canyones.size() >=1 )
    {
        for (int cont = 0; cont < canyones.size(); cont++)
        {
            if( nave->getSprite().getGlobalBounds().intersects((canyones.at(cont))->getSprite().getGlobalBounds()) && !explotada )
            {
                // Borro todos los canyones
                int num = 0;
                while( num <3 )
                {
                    if( canyones.size() >=1 )
                    {
                        for (int i = 0; i < canyones.size(); i++)
                        {
                            //std::cout << "borro canyon por explosion con nave" << std::endl;
                            delete(canyones.at(i));
                            canyones.erase(canyones.begin()+i);
                        }
                    }
                    num++;
                }
                nave->setVida(-1);
                nave->setScore(bonificacion);
                if( canyones.size() == 0 )
                {
                    explotada = true; // no lo pongo hasta que no se borren todos los canyones
                }
            }
        }
    }

    //Colision con las Balas de la Nave
    if(balasNave != nullptr && !balasNave->empty() && balasNave->size() >=1 )
    {
        for (int cont = 0; cont < balasNave->size(); cont++)
        {
            if((balasNave->at(cont))->getSprite().getGlobalBounds().intersects(spriteCentro.getGlobalBounds()) && puedoMorir && !explotada)
            {
                //std::cout << "Me disparan estacion centro!!! " << std::endl;
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

void Estacion::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if(mostrarColision)
    {
        window->draw(rectColision);
        window->draw(rectColisionCentro);
    }

    if(!explotada){
        window->draw(sprite);
        window->draw(spriteCentro);
    } else if(!explosion->getTermina() && explotada)
    {
        explosion->render(percentTick);
    }

    // Canyones
    View *viewJuego = Bosconian::Instance()->getViewJuego();
    int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));
    int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*4));

    if( !canyones.empty() )
    {
        for (int cont = 0; cont < canyones.size(); cont++)
        {
            if( ( (canyones.at(cont))->getSprite().getPosition().y > min_pos_y_view ||
                (canyones.at(cont))->getSprite().getPosition().y < max_pos_y_view ) &&
                ( (canyones.at(cont))->getSprite().getPosition().x < max_pos_x_view ||
                (canyones.at(cont))->getSprite().getPosition().x > min_pos_x_view ) )
            {
                (canyones.at(cont))->render(percentTick);
            }
        }
    }

}
