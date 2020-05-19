#include "Nave.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Configuracion.h>
#include <Bosconian.h>
#include <Bala.h>

using namespace sf;
using namespace std;

Nave::Nave()
{
    //ctor
    score = scoreAntes = sumaScoreAntes = 0;
    muerto = false;
    vida = vidaAntes = 3;

    velocidad = 4.f;

    if (!texture.loadFromFile("resources/nave.png"))
    {
        std::cerr << "Error cargando la imagen resources/nave.png";
        exit(0);
    }
    sprite.setTexture(texture);
    sprite.setOrigin(1,67);
    sprite.setTextureRect(IntRect(0*66, 1*66, 67, 67)); //Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight)
    //sprite.scale(1.5,1.5);
    sprite.setPosition(Configuracion::TAMANYO_MAPA_X/2, Configuracion::TAMANYO_PANTALLA_Y*5);

    //balas = new std::vector<Bala *>;
    tiempoDisp = 0;

    Vector2i* peq = new Vector2i();
    Vector2i* grnd = new Vector2i();
    peq->x = sprite.getPosition().x-8;
    peq->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ-6;
    grnd->x = sprite.getPosition().x-40;
    grnd->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ-40;
    explosion = new Explosion(peq, grnd);

}

Nave::~Nave()
{
    //dtor
}

void Nave::setVida(int salud)
{
    if( !Bosconian::Instance()->getModoDios() )
    {
        vida+=salud;
    }
}

void Nave::restartNave()
{
    if(!balas.empty())
    {
        for (int cont = 0; cont < balas.size(); cont++)
        {
            //std::cout << "borro bala --> todas" << std::endl;
            delete(balas.at(cont));
            balas.erase(balas.begin()+cont);

        }
    }
    muerto = false;
    //vidaAntes = vida;
    sprite.setOrigin(1,67);
    sprite.setTextureRect(IntRect(0*66, 1*66, 67, 67));
    sprite.setPosition(Configuracion::TAMANYO_MAPA_X/2, Configuracion::TAMANYO_PANTALLA_Y*5);
    tiempoDisp = 0;

    Vector2i* peq = new Vector2i();
    Vector2i* grnd = new Vector2i();
    peq->x = sprite.getPosition().x-8;
    peq->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ-6;
    grnd->x = sprite.getPosition().x-40;
    grnd->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ-40;
    explosion = new Explosion(peq, grnd);
}

void Nave::update(sf::Time timeElapsed)
{
    RenderWindow *window = Bosconian::Instance()->getWindow();

    colisionNave(timeElapsed);
    if(!muerto)
    {
        moverNave(timeElapsed);
    }
    updateBalas(timeElapsed);

    // Comprobaciones de cuando muero y exploto
    //std::cout << "Vidas " << vida << std::endl;
    //std::cout << "Vida antes " << vidaAntes << std::endl;
    if(vida != vidaAntes){
        //std::cout << "Me quito vida" << std::endl;
        //std::cout << "Vidas " << vida << std::endl;
        //std::cout << "Vida antes " << vidaAntes << std::endl;
        vidaAntes = vida;
        muerto = true;
        //std::cout << "Vida ahora " << vida << "  " << vidaAntes << std::endl;
    }
    if(!explosion->getTermina() && muerto)
    {
        Vector2i* peq = new Vector2i();
        Vector2i* grnd = new Vector2i();
        peq->x = sprite.getPosition().x-8;
        peq->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ-6;
        grnd->x = sprite.getPosition().x-40;
        grnd->y = sprite.getPosition().y-Configuracion::TAMANYO_SPRITE_PEQ-40;
        explosion->setPosicion(peq, grnd);
        explosion->update(timeElapsed);
    } else if(explosion->getTermina())
    {
        muerto = false;
        restartNave();
    }

    /*
    // Process events
    Event event;
    //input(window, event);
    while (window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                window->close();
                break;
            case Event::KeyReleased:
            {
                //std::cout << "Se soltó una tecla" << std::endl;
                if(event.key.code == Keyboard::Escape) {
                    window->close();
                }
                /*if(event.key.code == Keyboard::G) {
                    std::cout << "Modo Dios activado" << std::endl;
                    modoDios = true;
                }*
                break;
            }
        }
    }
    */

}

void Nave::moverNave(sf::Time timeElapsed)
{
    //Cambio sprite segun las teclas que presione
    if (Keyboard::isKeyPressed(sf::Keyboard::Up) && !Keyboard::isKeyPressed(sf::Keyboard::Down) ) { //Up !Down
        //std::cout << "sprite hacia arriba" << std::endl;
        sprite.setTextureRect(IntRect(0*66, 1*66, 67, 67));
    } else if (Keyboard::isKeyPressed(sf::Keyboard::Down) && !Keyboard::isKeyPressed(sf::Keyboard::Up) ) { // Down !Up
        //std::cout << "sprite hacia abajo" << std::endl;
        sprite.setTextureRect(IntRect(0*66, 0*66, 67, 67));
    }

    if (Keyboard::isKeyPressed(sf::Keyboard::Right) && !Keyboard::isKeyPressed(sf::Keyboard::Left) ) { // Right !Left
        if(Keyboard::isKeyPressed(sf::Keyboard::Up) && !Keyboard::isKeyPressed(sf::Keyboard::Down) ) // Right !Left && Up !Down
        {
            //std::cout << "sprite derecha-arriba" << std::endl;
            sprite.setTextureRect(IntRect(1*66, 1*66, 67, 67));
        } else if(Keyboard::isKeyPressed(sf::Keyboard::Down) && !Keyboard::isKeyPressed(sf::Keyboard::Up) ) // Right !Left && Down !Up
        {
            //std::cout << "sprite derecha-abajo" << std::endl;
            sprite.setTextureRect(IntRect(1*66, 0*66, 67, 67));
        } else{
            //std::cout << "sprite derecha" << std::endl;
            sprite.setTextureRect(IntRect(0*66, 2*66, 67, 67));
        }
    } else if (Keyboard::isKeyPressed(sf::Keyboard::Left) && !Keyboard::isKeyPressed(sf::Keyboard::Right) ) { // Left !Right
        if(Keyboard::isKeyPressed(sf::Keyboard::Up) && !Keyboard::isKeyPressed(sf::Keyboard::Down) ) // Left !Right && Up !Down
        {
            //std::cout << "sprite izquierda-arriba" << std::endl;
            sprite.setTextureRect(IntRect(2*66, 1*66, 67, 67));
        } else if(Keyboard::isKeyPressed(sf::Keyboard::Down) && !Keyboard::isKeyPressed(sf::Keyboard::Up) ) // Left !Right && Down !Up
        {
            //std::cout << "sprite izquierda-abajo" << std::endl;
            sprite.setTextureRect(IntRect(2*66, 0*66, 67, 67));
        } else{
            //std::cout << "sprite izquierda" << std::endl;
            sprite.setTextureRect(IntRect(1*66, 2*66, 67, 67));
        }
    }

    //Me muevo hacia la ultima direccion que ha pulsado
    IntRect rectNave = sprite.getTextureRect();
    if( (rectNave.left == 0*66 && rectNave.top == 1*66) && !(rectNave.left == 0*66 && rectNave.top == 0*66) ) { // Up !Down
        if(sprite.getPosition().y > Configuracion::MIN_POS_Y)
        {
            sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y-velocidad));
        } else
        {
            //std::cout << "INFINITO UP" << std::endl;
            sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MAX_POS_Y));
        }
    } else if( (rectNave.left == 0*66 && rectNave.top == 0*66) && !(rectNave.left == 0*66 && rectNave.top == 1*66) ) { // Down !Up
        if(sprite.getPosition().y < Configuracion::MAX_POS_Y)
        {
            sprite.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y+velocidad));
        } else
        {
            //std::cout << "INFINITO DOWN" << std::endl;
            sprite.setPosition(Vector2f(sprite.getPosition().x, Configuracion::MIN_POS_Y));
        }
    }

    if( (rectNave.left == 0*66 && rectNave.top == 2*66) && !(rectNave.left == 1*66 && rectNave.top == 2*66) ) { // Right  !Left
        if(sprite.getPosition().x < Configuracion::MAX_POS_X)
        {
            sprite.setPosition(Vector2f(sprite.getPosition().x+velocidad, sprite.getPosition().y));
        } else
        {
            //std::cout << "INFINITO RIGHT" << std::endl;
            sprite.setPosition(Vector2f(Configuracion::MIN_POS_X, sprite.getPosition().y));
        }
    } else if( (rectNave.left == 1*66 && rectNave.top == 2*66) && !(rectNave.left == 0*66 && rectNave.top == 2*66) ) { // Left !Right
        if(sprite.getPosition().x > Configuracion::MIN_POS_X)
        {
            sprite.setPosition(Vector2f(sprite.getPosition().x-velocidad, sprite.getPosition().y));
        } else
        {
            //std::cout << "INFINITO LEFT" << std::endl;
            sprite.setPosition(Vector2f(Configuracion::MAX_POS_X, sprite.getPosition().y));
        }
    }

    if( (rectNave.left == 1*66 && rectNave.top == 1*66) && !(rectNave.left == 2*66 && rectNave.top == 0*66) ) { // Right-Up !Left-Down
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
    } else if( (rectNave.left == 2*66 && rectNave.top == 0*66) && !(rectNave.left == 1*66 && rectNave.top == 1*66) ) { // Left-Down !Right-Up
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
    }
    if( (rectNave.left == 1*66 && rectNave.top == 0*66) && !(rectNave.left == 2*66 && rectNave.top == 1*66) ) { // Right-Down !Left-Up
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
    } else if( (rectNave.left == 2*66 && rectNave.top == 1*66) && !(rectNave.left == 1*66 && rectNave.top == 0*66) ) { // Left-Up !Right-Down
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
    }

}

void Nave::colisionNave(sf::Time timeElapsed)
{
    //mostrarColision = true;
    //CUADRADO DE COLISION DE LA NAVE
    rectColision.setSize(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    rectColision.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    rectColision.setFillColor(Color::Blue);

    //CUADRADO VISTA JUEGO
    //mostrarRectInicial = true;
    rectInicial.setSize(Vector2f(Configuracion::TAMANYO_VISTA_JUEGO_X, Configuracion::TAMANYO_PANTALLA_Y));
    rectInicial.setPosition(sprite.getGlobalBounds().left-(Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ/2), sprite.getGlobalBounds().top-(Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ/2));
    rectInicial.setFillColor(Color::Magenta);
}

void Nave::updateBalas(sf::Time timeElapsed)
{
    //std::cout << tiempoDisp << std::endl;
    if(Keyboard::isKeyPressed(sf::Keyboard::Space) && tiempoDisp == 0)
    {
        //std::cout << "2 nuevas balas" << std::endl;
        balas.push_back(new Bala((&sprite), -1)); //bala arriba
        balas.push_back(new Bala((&sprite), 1)); //bala abajo
        tiempoDisp = 20;
    }
    if(tiempoDisp > 0)
    {
        tiempoDisp--;
    }

    //Si tengo balas en marcha
    if( !balas.empty() )
    {
        //Llamo al update de cada bala
        View *viewJuego = Bosconian::Instance()->getViewJuego();
        int min_pos_x_view = viewJuego->getCenter().x-((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*2));
        int min_pos_y_view = viewJuego->getCenter().y-((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*2));
        int max_pos_x_view = viewJuego->getCenter().x+((Configuracion::TAMANYO_VISTA_JUEGO_X/2)+(Configuracion::TAMANYO_SPRITE_PEQ*2));
        int max_pos_y_view = viewJuego->getCenter().y+((Configuracion::TAMANYO_PANTALLA_Y/2)+(Configuracion::TAMANYO_SPRITE_PEQ*2));
        for (int cont = 0; cont < balas.size(); cont++)
        {

            if((balas.at(cont))->getSprite().getPosition().y > Configuracion::MIN_POS_Y ||
                (balas.at(cont))->getSprite().getPosition().y < Configuracion::MAX_POS_Y ||
                (balas.at(cont))->getSprite().getPosition().x < Configuracion::MAX_POS_X ||
                (balas.at(cont))->getSprite().getPosition().x > Configuracion::MIN_POS_X)
            {
                //std::cout << "UPDATE bala" << std::endl;
                (balas.at(cont))->update(timeElapsed);
            }

            //Borro las balas que han chocado con algun enemigo u objeto
            if( (balas.at(cont))->getBorrar() )
            {
                //std::cout << "borro bala que choca" << std::endl;
                delete(balas.at(cont));
                balas.erase(balas.begin()+cont);
            }
            // Borro las balas cuando estan a una distancia de 2 sprites pequenyos fuera de la vista
            else if((balas.at(cont))->getSprite().getPosition().y < min_pos_y_view ||
                (balas.at(cont))->getSprite().getPosition().y > max_pos_y_view ||
                (balas.at(cont))->getSprite().getPosition().x > max_pos_x_view ||
                (balas.at(cont))->getSprite().getPosition().x < min_pos_x_view )
            {
                //std::cout << "borro bala lejena" << std::endl;
                delete(balas.at(cont));
                balas.erase(balas.begin()+cont);
            }

        }
    }

}

void Nave::render(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();

    if( !balas.empty() )
    {
        for (int cont = 0; cont < balas.size(); cont++)
        {
            //std::cout << "disparoo!!" << std::endl;
            (balas.at(cont))->render(percentTick);
        }
    }

    if(mostrarColision)
    {
        window->draw(rectColision);
    }
    if(mostrarRectInicial)
    {
        window->draw(rectInicial);
    }


    /*
    // Vista del juego de verdad, si saliese la del Hud
    View *viewJuego = Bosconian::Instance()->getViewJuego();
    viewJuego->setCenter(sprite.getPosition().x+(66/2), sprite.getPosition().y-(66/2));
    //vistaJ->setViewport(FloatRect(0.0, 0.0, 0.732421875, 1.0));
    */

    //Vista Juego
    View *viewJuego = Bosconian::Instance()->getViewJuego();
    viewJuego->setCenter(sprite.getPosition().x+(66/2)+(Configuracion::TAMANYO_HUD_X-135), sprite.getPosition().y-(66/2));

    if(!muerto){
        window->draw(sprite);
    } else if(!explosion->getTermina() && muerto)
    {
        explosion->render(percentTick);
    }


}

void Nave::renderMiniMapa(double percentTick)
{
    sf::RenderWindow *window = Bosconian::Instance()->getWindow();
    //sprite.setScale(2,2);
    if(!muerto){
        window->draw(sprite);
    } else if(!explosion->getTermina() && muerto)
    {
        explosion->render(percentTick);
    }


}
